#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openssl/md5.h>

// Constantes para el filtro de conteo
#define INITIAL_SIZE 1000
#define NUM_HASHES 3
#define RESIZE_THRESHOLD 0.1
#define RESIZE_FACTOR 2

typedef struct {
    int size;
    int num_hashes;
    double resize_threshold;
    int resize_factor;
    int *filter;
    unsigned int *hash_seeds;
    int element_count;
} countfilter_t;

typedef struct {
    void **elements;
    int count;
    int capacity;
    countfilter_t *filter;
    size_t data_type_size;
    unsigned char *(*hash_function)(const unsigned char *, size_t, unsigned char *);
    int (*compare_function)(const void *, const void *);
} unique_list_t;

unsigned int *generate_seeds(int num_hashes) {
    unsigned int *seeds = malloc(num_hashes * sizeof(unsigned int));
    for (int i = 0; i < num_hashes; i++) {
        seeds[i] = rand();
    }
    return seeds;
}

unsigned char *md5_hash(const unsigned char *data, size_t length, unsigned char *result) {
    MD5(data, length, result);
    return result;
}

int *get_indices(countfilter_t *filter, unsigned char *hashes) {
    int *indices = malloc(filter->num_hashes * sizeof(int));
    for (int i = 0; i < filter->num_hashes; i++) {
        indices[i] = (hashes[i * MD5_DIGEST_LENGTH] + filter->hash_seeds[i]) % filter->size;
    }
    return indices;
}

countfilter_t *create_count_filter(int size, int num_hashes, double resize_threshold, int resize_factor) {
    countfilter_t *filter = malloc(sizeof(countfilter_t));
    if (!filter) return NULL;
    filter->size = size;
    filter->num_hashes = num_hashes;
    filter->resize_threshold = resize_threshold;
    filter->resize_factor = resize_factor;
    filter->filter = calloc(size, sizeof(int));
    if (!filter->filter) {
        free(filter);
        return NULL;
    }
    filter->hash_seeds = generate_seeds(num_hashes);
    filter->element_count = 0;
    return filter;
}

double false_positive_probability(countfilter_t *filter) {
    return pow(1 - exp(-filter->num_hashes * (double)filter->element_count / filter->size), filter->num_hashes);
}

void resize_count_filter(countfilter_t *filter, int new_size) {
    int *old_filter = filter->filter;
    int old_size = filter->size;
    filter->size = new_size;
    filter->filter = calloc(new_size, sizeof(int));
    if (!filter->filter) return;
    filter->hash_seeds = generate_seeds(filter->num_hashes);

    for (int i = 0; i < old_size; i++) {
        if (old_filter[i] > 0) {
            char element[12];
            snprintf(element, 12, "%d", i);
            unsigned char hash[MD5_DIGEST_LENGTH];
            md5_hash((unsigned char *)element, strlen(element), hash);
            int *indices = get_indices(filter, hash);
            for (int j = 0; j < filter->num_hashes; j++) {
                filter->filter[indices[j]] += old_filter[i];
            }
            free(indices);
        }
    }
    free(old_filter);
}

void add_to_filter(countfilter_t *filter, const char *element) {
    filter->element_count++;
    unsigned char hash[MD5_DIGEST_LENGTH];
    md5_hash((unsigned char *)element, strlen(element), hash);
    int *indices = get_indices(filter, hash);
    for (int i = 0; i < filter->num_hashes; i++) {
        filter->filter[indices[i]]++;
    }
    free(indices);

    if (false_positive_probability(filter) > filter->resize_threshold) {
        resize_count_filter(filter, filter->size * filter->resize_factor);
    }
}

void remove_from_filter(countfilter_t *filter, const char *element) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    md5_hash((unsigned char *)element, strlen(element), hash);
    int *indices = get_indices(filter, hash);
    for (int i = 0; i < filter->num_hashes; i++) {
        if (filter->filter[indices[i]] > 0) {
            filter->filter[indices[i]]--;
        }
    }
    filter->element_count--;
    free(indices);
}

