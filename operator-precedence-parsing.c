//
//  operator-precedence-parser.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 29/07/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OPERATORS 100
#define MAX_INPUT_LEN 100

// Operator precedence table
char precedence_table[MAX_OPERATORS][MAX_OPERATORS];

// Function to initialize the precedence table (replace with actual values)
void def_precedence_table() {
    // Assuming operators are '+', '-', '*', '/', '^'
    // You can add more operators as needed

    // Initialize all cells to 0 (lower precedence)
    memset(precedence_table, 0, sizeof(precedence_table));

    // Set higher precedence for operators
    precedence_table['*']['+'] = 2;
    precedence_table['*']['-'] = 2;
    precedence_table['/']['+'] = 2;
    precedence_table['/']['-'] = 2;
    precedence_table['^']['*'] = 2;
    precedence_table['^']['/'] = 2;
    precedence_table['^']['+'] = 2;
    precedence_table['^']['-'] = 2;

    // Set equal precedence for some operators (e.g., left-associative)
    precedence_table['+']['+'] = 1;
    precedence_table['-']['-'] = 1;
    precedence_table['*']['*'] = 1;
    precedence_table['/']['/'] = 1;
}

// Function to check precedence of two operators
int compare_precedence(char op1, char op2) {
    // ... compare precedence based on the precedence table ...
    return precedence_table[op1][op2];
}

// Function to perform operator precedence parsing
void operator_precedence_parsing(char input[]) {
    int i, top = -1;
    char stack[MAX_INPUT_LEN], output[MAX_INPUT_LEN];
    int output_index = 0;
    int accepted = 1; // Assume accepted initially

    // Push '$' onto the stack
    stack[++top] = '$';

    // Add '$' at the end of input string
    strcat(input, "$");

    i = 0;
    while (input[i] != '$') {
        if (isalpha(input[i])) {
            // Operand, append to output
            output[output_index++] = input[i];
            i++;
        } else {
            // Operator
            if (compare_precedence(stack[top], input[i]) < 0) {
                // Shift
                stack[++top] = input[i];
                i++;
            } else {
                // Reduce
                while (compare_precedence(stack[top], input[i]) >= 0) {
                    output[output_index++] = stack[top];
                    top--;
                }
                stack[++top] = input[i];
                i++;
            }
        }
    }

    // Pop remaining operators
    while (stack[top] != '$') {
        output[output_index++] = stack[top];
        top--;
    }
    output[output_index] = '\0';

    // Check for acceptance
    if (top != 0 || output_index == 0) {
        accepted = 0;
    }

    printf("Parsed string: %s\n", output);
    if (accepted) {
        printf("Input string accepted\n");
    } else {
        printf("Input string rejected\n");
    }
}

int main() {
    char input[MAX_INPUT_LEN];

    def_precedence_table();

    printf("Enter the input string: ");
    scanf("%s", input);

    operator_precedence_parsing(input);

    return 0;
}
