#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

DEFINE_ARRAY(double)
CREATE_ARRAY(double)
SORT_ARRAY(double)
LOAD_ARRAY(double)
FREE_ARRAY(double)
SAVE_ARRAY(double)
DEFINE_ARRAY(int)
CREATE_ARRAY(int)
SORT_ARRAY(int)
LOAD_ARRAY(int)
FREE_ARRAY(int)
SAVE_ARRAY(int)

int main() {
    char* filename = calloc(31, sizeof(char));
    if(filename==NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Filename: ");
    fgets(filename, 50, stdin);
    if(*(filename+ strlen(filename)-1) == '\n'){
        *(filename+ strlen(filename)-1) = '\0';
    }

    int type, res;
    printf("TYPE: ");
    res = scanf("%d", &type);
    if(res!=1){
        printf("Incorrect input");
        free(filename);
        return 1;
    }
    if(!(type==0 || type==1)){
        printf("Incorrect input data");
        free(filename);
        return 2;
    }
    struct array_int_t *structint;
    struct array_double_t *structdouble;
    switch (type) {
        case 0:
            res = load_array_int(&structint, filename);
            switch (res) {
                case 2:
                    printf("Couldn't open file");
                    free(filename);
                    return 4;
                case 3:
                    printf("File corrupted");
                    free(filename);
                    return 6;
                case 4:
                    printf("Failed to allocate memory");
                    free(filename);
                    return 8;
            }
            sort_array_int(structint);
            res = save_array_int(structint, filename);
            if(res!=0) {
                    printf("Couldn't create file");
                    free_array_int(structint);
                    free(filename);
                    return 5;
            }
            printf("File saved");
            free_array_int(structint);
            free(filename);
            return 0;
        case 1:
            res = load_array_double(&structdouble, filename);
            switch (res) {
                case 2:
                    printf("Couldn't open file");
                    free(filename);
                    return 4;
                case 3:
                    printf("File corrupted");
                    free(filename);
                    return 6;
                case 4:
                    printf("Failed to allocate memory");
                    free(filename);
                    return 8;
            }
            sort_array_double(structdouble);
            res = save_array_double(structdouble, filename);
            if(res!=0) {
                printf("Couldn't create file");
                free(filename);
                free_array_double(structdouble);
                return 5;
            }
            printf("File saved");
            free_array_double(structdouble);
            free(filename);
            return 0;
    }

    free(filename);
    return 0;
}
