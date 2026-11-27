#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"

static int read_integer(const char *text, int *number)
{
    const char *digit = text;
    if (*digit == '+' || *digit == '-') {
        digit++;
    }
    if (*digit < '0' || *digit > '9') {
        return 0;
    }

    char *end;
    long long value = strtoll(text, &end, 10);

    if (*end != '\0' || value < -2147483648LL || value > 2147483647LL) {
        return 0;
    }

    *number = (int)value;
    return 1;
}

int main(int argc, char *argv[])
{
    int key;
    if (argc < 6 || (argc - 3) % 3 != 0 ||
        strcmp(argv[argc - 2], "-k") != 0 ||
        !read_integer(argv[argc - 1], &key)) {
        fputs("Использование: practical-calc ЧИСЛО ОПЕРАТОР ЧИСЛО [...] -k КЛЮЧ\n", stderr);
        return 1;
    }

    int count = (argc - 3) / 3;
    long long results[count];

    for (int i = 0; i < count; i++) {
        int arg = 1 + i * 3;
        int left, right;
        const char *op = argv[arg + 1];

        if (!read_integer(argv[arg], &left) || !read_integer(argv[arg + 2], &right) ||
            strlen(op) != 1 || !calculate(left, op[0], right, &results[i])) {
            fprintf(stderr, "Ошибка в выражении %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Результат %d: %lld\n", i + 1, results[i]);
    }

    print_text(results, count, key);
    return 0;
}
