#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#define REPEATS 10 //
#define RANGE_DOWN 0 // НИЖНЯ ГРАНИЦЯ ДІАПАЗОНУ ПСЕВДОВИПАДКОВИХ ЧИСЕЛ
#define RANGE_UP 100 // ВЕРХНЯ...
#define STOP_VALUE (rand()%100) // Задане псевдовипадкове число, при якому потік завершує роботу

/*
 * Напишіть програму, яка створює два нових потоки виконання.
 * Один із потоків — нащадків виводить у стандартний потік виведення задану кількість разів заданий рядок (аналогічну рядкам із Завдання No1)
 * Інший потік генерує задану кількість цілих псевдовипадкових чисел із заданого діапазону і виводить їх у стандартний потік виведення в вигляді,
 * аналогічному висновку першого потоку - нащадка. Якщо під час роботи цього потоку буде отримано задане псевдовипадкове число,
 * то потік передчасно завершує свою роботу з видачею відповідного повідомлення.
 * Основний, батьківський потік, чекає закінчення роботи всіх дочірніх потоків і виводить у стандартний потік виведення своє повідомлення.
*/

void *randomGenerate(void *arg) { // Функція для генерації випадкових чисел

    srand(time(NULL));

    while (true) {

        int num = RANGE_DOWN + rand() % (RANGE_UP - RANGE_DOWN);
        printf("Thread SECOND: Generated %d\n", num);

        if (num == STOP_VALUE) {
            printf("Thread SECOND: Stopped with the STOP_VALUE (%d).\n", STOP_VALUE);
            break;
        }
    }

    pthread_exit(NULL);
}

void *strPrint(void *arg) { // Функція друкування рядка

    char *str = (char *)arg;

    for (int i = 1; i <= REPEATS; i++) {
        printf("Thread FIRST: %s %d\n", str, i);
    }

    pthread_exit(NULL);

}

int main() {

    pthread_t thread1, thread2;
    char *str = "...routine #";

    pthread_create(&thread1, NULL, strPrint, str);
    pthread_create(&thread2, NULL, randomGenerate, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread FIRST: Thread SECOND has finished.\n");
    return 0;

}