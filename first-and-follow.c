//
//  first-and-follow.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 04/08/24.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_PRODUCTIONS 20
#define MAX_SYMBOLS 20
#define MAX_RHS 10

int num_of_productions;
char production_set[MAX_PRODUCTIONS][MAX_SYMBOLS];
char FIRST_sets[MAX_SYMBOLS][MAX_SYMBOLS];
char FOLLOW_sets[MAX_SYMBOLS][MAX_SYMBOLS];

void compute_FIRST(char result[], char c);
void compute_FOLLOW(char c);
void add_to_set(char set[], char c);
void merge_sets(char dest[], char src[]);
int set_contains(char set[], char c);
void split_productions(char lhs, char *rhs[], int *num_rhs);

int main() {
    int i, j;
    char choice;
    char c;

    printf("Enter the number of productions: ");
    scanf("%d", &num_of_productions);
    puts("Enter the production strings like \"E=E+T\" and epsilon as #");

    for (i = 0; i < num_of_productions; ++i) {
        printf("Enter production number %d: ", i + 1);
        scanf("%s", production_set[i]);
    }

    // Initialize FIRST and FOLLOW sets
    for (i = 0; i < MAX_SYMBOLS; ++i) {
        FIRST_sets[i][0] = '\0';
        FOLLOW_sets[i][0] = '\0';
    }

    // Compute FIRST sets for all non-terminals
    for (i = 0; i < num_of_productions; ++i) {
        char non_terminal = production_set[i][0];
        compute_FIRST(FIRST_sets[non_terminal], non_terminal);
    }

    // Compute FOLLOW sets for all non-terminals
    for (i = 0; i < num_of_productions; ++i) {
        char non_terminal = production_set[i][0];
        compute_FOLLOW(non_terminal);
    }

    // Display FIRST sets
    printf("\nFIRST sets:\n");
    for (i = 0; i < num_of_productions; ++i) {
        char non_terminal = production_set[i][0];
        printf("FIRST(%c) = { ", non_terminal);
        for (j = 0; j < strlen(FIRST_sets[non_terminal]); ++j) {
            printf("%c ", FIRST_sets[non_terminal][j]);
        }
        printf("}\n");
    }

    // Display FOLLOW sets
    printf("\nFOLLOW sets:\n");
    for (i = 0; i < num_of_productions; ++i) {
        char non_terminal = production_set[i][0];
        printf("FOLLOW(%c) = { ", non_terminal);
        for (j = 0; j < strlen(FOLLOW_sets[non_terminal]); ++j) {
            printf("%c ", FOLLOW_sets[non_terminal][j]);
        }
        printf("}\n");
    }

    return 0;
}

void compute_FIRST(char result[], char c) {
    int i, j, k;
    char sub_result[MAX_SYMBOLS];
    char *rhs[MAX_RHS];
    int num_rhs;
    int found_epsilon;

    sub_result[0] = '\0';

    if (!isupper(c)) {
        add_to_set(result, c);
        return;
    }

    // Initialize FIRST set for the current non-terminal
    result[0] = '\0';

    // Split productions for the current non-terminal
    split_productions(c, rhs, &num_rhs);

    for (i = 0; i < num_rhs; ++i) {
        j = 0;
        found_epsilon = 1;

        while (rhs[i][j] != '\0') {
            compute_FIRST(sub_result, rhs[i][j]);

            merge_sets(result, sub_result);

            if (set_contains(sub_result, '#')) {
                found_epsilon = 0;
            } else {
                found_epsilon = 1;
                break;
            }
            ++j;
        }

        if (rhs[i][j] == '\0' && found_epsilon) {
            add_to_set(result, '#');
        }

        // Free allocated memory for rhs
        free(rhs[i]);
    }
}

void compute_FOLLOW(char c) {
    int i, j;
    if (production_set[0][0] == c) {
        add_to_set(FOLLOW_sets[c], '$');
    }

    for (i = 0; i < num_of_productions; ++i) {
        char lhs = production_set[i][0];
        for (j = 2; j < strlen(production_set[i]); ++j) {
            if (production_set[i][j] == c) {
                // Process the symbol after 'c'
                if (production_set[i][j + 1] != '\0') {
                    char temp[MAX_SYMBOLS];
                    compute_FIRST(temp, production_set[i][j + 1]);
                    for (int k = 0; k < strlen(temp); ++k) {
                        if (temp[k] != '#') {
                            add_to_set(FOLLOW_sets[c], temp[k]);
                        }
                    }
                }
                // Process FOLLOW set for the non-terminal on the LHS
                if (production_set[i][j + 1] == '\0' && lhs != c) {
                    compute_FOLLOW(lhs);
                    merge_sets(FOLLOW_sets[c], FOLLOW_sets[lhs]);
                }
            }
        }
    }
}

void add_to_set(char set[], char c) {
    if (!set_contains(set, c) && c != '|') {  // Exclude '|' from sets
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void merge_sets(char dest[], char src[]) {
    int i;
    for (i = 0; i < strlen(src); ++i) {
        if (src[i] != '|') {  // Exclude '|' from sets
            add_to_set(dest, src[i]);
        }
    }
}

int set_contains(char set[], char c) {
    int i;
    for (i = 0; i < strlen(set); ++i) {
        if (set[i] == c) {
            return 1;
        }
    }
    return 0;
}

void split_productions(char lhs, char *rhs[], int *num_rhs) {
    int i, j;
    char buffer[MAX_SYMBOLS];
    *num_rhs = 0;

    for (i = 0; i < num_of_productions; ++i) {
        if (production_set[i][0] == lhs) {
            j = 2;
            while (production_set[i][j] != '\0') {
                int k = 0;
                while (production_set[i][j] != '|' && production_set[i][j] != '\0') {
                    buffer[k++] = production_set[i][j++];
                }
                buffer[k] = '\0';
                if (k > 0) { // Only add non-empty productions
                    rhs[*num_rhs] = strdup(buffer);
                    (*num_rhs)++;
                }
                if (production_set[i][j] == '|') {
                    j++;
                }
            }
        }
    }
}
