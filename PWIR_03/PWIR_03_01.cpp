#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <iostream>

//matrix * vector

#define MATRIX_H 30000
#define MATRIX_W 30000
#define VECTOR_S 30000
#define MUL_TIME 25

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
    for(i = 0;i<MATRIX_H;i++){
        for(k = 0;k<MATRIX_W;k++){
            matrix[i][k] = (uint16_t)(rand() % 100);
        }
    }

    //fill vector random data
    for(i = 0;i<VECTOR_S;i++){
        vector[i] = (uint16_t)(rand() % 100);
    }

    //schedule(how to split iteration, [chunk size])
    //let user to controll iteration split between threads
    //chunk - how many iteration counts every chunk
    //first arg:
    //static:
    //  -iterations split on equal chunk of specified size or iterations/threads
    //  -chunk is mapped statically to thread
    //dynamic:
    //  -like static
    //  -but chunks are mapped dynamically
    //guided:
    //  -like dynamic
    //  -chunk count decrease during processing
    //runtime:
    //  -both argument are specified at runtime base on OMP_SCHEDULE var

    #pragma omp parallel for default(shared) private(i, k)
    for(i = 0;i<MATRIX_H;i++){
        for(k = 0;k<MATRIX_W;k++){
            matrix[i][k] = (uint16_t)(rand() % 100);           
        }
    }
    
    #pragma omp parallel for default(shared) private(i)
    for(i = 0;i<VECTOR_S;i++){
        vector[i] = (uint16_t)(rand() % 100);
    }

    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for schedule(static) shared(matrix, vector, result) private(i, k)
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for schedule(static) shared(matrix, vector, result) private(i, k)
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel static way in %llu miliseconds\n", 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

int duration_static=0;
for (int ile=0; ile<5; ile++){
   
    start = std::chrono::high_resolution_clock::now();
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for schedule(static, MATRIX_H/10) shared(matrix, vector, result) private(i, k)
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel static N(MATRIX_H/10) way in %llu miliseconds\n", 
     std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

     duration_static+=std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    
}

    printf("Srednia static N(MATRIX_H/10) wynosi: %llu \n",duration_static/5);
     


int duration_dynamic=0;
for (int ile=0; ile<5; ile++){
    start = std::chrono::high_resolution_clock::now();
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for schedule(dynamic, MATRIX_H/10) shared(matrix, vector, result) private(i, k)
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel dynamic N(MATRIX_H/10) way in %llu miliseconds\n", 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

  duration_dynamic+=std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    
}


    printf("Srednia dynamic N(MATRIX_H/10) wynosi: %llu \n",duration_dynamic/5);



int duration_guided=0;
for (int ile=0; ile<5; ile++){
    start = std::chrono::high_resolution_clock::now();
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for schedule(guided, MATRIX_H/10) shared(matrix, vector, result) private(i, k)
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel guided N(MATRIX_H/10) way in %llu miliseconds\n", 

std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

     duration_guided+=std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    
}



    printf("Srednia guided N(MATRIX_H/10) wynosi: %llu \n",duration_guided/5);
    


int duration_runtime=0;
for (int ile=0; ile<5; ile++){
    start = std::chrono::high_resolution_clock::now();
    for(uint32_t p = 0; p < MUL_TIME;p++){
        #pragma omp parallel for schedule(runtime) shared(matrix, vector, result) private(i, k)
        for(i = 0;i<MATRIX_H;i++){
            for(k = 0;k<MATRIX_W;k++){
                result[i] += matrix[i][k] * vector[k];           
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    printf("Calculated parallel runtime way in %llu miliseconds\n", 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    duration_runtime+=std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    
}

    printf("Srednia runtime N(MATRIX_H/10) wynosi : %llu \n",duration_runtime/5);


    //free memory
    free(vector);
    free(result);

    for(i = 0;i<MATRIX_H;i++)
        free(matrix[i]);
    
    
    free(matrix);

    return 0;
}