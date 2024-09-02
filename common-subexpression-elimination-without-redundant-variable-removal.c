//
//  cd-expt7.c
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
    char result[MAX_EXPR_LEN];
} Expression;

void optimize_cse(Expression *exprs, int n) {
    char temp[MAX_EXPR_LEN];
    int temp_var_counter = 1;
    int output_counter = 0;
    int found;

    // New array to store unique expressions
    Expression unique_exprs[MAX_EXPR];

    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < output_counter; j++) {
            if (strcmp(exprs[i].rhs, unique_exprs[j].rhs) == 0) {
                // Reuse the result of the common subexpression
                strcpy(exprs[i].result, unique_exprs[j].result);
                found = 1;
                break;
            }
        }
        if (!found) {
            // If no common subexpression found, use a new temporary variable
            snprintf(temp, MAX_EXPR_LEN, "t%d", temp_var_counter++);
            strcpy(exprs[i].result, temp);
            strcpy(unique_exprs[output_counter].lhs, exprs[i].lhs);
            strcpy(unique_exprs[output_counter].rhs, exprs[i].rhs);
            strcpy(unique_exprs[output_counter].result, temp);
            output_counter++;
        }
    }

    // Now print the optimized expressions
    printf("\nOptimized Code:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", exprs[i].lhs, exprs[i].rhs);
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
            exprs[i].result[0] = '\0';  // Initialize result as empty string
        } else {
            // Handle the case where there is no '=' in the input (though unlikely in assignments)
            strcpy(exprs[i].lhs, "");
            strcpy(exprs[i].rhs, input);
            exprs[i].result[0] = '\0';
        }
    }

    // Perform Common Subexpression Elimination
    optimize_cse(exprs, n);

    return 0;
}
