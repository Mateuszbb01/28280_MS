#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>

#include <time.h>
#include <iostream>
using namespace std;

#define MATRIX_H 30000
#define MATRIX_W 30000

    uint32_t sum = 0;
    uint32_t i;
    uint32_t k;

    uint8_t** matrix;

int main()
{



    srand(time(NULL));
    int tabrozmiar = 10000;
    int tab[tabrozmiar];
    int rozmiara=0;
    int rozmiarb=0;

    auto  start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < tabrozmiar; i++)
    {
        tab[i] = rand() % 11;
    }
    #pragma omp parallel for shared(matrix) private(i, k) reduction(+ : sum)
    for(int i = 0; i < tabrozmiar; i++)
    {
        rozmiara+=1;

    }

 auto  end = std::chrono::high_resolution_clock::now();


     printf("deklaracja: %u in time: %llu ms\r\n", rozmiara,
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


       start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < tabrozmiar; i++)
    {
        tab[i] = rand() % 11;
    }

    for(int i = 0; i < tabrozmiar; i++)
    {
        rozmiarb+=1;

    }

   end = std::chrono::high_resolution_clock::now();


     printf("bez deklaracji: %u in time: %llu ms\r\n", rozmiarb,
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());



   return 0;
}
