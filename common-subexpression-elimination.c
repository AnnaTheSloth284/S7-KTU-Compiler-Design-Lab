//
//  cd-expt7-redundant-elimination.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 02/09/24.
//

#include <stdio.h>
#include <string.h>

#define MAX_EXPR_LEN 100
#define MAX_EXPR 50

typedef struct {
    char lhs[MAX_EXPR_LEN];
    char rhs[MAX_EXPR_LEN];
} Expression;

void optimize_cse(Expression *exprs, int n) {
    char temp[MAX_EXPR_LEN];
    int temp_var_counter = 1;
    int optimized_counter = 0;
    int found;

    // New array to store optimized expressions
    Expression optimized_exprs[MAX_EXPR];

    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < optimized_counter; j++) {
            if (strcmp(exprs[i].rhs, optimized_exprs[j].rhs) == 0) {
                // If a common subexpression is found, skip adding it again
                // Replace the LHS of the current expression with the existing optimized LHS
                for (int k = 0; k < n; k++) {
                    if (strcmp(exprs[k].rhs, exprs[i].lhs) == 0) {
                        strcpy(exprs[k].rhs, optimized_exprs[j].lhs);
                    }
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            // If no common subexpression found, add the expression to the optimized list
            strcpy(optimized_exprs[optimized_counter].lhs, exprs[i].lhs);
            strcpy(optimized_exprs[optimized_counter].rhs, exprs[i].rhs);
            optimized_counter++;
        }
    }

    // Now print the optimized expressions
    printf("\nOptimized Code:\n");
    for (int i = 0; i < optimized_counter; i++) {
        printf("%s = %s;\n", optimized_exprs[i].lhs, optimized_exprs[i].rhs);
    }
}

int main() {
    Expression exprs[MAX_EXPR];
    int n;

    printf("Enter the number of expressions: ");
    scanf("%d", &n);

    // Input the expressions from the user
    for (int i = 0; i < n; i++) {
        char input[MAX_EXPR_LEN];
        printf("Enter expression %d: ", i + 1);
        scanf(" %[^\n]s", input);  // Read the entire line, including spaces

        // Split the input into lhs and rhs
        char *equal_sign = strchr(input, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';  // Split the string into lhs and rhs
            strcpy(exprs[i].lhs, input);
            strcpy(exprs[i].rhs, equal_sign + 1);
        }
    }

    // Perform Common Subexpression Elimination
    optimize_cse(exprs, n);

    return 0;
}
