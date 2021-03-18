#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>

//matrix * vector

#define MATRIX_H 30000
#define MATRIX_W 30000
#define VECTOR_S 30000
#define MUL_TIME 100

uint16_t** matrix;
uint16_t* vector;
uint16_t* result;

uint32_t i;
uint32_t k;

int main(){
    //check if vector size == matrix width
    assert(MATRIX_W == VECTOR_S);

    //alloc matrix
    matrix = (uint16_t**)new uint16_t*[MATRIX_H];
    for (i = 0;i<MATRIX_H;i++)
        matrix[i] = new uint16_t[MATRIX_W];

    //alloc vectors
    vector = (uint16_t*)new uint16_t[VECTOR_S];
    result = (uint16_t*)new uint16_t[VECTOR_S];

    //fill matrix random data normal way  
    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for shared(matrix) private(i, k)
    for(int ile=1; ile <5; ile ++){
        for(i = 0;i<MATRIX_H;i++){
            for(i = 0;i<MATRIX_H;i++){
                for(k = 0;k<MATRIX_W;k++){
                   matrix[i][k] = (uint16_t)(rand() % 100);           
                }
            }
        }
    }
    
    #pragma omp parallel for shared(vector) private(i)
    for(i = 0;i<VECTOR_S;i++){
        vector[i] = (uint16_t)(rand() % 100);
    }
     auto end = std::chrono::high_resolution_clock::now();

    printf("Fill parallel way in %lu miliseconds\n",
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

//normal execution
    start = std::chrono::high_resolution_clock::now();
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for shared(matrix, vector, result) private(i, k)
        for (int ile=1; ile<5; ile++){
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }

        }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel way in %lu miliseconds\n",
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    //free memory
    free(vector);
    free(result);

    for(i = 0;i<MATRIX_H;i++)
        free(matrix[i]);
    
    free(matrix);

    return 0;
}