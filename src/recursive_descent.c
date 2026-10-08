/**
 * ============================================================================
 * Course: Compiler Design Laboratory (BCSE306L)
 * Experiment 4: LL(1) Recursive Descent Parser
 * Author: Shrri Dharshan D R (Reg No: 23BPS1090)
 * Slot: L23+L24
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input_str[128];
int cursor = 0;
int error_flag = 0;
char error_msg[128] = "";

/* Function prototypes corresponding to grammar non-terminals */
void E(void);
void E_prime(void);
void T(void);
void T_prime(void);
void F(void);

void skip_spaces(void) {
    while (input_str[cursor] && isspace((unsigned char)input_str[cursor])) {
        cursor++;
    }
}

/**
 * Grammar Productions:
 * E  -> T E'
 * E' -> '+' T E' | '-' T E' | epsilon
 * T  -> F T'
 * T' -> '*' F T' | '/' F T' | epsilon
 * F  -> '(' E ')' | id | num
 */

void E(void) {
    T();
    E_prime();
}

void E_prime(void) {
    skip_spaces();
    if (input_str[cursor] == '+') {
        cursor++;
        T();
        E_prime();
    } else if (input_str[cursor] == '-') {
        cursor++;
        T();
        E_prime();
    }
    /* epsilon transition */
}

void T(void) {
    F();
    T_prime();
}

void T_prime(void) {
    skip_spaces();
    if (input_str[cursor] == '*') {
        cursor++;
        F();
        T_prime();
    } else if (input_str[cursor] == '/') {
        cursor++;
        F();
        T_prime();
    }
    /* epsilon transition */
}

void F(void) {
    skip_spaces();
    if (input_str[cursor] == '(') {
        cursor++;
        E();
        skip_spaces();
        if (input_str[cursor] == ')') {
            cursor++;
        } else {
            error_flag = 1;
            strcpy(error_msg, "Syntax Error in F: Missing closing parenthesis ')'");
        }
    } else if (isalnum((unsigned char)input_str[cursor]) || input_str[cursor] == '_') {
        /* Consume alphanumeric identifier or number */
        while (isalnum((unsigned char)input_str[cursor]) || input_str[cursor] == '_') {
            cursor++;
        }
    } else {
        error_flag = 1;
        snprintf(error_msg, sizeof(error_msg), 
                 "Syntax Error in F: Unexpected symbol '%c' at index %d", 
                 input_str[cursor], cursor);
    }
}

void test_expression(const char *expr) {
    strncpy(input_str, expr, sizeof(input_str) - 1);
    input_str[sizeof(input_str) - 1] = '\0';
    cursor = 0;
    error_flag = 0;
    error_msg[0] = '\0';

    printf("Testing Input: \"%s\"\n", expr);
    E();
    skip_spaces();

    if (cursor == (int)strlen(input_str) && error_flag == 0) {
        printf("  Result: [SUCCESS] Parsing Successful! Valid LL(1) Expression.\n\n");
    } else {
        if (error_flag) {
            printf("  Result: [FAILED] %s\n\n", error_msg);
        } else {
            printf("  Result: [FAILED] Syntax Error: Unconsumed trailing tokens '%s'\n\n", 
                   input_str + cursor);
        }
    }
}

int main(void) {
    printf("============================================================\n");
    printf("   EXPERIMENT 4: LL(1) RECURSIVE DESCENT PARSER (RDP)       \n");
    printf("============================================================\n\n");

    const char *test_cases[] = {
        "a + b * c",
        "(a + b) * (c - d)",
        "x * y + z / 2",
        "a * + b",          /* Syntax error in F */
        "(a + b * c",       /* Missing ')' */
        "a + b)",           /* Unexpected closing ')' */
        "var1 + 42 * count"
    };

    int total_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (int i = 0; i < total_cases; i++) {
        test_expression(test_cases[i]);
    }

    return 0;
}
