#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26  // Assuming 26 symbols (a-z) excluding epsilon

// Global variables to store the epsilon-NFA and closures
int epsilonTransitions[MAX_STATES][MAX_STATES];  // Transition table for epsilon transitions
int closure[MAX_STATES][MAX_STATES];             // Closure table
int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];    // NFA transitions excluding epsilon
int numStates, numSymbols;

// Function to perform DFS and find epsilon closure (used by calculateEpsilonClosures)
void dfs(int state, int closureIndex) {
    for (int i = 0; i < numStates; i++) {
        if (epsilonTransitions[state][i] == 1 && closure[closureIndex][i] == 0) {
            closure[closureIndex][i] = 1;
            dfs(i, closureIndex);
        }
    }
}

// Function to calculate epsilon closure for each state
void calculateEpsilonClosures() {
    for (int i = 0; i < numStates; i++) {
        closure[i][i] = 1;
        dfs(i, i);
    }
}

// Function to find union of states for a given state and symbol, considering epsilon closure
void calculateNfaTransitions() {
    for (int state = 0; state < numStates; state++) {
        // Step 3.1: Get the epsilon closure for the current state (temporary array)
        int stateClosure[MAX_STATES] = {0};
        for (int i = 0; i < numStates; i++) {
            if (closure[state][i]) {
                stateClosure[i] = 1;
            }
        }

        // Step 3.2: For each symbol (excluding epsilon), compute the union of reachable states
        for (int symbol = 0; symbol < numSymbols; symbol++) {
            int unionClosure[MAX_STATES] = {0};  // Temporary closure for union of transitions

            // Find all transitions from each state in stateClosure using the symbol
            for (int i = 0; i < numStates; i++) {
                if (stateClosure[i]) {
                    for (int k = 0; k < numStates; k++) {
                        if (nfa[i][symbol][k]) {
                            unionClosure[k] = 1;  // Add reachable state to unionClosure
                        }
                    }
                }
            }

            // Step 3.3: Compute epsilon closure of the union and store in nfa[state][symbol]
            for (int i = 0; i < numStates; i++) {
                if (unionClosure[i]) {
                    for (int j = 0; j < numStates; j++) {
                        if (closure[i][j]) {
                            nfa[state][symbol][j] = 1;
                        }
                    }
                }
            }
        }
    }
}

// Function to print the NFA table
void printNfaTable() {
    printf("\nNFA transitions (excluding epsilon):\n");
    for (int state = 0; state < numStates; state++) {
        for (int symbol = 0; symbol < numSymbols; symbol++) {
            printf("NFA transition from state %d on symbol '%c': { ", state, 'a' + symbol);
            for (int nextState = 0; nextState < numStates; nextState++) {
                if (nfa[state][symbol][nextState]) {
                    printf("%d ", nextState);
                }
            }
            printf("}\n");
        }
    }
}

int main() {
    int numTransitions, fromState, toState;
    char transitionSymbol;

    // Read the number of states and symbols (excluding epsilon)
    printf("Enter the number of states in the epsilon-NFA: ");
    scanf("%d", &numStates);
    printf("Enter the number of symbols (excluding epsilon): ");
    scanf("%d", &numSymbols);

    // Initialize tables
    memset(epsilonTransitions, 0, sizeof(epsilonTransitions));
    memset(closure, 0, sizeof(closure));
    memset(nfa, 0, sizeof(nfa));

    // Read transitions
    printf("Enter the number of transitions: ");
    scanf("%d", &numTransitions);
    printf("Enter transitions (from_state to_state symbol), 'e' for epsilon:\n");
    for (int i = 0; i < numTransitions; i++) {
        scanf("%d %d %c", &fromState, &toState, &transitionSymbol);
        if (transitionSymbol == 'e') {
            epsilonTransitions[fromState][toState] = 1;
        } else {
            int symbolIndex = transitionSymbol - 'a';
            nfa[fromState][symbolIndex][toState] = 1;
        }
    }

    // Calculate epsilon closures
    calculateEpsilonClosures();

    // Calculate NFA transitions
    calculateNfaTransitions();

    // Print the resulting NFA table
    printNfaTable();

    return 0;
}
