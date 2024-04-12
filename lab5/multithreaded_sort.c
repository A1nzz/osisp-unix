#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define MAX_THREADS 8

// Структура, представляющая фрагмент массива и его размер
typedef struct {
    int* array;
    size_t size;
} ArrayFragment;

// Функция для сравнения элементов массива
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Функция, выполняемая каждым потоком для сортировки своего фрагмента
void* sortFragment(void* arg) {
    ArrayFragment* fragment = (ArrayFragment*)arg;
    qsort(fragment->array, fragment->size, sizeof(int), compare);
    return NULL;
}
void mergeArrays(int* arr1, int* arr2, size_t size1, size_t size2) {
    int* mergedArray = (int*)malloc((size1 + size2) * sizeof(int));

    size_t i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            mergedArray[k++] = arr1[i++];
        } else {
            mergedArray[k++] = arr2[j++];
        }
    }

    while (i < size1) {
        mergedArray[k++] = arr1[i++];
    }

    while (j < size2) {
        mergedArray[k++] = arr2[j++];
    }

    // Копирование объединенного массива обратно в arr1
    memcpy(arr1, mergedArray, (size1 + size2) * sizeof(int));

    free(mergedArray);
}

// Функция для вывода массива
void printArray(const int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


int main() {
    int numThreads, arraySize;
    while (1) {
        printf("Введите количество потоков (1-%d): ", MAX_THREADS);
        scanf("%d", &numThreads);
        if (numThreads >= 1 && numThreads <= MAX_THREADS) {
            break;
        }
        printf("Некорректный ввод. Попробуйте еще раз.\n");
    }

    while (1) {
        printf("Введите размер массива: ");
        scanf("%d", &arraySize);
        if (arraySize > 0) {
            break;
        }
        printf("Некорректный ввод. Попробуйте еще раз.\n");
    }

    // Создание и инициализация массива случайными числами
    int* array = (int*)malloc(arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand();
    }

    printf("Сгенерированный массив:\n");
    printArray(array, arraySize);

    // Разделение массива на фрагменты для каждого потока
    ArrayFragment fragments[MAX_THREADS];
    int fragmentSize = arraySize / numThreads;
    for (int i = 0; i < numThreads; i++) {
        fragments[i].array = array + i * fragmentSize;
        fragments[i].size = (i == numThreads - 1) ? (arraySize - i * fragmentSize) : fragmentSize;
    }

    // Создание потоков и запуск сортировки для каждого фрагмента
    pthread_t threads[MAX_THREADS];
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, sortFragment, (void*)&fragments[i]);
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    printf("Отсортированные фрагменты:\n");
    for (int i = 0; i < numThreads; i++) {
        printf("Фрагмент %d: ", i + 1);
        printArray(fragments[i].array, fragments[i].size);
    }

    // Объединение отсортированных фрагментов
    for (int i = 1; i < numThreads; i++) {
        mergeArrays(fragments[0].array, fragments[i].array, fragments[0].size, fragments[i].size);
    }

    printf("Результат сортировки:\n");
    printArray(array, arraySize);

    // Вывод времени выполнения
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    printf("Время выполнения: %.6f секунд\n", elapsed);

    free(array);
    return 0;
}