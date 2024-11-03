#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2

typedef struct {
    int state;  // current state
    int next_state;  // next state
    char symbol;  // transition symbol (0 for epsilon)
} Transition;

typedef struct {
    int transitions[MAX_STATES][ALPHABET_SIZE][MAX_STATES];  // transitions for NFA
    int state_count;  // number of states
} NFA;

Transition epsilon_transitions[MAX_STATES][MAX_STATES];  // ε-NFA transitions
int epsilon_count[MAX_STATES];  // count of epsilon transitions for each state

void add_epsilon_transition(int from, int to) {
    epsilon_transitions[from][epsilon_count[from]].next_state = to;
    epsilon_transitions[from][epsilon_count[from]].state = from;
    epsilon_transitions[from][epsilon_count[from]].symbol = 0; // 0 for epsilon
    epsilon_count[from]++;
}

void convert_epsilon_nfa_to_nfa(int state_count, NFA* nfa) {
    for (int state = 0; state < state_count; state++) {
        // For each state, process epsilon transitions
        for (int i = 0; i < epsilon_count[state]; i++) {
            int epsilon_target = epsilon_transitions[state][i].next_state;

            // Add the epsilon transitions to the NFA transitions
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (nfa->transitions[epsilon_target][j]) {
                    for (int k = 0; k < MAX_STATES; k++) {
                        if (nfa->transitions[epsilon_target][j][k]) {
                            nfa->transitions[state][j][k] = 1; // mark as reachable
                        }
                    }
                }
            }
        }
    }
}

void print_nfa(NFA* nfa) {
    printf("NFA transitions:\n");
    for (int i = 0; i < nfa->state_count; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("State %d, Symbol %d: ", i, j);
            for (int k = 0; k < MAX_STATES; k++) {
                if (nfa->transitions[i][j][k]) {
                    printf("%d ", k);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    NFA nfa = {0};
    int state_count, epsilon_transitions_count;

    // User input for number of states
    printf("Enter the number of states: ");
    scanf("%d", &state_count);
    nfa.state_count = state_count;

    // User input for epsilon transitions
    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &epsilon_transitions_count);

    printf("Enter epsilon transitions (format: from to):\n");
    for (int i = 0; i < epsilon_transitions_count; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        add_epsilon_transition(from, to);
    }

    // User input for other transitions
    int other_transitions_count;
    printf("Enter the number of other transitions: ");
    scanf("%d", &other_transitions_count);

    printf("Enter transitions (format: from symbol to):\n");
    for (int i = 0; i < other_transitions_count; i++) {
        int from, to;
        char symbol;
        scanf("%d %c %d", &from, &symbol, &to);
        int symbol_index = symbol - 'a'; // Assuming 'a' and 'b' are the only symbols
        nfa.transitions[from][symbol_index][to] = 1; // Mark transition in the NFA
    }

    // Convert ε-NFA to NFA
    convert_epsilon_nfa_to_nfa(state_count, &nfa);

    // Print the resulting NFA
    print_nfa(&nfa);

    return 0;
}
