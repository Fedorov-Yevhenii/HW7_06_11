#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

/*
 * Напишіть програму, яка створює новий потік виконання.
 * При створенні використовуйте стандартні атрибути потоку.
 * Початковий та новостворений потік повинні вивести у стандартний потік виведення десять рядків тексту
 * (Батьківський потік виводить рядки виду «Main Thread. Iteration: 1», новий потік: «Child Thread. Iteration: 1»).
 * Після виведення рядка кожен потік «засипає» на задану кількість секунд (наприклад, від 0 до 2).
*/

void *childThread(void *arg) {
    // 1. Приведення типу *arg для інтерпретування компілятором як вказівника на int
    int count = *((int *) arg);

    for (int i = 0; i < 10; i++) {
        // 2. Виведення рядка нового потоку
        printf("Child Thread. Iteration: %d\n", count + 1);
        // 3. Призупинення потоку від на термін 0 до 2 секунд
        sleep(rand()%3);

    }

}

int main() {

    pthread_t child_thread;
    int count = 0;
    srand(time(nullptr));

    for (count = 0; count < 10; count++) {

        printf("Main Thread. Iteration: %d\n", count + 1);

        if (pthread_create(&child_thread, nullptr, childThread, &count) != 0) {
            // On success, pthread_create() returns 0;
            // On error, it returns an error number, and the contents of *thread are undefined.
            fprintf(stderr, "Error during new thread initializing.\n");
            return 1;

        }
        pthread_join(child_thread, nullptr);
        sleep(rand() % 3);

    }

    return 0;
}