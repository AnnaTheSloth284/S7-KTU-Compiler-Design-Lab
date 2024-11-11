#include <stdio.h>
#include <string.h>

#define MAX_STATES 100

// Global variables to store the NFA and closures
int epsilonTransitions[MAX_STATES][MAX_STATES];  // Transition table for epsilon transitions
int closure[MAX_STATES][MAX_STATES];             // Closure table
int numStates;

// Function to perform DFS and find epsilon closure
void dfs(int state, int closureIndex) {
    for (int i = 0; i < numStates; i++) {
        // Check if there is an epsilon transition from 'state' to 'i' and 'i' is not already in the closure
        if (epsilonTransitions[state][i] == 1 && closure[closureIndex][i] == 0) {
            closure[closureIndex][i] = 1;  // Mark state 'i' as part of closure
            dfs(i, closureIndex);          // Continue DFS for state 'i'
        }
    }
}

// Function to calculate epsilon closure for each state
void calculateEpsilonClosures() {
    for (int i = 0; i < numStates; i++) {
        // Initialize the closure with the state itself
        closure[i][i] = 1;
        // Perform DFS to find all states reachable through epsilon transitions
        dfs(i, i);
    }
}

// Function to print the epsilon closures for all states
void printEpsilonClosures() {
    printf("\nEpsilon closures of all states:\n");
    for (int i = 0; i < numStates; i++) {
        printf("Epsilon closure of state %d: { ", i);
        for (int j = 0; j < numStates; j++) {
            if (closure[i][j]) {
                printf("%d ", j);
            }
        }
        printf("}\n");
    }
}

int main() {
    int numTransitions, fromState, toState;
    char transitionSymbol;

    // Read the number of states in the NFA
    printf("Enter the number of states in the NFA: ");
    scanf("%d", &numStates);

    // Initialize epsilon transition and closure tables
    memset(epsilonTransitions, 0, sizeof(epsilonTransitions));
    memset(closure, 0, sizeof(closure));

    // Read the number of transitions
    printf("Enter the number of transitions: ");
    scanf("%d", &numTransitions);

    // Read the transitions, including epsilon ones
    printf("Enter the transitions (from_state to_state symbol), where symbol 'e' denotes epsilon:\n");
    for (int i = 0; i < numTransitions; i++) {
        scanf("%d %d %c", &fromState, &toState, &transitionSymbol);

        if (transitionSymbol == 'e') {
            // Mark this as an epsilon transition
            epsilonTransitions[fromState][toState] = 1;
        } else {
            // Non-epsilon transitions can be stored or ignored for now (not relevant for epsilon closure)
            printf("Non-epsilon transition (%c) is ignored in epsilon closure computation.\n", transitionSymbol);
        }
    }

    // Calculate epsilon closures for all states
    calculateEpsilonClosures();

    // Print the epsilon closures
    printEpsilonClosures();

    return 0;
}
