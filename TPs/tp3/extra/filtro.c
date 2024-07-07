typedef struct {
    int size;
    int num_hashes;
    double resize_threshold;
    int resize_factor;
    int *filter;
    unsigned int *hash_seeds;
    int element_count;
} countfilter_t;

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
    if (contains_in_filter(filter, element)) {
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
