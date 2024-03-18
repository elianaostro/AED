#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// para nombres que terminaban en ‘a’ u ‘o’, se les agregaba 'ic' antes de la última letra

void setDiminutivo(const char *nombre, char *diminutivo) {
    strcpy(diminutivo, nombre);
    if (nombre[strlen(nombre)] == 'a'|| nombre[strlen(nombre)] == 'o' ){
        diminutivo[strlen(nombre)] = '\0';
        char final[]={'i','c', nombre[strlen(nombre)] ,'\0'};
        strcat(diminutivo,final);
    } 
}

char* getDiminutivo(const char* nombre) {
    char * diminutivo = malloc(sizeof(char) * strlen(nombre) + 3);
    setDiminutivo(nombre, diminutivo);

    return diminutivo;
}

void testDiminutivo(char* actual, char* expected) {
    if(strcmp(actual, expected)){
        printf("TEST FAILED | Actual: %s Expected: %s \n", actual, expected);
    }
    else {
        printf("TEST PASSED |  Actual: %s Expected: %s \n", actual, expected);
    }
}

int main() {

    // TEST 1
    char* test_1 = "magali";
    char* expected_1 = "magali";
    char* test_1_result = getDiminutivo(test_1);
    testDiminutivo(expected_1, test_1_result);
    free(test_1_result);

    // TEST 2
    char* test_2 = "roberto";
    char* expected_2 = "robertico";
    char* test_2_result = getDiminutivo(test_2);
    testDiminutivo(expected_2, test_2_result);
    free(test_2_result);

    // TEST 3
    char* test_3 = "marta";
    char* expected_3 = "martica";
    char* test_3_result = getDiminutivo(test_3);
    testDiminutivo(expected_3, test_3_result);
    free(test_3_result);
    
    // TEST 4
    char* test_4 = "juan";
    char* expected_4 = "juan";
    char* test_4_result = getDiminutivo(test_4);
    testDiminutivo(expected_4, test_4_result);
    free(test_4_result);

    return 0;
}
