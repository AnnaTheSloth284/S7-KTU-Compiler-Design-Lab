//
//  operator-precedence-4.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 03/08/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OPERATORS 256
#define MAX_INPUT_LEN 100

// Operator precedence table
char precedence_table[MAX_OPERATORS][MAX_OPERATORS];

// Function to initialize the precedence table
void init_precedence_table() {
    // Initialize all cells to -1 (no precedence)
    memset(precedence_table, -1, sizeof(precedence_table));

    // Set higher precedence for operators
    precedence_table['*']['+'] = 1;
    precedence_table['*']['-'] = 1;
    precedence_table['/']['+'] = 1;
    precedence_table['/']['-'] = 1;
    precedence_table['^']['*'] = 1;
    precedence_table['^']['/'] = 1;
    precedence_table['^']['+'] = 1;
    precedence_table['^']['-'] = 1;

    // Set equal precedence for some operators (e.g., left-associative)
    precedence_table['+']['+'] = 0;
    precedence_table['-']['-'] = 0;
    precedence_table['*']['*'] = 0;
    precedence_table['/']['/'] = 0;
    precedence_table['^']['^'] = 0;
}

// Function to compare precedence of two operators
int compare_precedence(char op1, char op2) {
    return precedence_table[(unsigned char)op1][(unsigned char)op2];
}

// Function to check if a character is an operator
int is_operator(char symbol) {
    return strchr("+-*/^()", symbol) != NULL;
}

// Function to print the current state of the stack and input
void print_state(char stack[], int top, char input[], int input_index, char action_char) {
    char stack_str[MAX_INPUT_LEN];
    char input_str[MAX_INPUT_LEN];
    
    // Format stack
    stack_str[0] = '\0';
    for (int i = 0; i <= top; i++) {
        strncat(stack_str, &stack[i], 1);
    }
    
    // Format input
    snprintf(input_str, sizeof(input_str), "%s", input + input_index);

    // Determine action description
    char action[50];
    if (action_char != '\0') {
        snprintf(action, sizeof(action), "SHIFT->%c", action_char);
    } else {
        snprintf(action, sizeof(action), "REDUCE TO E");
    }

    printf("%-20s %-30s %s\n", stack_str, input_str, action);
}


// Function to perform reductions
void perform_reductions(char stack[], int *top) {
    while (*top > 0 && stack[*top] == 'E') {
        (*top)--; // Pop operator
        stack[*top] = 'E'; // Reduce to 'E'
        char input[] = " ";
        char stack_str[MAX_INPUT_LEN];
        char input_str[MAX_INPUT_LEN];
        stack_str[0] = '\0';
        for (int i = 0; i <= *top; i++) {
            strncat(stack_str, &stack[i], 1);
        }
        // Format input
        snprintf(input_str, sizeof(input_str), "%s", input + 0);
        printf("%-20s %-30s REDUCE TO E\n", stack_str, input_str);
        //print_state(stack, *top, "", 0, "REDUCE TO E");
    }
}

// Function to perform operator precedence parsing
void operator_precedence_parsing(char input[]) {
    int i = 0, top = -1;
    char stack[MAX_INPUT_LEN];
    stack[++top] = '$';

    // Add '$' at the end of input string
    strcat(input, "$");

    printf("STACK                INPUT                           ACTION\n");
    printf("-------------------------------------------------------------------\n");

    while (input[i] != '$') {
        if (isalpha(input[i])) {
            // Operand (single letter), push to stack as 'E'
            stack[++top] = 'E';
            print_state(stack, top, input, i + 1, input[i]); // Pass operand
            i++; // Move past operand
        } else {
            // Operator or parentheses
            if (input[i] == '|') {
                i++;
            }
            else if (input[i] == '(') {
                stack[++top] = input[i];
                i++;
                print_state(stack, top, input, i, '('); // Pass '('
            } else if (input[i] == ')') {
                while (top > 0 && stack[top] != '(') {
                    if (top < 0) {
                        printf("Error: Mismatched parentheses\n");
                        return;
                    }
                    top--; // Pop until '('
                    perform_reductions(stack, &top); // Perform reductions
                }
                if (top > 0 && stack[top] == '(') {
                    top--; // Pop '('
                } else {
                    //printf("Error: Mismatched parentheses\n");
                    return;
                }
                perform_reductions(stack, &top); // Perform reductions
                print_state(stack, top, input, i, '\0'); // Reduce
                i++;
            } else if (is_operator(input[i])) {
                while (top > 0 && is_operator(stack[top]) &&
                       compare_precedence(stack[top], input[i]) >= 0) {
                    // Reduce
                    top--; // Pop operator
                    stack[top] = 'E'; // Reduce to 'E'
                    print_state(stack, top, input, i, '\0'); // Reduce
                }
                // Shift
                stack[++top] = input[i];
                print_state(stack, top, input, i + 1, input[i]); // Pass operator
                i++;
            } else {
                printf("Error: Invalid character '%c'\n", input[i]);
                return;
            }
        }
        perform_reductions(stack, &top); // Check for reductions after each shift
    }

    // Final reduction
    while (top > 0 && stack[top] != '$') {
        // Reduce
        top--; // Pop operator
        stack[top] = 'E'; // Reduce to 'E'
        print_state(stack, top, input, i, '\0'); // Reduce
    }
}

int main() {
    //char input[MAX_INPUT_LEN];

    init_precedence_table();
    char input[] = "E+E|E-E|E*E|E|E^E|(E)";
    //printf("Enter the input string: ");
    //scanf("%s", input);

    operator_precedence_parsing(input);

    return 0;
}
