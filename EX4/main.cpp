#include <cstdio>
#include <pthread.h>

#define PRIME_NUMBERS 20 // Кількість простих чисел
#define CATALAN_NUMBERS 10 // Кількість чисел Каталана

/*
 * Напишіть програму, яка створює два нових потоки виконання.
 * Один із нових потоків виконання обчислює задану кількість перших чисел Каталана,
 * інший новий потік виконання обчислює задану кількість перших простих чисел.
 * Потім, обчислений масив чисел повертається кожним потоком — нащадком у очікування завершення основної.
*/

void *catalanNumberEvaluation(void *arg) { // Функція обчислення чисел Каталана

    int N = *((int *) arg);
    unsigned long long catalan[100];
    catalan[0] = 1;

    for (int i = 1; i <= N; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }

    printf("%d CATALAN NUMBERS:\n", N);
    for (int i = 0; i < N; i++) {
        printf("%d) %llu\n", i+1, catalan[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}

bool isPrime(int N) { // Функція перевірки числа на простоту

    if (N <= 1) return false;
    for (int i = 2; i <= N / 2; i++)
        if (N % i == 0)
            return false;

    return true;
}

void *calculatePrimes(void *arg) { // Функція для обчислення перших N простих чисел

    int N = *((int *) arg);
    int Prime[100];
    int tmp_Number = 2;
    int i = 0;

    while (i < N) {
        if (isPrime(tmp_Number)) {
            Prime[i] = tmp_Number;
            i++;
        }
        tmp_Number++;
    }

    printf("%d PRIME NUMBERS:\n", N);
    for (i = 0; i < N; i++) {
        printf("%d) %d\n", i+1, Prime[i]);
    }

    printf("\n");
    pthread_exit(NULL);
}

int main() {
    
    pthread_t FIRST, SECOND;
    int a = CATALAN_NUMBERS;
    int b = PRIME_NUMBERS; 

    pthread_create(&FIRST, NULL, catalanNumberEvaluation, &a);
    pthread_create(&SECOND, NULL, calculatePrimes, &b);

    pthread_join(FIRST, NULL);
    pthread_join(SECOND, NULL);

    return 0;
}