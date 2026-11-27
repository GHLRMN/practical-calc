#include <stdio.h>

#include "calc.h"

int calculate(int left, char operation, int right, long long *result)
{
    switch (operation) {
    case '+':
        *result = (long long)left + right;
        return 1;
    case '-':
        *result = (long long)left - right;
        return 1;
    case '*':
        *result = (long long)left * right;
        return 1;
    case '%':
        if (right == 0) {
            return 0;
        }
        *result = (long long)left % right;
        return 1;
    default:
        return 0;
    }
}

void print_text(const long long *results, int count, int key)
{
    for (int i = 0; i < count; i++) {
        putchar((unsigned char)(results[i] - key));
    }
    putchar('\n');
}
