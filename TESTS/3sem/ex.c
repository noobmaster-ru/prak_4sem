#include <stdio.h>
#include <stdlib.h>

// посимвольное получение динамической строки с пробелами c получением её реальной длины
char *get_string(int *len) {
    *len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char *s = (char*) malloc(sizeof(char)); // динамическая пустая строка

    char c = getchar(); // символ для чтения данных

    // читаем символы, пока не получим символ переноса строки (\n)
    while (c != '\n') {
        s[(*len)++] = c; // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) {
            capacity += 1; // увеличиваем ёмкость строки в два раза
            s = (char*) realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }

        c = getchar(); // считываем следующий символ          
    }

    s[*len] = '\0'; // завершаем строку символом конца строки

    return s; // возвращаем указатель на считанную строку
}

int main() {
    int len; // длина строки
    char *s = get_string(&len); // считываем динамическую строку

    printf("You've wrote: '%s', symbols: %d\n", s, len); // выводим строку и её длину
    free(s); // освобождаем динамическую память

    return 0;
}