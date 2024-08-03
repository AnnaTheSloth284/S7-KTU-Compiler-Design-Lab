//
//  intermediate-code-generator.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 03/08/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OP_SIZE 2
#define MAX_ARG_SIZE 5
#define MAX_RESULT_SIZE 10  // Increased size for result buffer

void generate_code(char *op, char *arg1, char *arg2, char *result);

int main() {
    char input[100];
    char op[MAX_OP_SIZE], arg1[MAX_ARG_SIZE], arg2[MAX_ARG_SIZE], result[MAX_RESULT_SIZE];
    char *token;

    printf("Enter the operation (format is either triple or quadruple):\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // Remove trailing newline

    // Tokenize the input
    token = strtok(input, " ");
    
    // Read operation and operands
    if (token != NULL) {
        strcpy(op, token); // Operation (e.g., +, *, -)
        token = strtok(NULL, " ");
        
        if (token != NULL) {
            strcpy(arg1, token); // First operand
            token = strtok(NULL, " ");
            
            if (token != NULL) {
                strcpy(arg2, token); // Second operand
                
                // Check if there's a fourth token for quadruple format
                token = strtok(NULL, " ");
                if (token != NULL) {
                    strncpy(result, token, MAX_RESULT_SIZE - 1);
                    result[MAX_RESULT_SIZE - 1] = '\0'; // Ensure null termination
                } else {
                    // If there is no fourth token, assume triple format
                    strncpy(result, "RESULT", MAX_RESULT_SIZE - 1);
                    result[MAX_RESULT_SIZE - 1] = '\0'; // Ensure null termination
                }
                
                generate_code(op, arg1, arg2, result);
            } else {
                fprintf(stderr, "Invalid input format.\n");
            }
        } else {
            fprintf(stderr, "Invalid input format.\n");
        }
    } else {
        fprintf(stderr, "Invalid input format.\n");
    }

    return EXIT_SUCCESS;
}

void generate_code(char *op, char *arg1, char *arg2, char *result) {
    if (strcmp(op, "+") == 0) {
        printf("\nMOV R0, %s", arg1);
        printf("\nADD R0, %s", arg2);
        printf("\nMOV %s, R0", result);
    } else if (strcmp(op, "*") == 0) {
        printf("\nMOV R0, %s", arg1);
        printf("\nMUL R0, %s", arg2);
        printf("\nMOV %s, R0", result);
    } else if (strcmp(op, "-") == 0) {
        printf("\nMOV R0, %s", arg1);
        printf("\nSUB R0, %s", arg2);
        printf("\nMOV %s, R0", result);
    } else if (strcmp(op, "/") == 0) {
        printf("\nMOV R0, %s", arg1);
        printf("\nDIV R0, %s", arg2);
        printf("\nMOV %s, R0", result);
    } else if (strcmp(op, "=") == 0) {
        printf("\nMOV R0, %s", arg1);
        printf("\nMOV %s, R0", result);
    } else {
        fprintf(stderr, "Unknown operation: %s\n", op);
    }
}
