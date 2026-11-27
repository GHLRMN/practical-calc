#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"

static int read_integer(const char *text, int *number)
{
    char *end;

    if (isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    long value = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE ||
        value < INT_MIN || value > INT_MAX) {
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
        fputs("Usage: practical-calc NUMBER OP NUMBER [...] -k KEY\n", stderr);
        return 1;
    }

    int count = (argc - 3) / 3;
    long long *results = calloc((size_t)count, sizeof(*results));
    if (results == NULL) {
        fputs("Not enough memory\n", stderr);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        int position = 1 + 3 * i;
        const char *operation = argv[position + 1];
        int left, right;

        if (!read_integer(argv[position], &left) ||
            !read_integer(argv[position + 2], &right) ||
            strlen(operation) != 1 ||
            !calculate(left, operation[0], right, &results[i])) {
            fprintf(stderr, "Invalid expression %d\n", i + 1);
            free(results);
            return 1;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d: %lld\n", i + 1, results[i]);
    }
    print_text(results, count, key);

    free(results);
    return 0;
}
