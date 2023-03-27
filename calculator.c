#include <stdio.h>
#include <stdlib.h>

// forward declaration
int expr(void);

// read a single character from input
int get_next_char(void) {
    return getchar();
}

// read and return an integer from input
int get_next_int(void) {
    int n;
    scanf("%d", &n);
    return n;
}

// parse a factor: either an integer or a parenthesized expression
int factor(void) {
    int c = get_next_char();
    if (c == '(') {
        int result = expr();
        if (get_next_char() != ')') {
            printf("Error: expected ')' after expression\n");
            exit(1);
        }
        return result;
    } else {
        ungetc(c, stdin);
        return get_next_int();
    }
}

// parse a term: a factor followed by zero or more multiplicative operators
int term(void) {
    int result = factor();
    int c;
    while ((c = get_next_char()) == '*' || c == '/') {
        int factor_value = factor();
        if (c == '*') {
            result *= factor_value;
        } else {
            result /= factor_value;
        }
    }
    ungetc(c, stdin);
    return result;
}

// parse an expression: a term followed by zero or more additive operators
int expr(void) {
    int result = term();
    int c;
    while ((c = get_next_char()) == '+' || c == '-') {
        int term_value = term();
        if (c == '+') {
            result += term_value;
        } else {
            result -= term_value;
        }
    }
    ungetc(c, stdin);
    return result;
}

int main(void) {
    int result = expr();
    if (get_next_char() != '\n') {
        printf("Error: expected end of input\n");
        return 1;
    }
    printf("Result: %d\n", result);
    return 0;
}