int contains_in_filter(countfilter_t *filter, const char *element) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    md5_hash((unsigned char *)element, strlen(element), hash);
    int *indices = get_indices(filter, hash);
    for (int i = 0; i < filter->num_hashes; i++) {
        if (filter->filter[indices[i]] == 0) {
            free(indices);
            return 0;
        }
    }
    free(indices);
    return 1;
}

unique_list_t *create_unique_list(size_t data_type_size, unsigned char *(*hash_function)(const unsigned char *, size_t, unsigned char *), int (*compare_function)(const void *, const void *)) {
    unique_list_t *list = malloc(sizeof(unique_list_t));
    if (!list) return NULL;
    list->elements = malloc(INITIAL_SIZE * sizeof(void *));
    if (!list->elements) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = INITIAL_SIZE;
    list->filter = create_count_filter(INITIAL_SIZE, NUM_HASHES, RESIZE_THRESHOLD, RESIZE_FACTOR);
    list->data_type_size = data_type_size;
    list->hash_function = hash_function;
    list->compare_function = compare_function;
    return list;
}

int insert_to_unique_list(unique_list_t *list, void *element) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    list->hash_function((unsigned char *)element, list->data_type_size, hash);

    if (!contains_in_filter(list->filter, (char *)hash)) {
        if (list->count == list->capacity) {
            list->capacity *= RESIZE_FACTOR;
            list->elements = realloc(list->elements, list->capacity * sizeof(void *));
            if (!list->elements) return 0;
        }
        list->elements[list->count] = malloc(list->data_type_size);
        if (!list->elements[list->count]) return 0;
        memcpy(list->elements[list->count], element, list->data_type_size);
        add_to_filter(list->filter, (char *)hash);
        list->count++;
        return 1;
    } else {
        for (int i = 0; i < list->count; i++) {
            if (list->compare_function(list->elements[i], element)) {
                return 0;
            }
        }
        if (list->count == list->capacity) {
            list->capacity *= RESIZE_FACTOR;
            list->elements = realloc(list->elements, list->capacity * sizeof(void *));
            if (!list->elements) return 0;
        }
        list->elements[list->count] = malloc(list->data_type_size);
        if (!list->elements[list->count]) return 0;
        memcpy(list->elements[list->count], element, list->data_type_size);
        add_to_filter(list->filter, (char *)hash);
        list->count++;
        return 1;
    }
}

int delete_from_unique_list(unique_list_t *list, void *element) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    list->hash_function((unsigned char *)element, list->data_type_size, hash);

    if (contains_in_filter(list->filter, (char *)hash)) {
        for (int i = 0; i < list->count; i++) {
            if (list->compare_function(list->elements[i], element)) {
                free(list->elements[i]);
                for (int j = i; j < list->count - 1; j++) {
                    list->elements[j] = list->elements[j + 1];
                }
                list->count--;
                remove_from_filter(list->filter, (char *)hash);
                return 1;
            }
        }
    }
    return 0;
}

void resize_unique_list_filter(unique_list_t *list, int new_size) {
    resize_count_filter(list->filter, new_size);
}

// Ejemplo de funciones de hash y comparación
unsigned char *example_hash_function(const unsigned char *data, size_t length, unsigned char *result) {
    return md5_hash(data, length, result);
}

int example_compare_function(const void *el1, const void *el2) {
    return strcmp((const char *)el1, (const char *)el2) == 0;
}

// Ejemplo de uso
int main() {
    unique_list_t *unique_list = create_unique_list(sizeof(char *), example_hash_function, example_compare_function);

    char *element1 = "elemento1";
    char *element2 = "elemento2";
    char *element3 = "elemento3";

    insert_to_unique_list(unique_list, element1);
    insert_to_unique_list(unique_list, element2);
    insert_to_unique_list(unique_list, element3);

    delete_from_unique_list(unique_list, element2);

    resize_unique_list_filter(unique_list, 2000);

    for (int i = 0; i < unique_list->count; i++) {
        free(unique_list->elements[i]);
    }
    free(unique_list->elements);
    free(unique_list->filter->filter);
    free(unique_list->filter->hash_seeds);
    free(unique_list->filter);
    free(unique_list);

    return 0;
}

