#include <cstdio>
#include <pthread.h>

/*
 * Напишіть програму, яка створює чотири потоки, що виконують одну і ту ж потокову функцію.
 * Ця функція повинна прийняти як параметри ім'я потоку name, базовий рядок для виведення str
 * і кількість повторень рядка num і вивести стандартний потік виведення послідовність текстових рядків,
 * сформованих за правилом: Thread name. Str i де i - ціле число, що визначає повторення рядка.
 * Кожен потік має отримати свій набір параметрів.
*/

void *threadRoutine(void *arg) { // Функція потоків
    char *name = ((char **) arg)[0]; // Ім'я потоку
    char *str = ((char **) arg)[1]; // Рядок для виведення
    int num = *((int *) arg); // Кількість повторень рядка

    for (int i = 1; i <= num; i++) {
        printf("Thread %s. %s %d\n", name, str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread[3];
    char *name[3] = {"FIRST", "SECOND", "THIRD"};
    char *str = "Number of repetitions: ";

    for (int i = 0; i < 4; i++) {
        char *args[2] = {name[i], str};
        pthread_create(&thread[i], NULL, threadRoutine, args);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}