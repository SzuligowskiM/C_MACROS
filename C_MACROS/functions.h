#ifndef ZAD9_15_FUNCTIONS_H
#define ZAD9_15_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#define DEFINE_ARRAY(TYPE) \
    struct array_##TYPE##_t{           \
         int size;         \
         int capacity;     \
         TYPE* data; \
    };

#define CREATE_ARRAY(TYPE) \
    struct array_##TYPE##_t *create_array_##TYPE(int size){ \
       if(size <= 0) return NULL;                         \
       struct array_##TYPE##_t *structures;                   \
       structures = calloc(1, sizeof(struct array_##TYPE##_t));\
       if(structures == NULL) return NULL;                 \
                            \
       structures -> data = calloc(size, sizeof(TYPE));       \
       if(structures -> data == NULL){                     \
          free(structures);  \
          return NULL;\
       }                    \
       structures -> capacity = size;                     \
       structures -> size = 0;\
       return structures;                         \
    }

#define FREE_ARRAY(TYPE) \
     void free_array_##TYPE(struct array_##TYPE##_t *array){ \
        if(array!=NULL){ \
            free(array->data);             \
            free(array);              \
        }                     \
     }

#define SAVE_ARRAY(TYPE) \
       int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename){ \
            if(array == NULL || filename==NULL || array->size<=0 || array->capacity<=0 || array->capacity<array->size || array->data == NULL) return 1;\
            FILE *f;      \
            f = fopen(filename, "wb");                                         \
            if(f == NULL) return 2;\
            int res;             \
            res = fwrite(&(array->size), sizeof(int), 1, f);                              \
            if(res!=1) return 3;\
            res = fwrite(array->data, sizeof(TYPE), array->size, f);                        \
            if(res!= array->size) return 3;\
                         \
            fclose(f);              \
            return 0;               \
       }

#define LOAD_ARRAY(TYPE) \
      int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename){ \
        if(array == NULL || filename==NULL) return 1;                               \
        FILE* f;         \
        f = fopen(filename, "rb");                                                  \
        if(f == NULL) return 2;                                                     \
        int count_of_structs, res;                                                       \
        res = fread(&count_of_structs, sizeof(int), 1, f);                          \
        if(res!=1){      \
         fclose(f);       \
         return 3;                 \
        }                 \
        if(count_of_structs <= 0){                                                  \
            fclose(f);       \
            return 3;               \
        }                \
                         \
        *array = create_array_##TYPE(count_of_structs);                \
        if(*array == NULL){                                                        \
            fclose(f);   \
            return 4;             \
        }                \
        res = fread((*array)->data, sizeof(TYPE), count_of_structs, f);             \
        if(res!=count_of_structs){                                                  \
            fclose(f);   \
            free_array_##TYPE(*array);\
            return 3;\
                         \
        }                \
        fclose(f);                 \
                         \
        (*array) -> size = count_of_structs;               \
        return 0;\
      }

#define SORT_ARRAY(TYPE) \
      int sort_array_##TYPE(struct array_##TYPE##_t *array){ \
            if(array == NULL || array->size<=0 || array->capacity<=0 || array->capacity<array->size || array->data == NULL) return 1; \
            TYPE holder;             \
            for(int i=0; i<(array->size) -1; i++){                \
                for(int y=0; y<(array->size) -1; y++){     \
                    if(*(array->data+y) > *(array->data+y+1)){                                                                        \
                        holder = *(array->data+y+1);     \
                        *(array->data+y+1) = *(array->data+y);                                                                        \
                        *(array->data+y) = holder;\
                    }         \
                }             \
            }             \
            return 0;\
      }

#endif