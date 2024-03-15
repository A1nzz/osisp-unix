#include <stdio.h>
#include <stdlib.h>
#include "reverse.h"

#define MAX_LENGTH 1000 // Максимальная длина строки

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл: %s\n", filename);
        return 1;
    }

    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        reverseString(line);
        printf("%s\n", line);
    }

    fclose(file);

    return 0;
}