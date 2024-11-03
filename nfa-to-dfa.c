#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_INPUT 10
#define MAX_DFA_STATES 256 // To handle combinations of NFA states

// Structure to represent an NFA
typedef struct {
    int nStates;                   // Number of states in NFA
    int nSymbols;                  // Number of input symbols
    int transition[MAX_STATES][MAX_INPUT][MAX_STATES]; // Transitions
    int accepting[MAX_STATES];      // Accepting states
} NFA;

// Structure to represent a DFA
typedef struct {
    int nStates;                   // Number of states in DFA
    int nSymbols;                  // Number of input symbols
    int transition[MAX_DFA_STATES][MAX_INPUT]; // Transitions
    int accepting[MAX_DFA_STATES]; // Accepting states
    int stateComposition[MAX_DFA_STATES][MAX_STATES]; // Store composition of each DFA state
} DFA;

// Function to initialize NFA
void initNFA(NFA *nfa, int nStates, int nSymbols) {
    nfa->nStates = nStates;
    nfa->nSymbols = nSymbols;
    memset(nfa->transition, 0, sizeof(nfa->transition));
    memset(nfa->accepting, 0, sizeof(nfa->accepting));
}

// Function to add a transition to NFA
void addTransition(NFA *nfa, int fromState, int symbol, int toState) {
    nfa->transition[fromState][symbol][toState] = 1;
}

// Function to set accepting state in NFA
void setAcceptingState(NFA *nfa, int state) {
    nfa->accepting[state] = 1;
}

// Function to convert NFA to DFA
void convertNFAtoDFA(NFA *nfa, DFA *dfa) {
    int stateMap[MAX_DFA_STATES] = {0}; // Map to check existing DFA states
    dfa->nStates = 0;
    dfa->nSymbols = nfa->nSymbols;

    // Initial DFA state from the start NFA state (assuming NFA starts at state 0)
    int initialState[MAX_STATES] = {0};
    initialState[0] = 1; // NFA state 0 is the starting state

    // Store initial state in DFA
    int dfaStateIndex = dfa->nStates++;
    memcpy(dfa->stateComposition[dfaStateIndex], initialState, sizeof(initialState));

    // Traverse the NFA to create DFA states
    for (int i = 0; i < dfa->nStates; i++) {
        for (int j = 0; j < nfa->nSymbols; j++) {
            int newState[MAX_STATES] = {0};

            // Compute the next states for the current DFA state
            for (int k = 0; k < MAX_STATES; k++) {
                if (dfa->stateComposition[i][k]) {
                    for (int l = 0; l < nfa->nStates; l++) {
                        if (nfa->transition[k][j][l]) {
                            newState[l] = 1; // Mark this NFA state as reachable
                        }
                    }
                }
            }

            // Check if the new state already exists in DFA
            int existingDFAState = -1;
            for (int k = 0; k < dfa->nStates; k++) {
                if (memcmp(newState, dfa->stateComposition[k], sizeof(newState)) == 0) {
                    existingDFAState = k;
                    break;
                }
            }

            // If it doesn't exist, create a new DFA state
            if (existingDFAState == -1) {
                existingDFAState = dfa->nStates++;
                memcpy(dfa->stateComposition[existingDFAState], newState, sizeof(newState));
            }

            // Add transition in DFA
            dfa->transition[i][j] = existingDFAState;

            // Mark accepting states in DFA
            if (newState[nfa->nStates - 1]) { // Check if any NFA accepting state is reached
                dfa->accepting[existingDFAState] = 1;
            }
        }
    }
}

// Function to display DFA transitions and state compositions
void displayDFA(DFA *dfa) {
    printf("DFA States: %d\n", dfa->nStates);
    printf("DFA Transitions:\n");
    for (int i = 0; i < dfa->nStates; i++) {
        printf("State %d (Composition: { ", i);
        for (int k = 0; k < MAX_STATES; k++) {
            if (dfa->stateComposition[i][k]) {
                printf("%d ", k);
            }
        }
        printf("})\n");
        for (int j = 0; j < dfa->nSymbols; j++) {
            printf("    --(%d)-> State %d\n", j, dfa->transition[i][j]);
        }
    }
    printf("Accepting States: ");
    for (int i = 0; i < dfa->nStates; i++) {
        if (dfa->accepting[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    NFA nfa;
    DFA dfa;

    // Input number of states and input symbols
    printf("Enter number of states in NFA: ");
    scanf("%d", &nfa.nStates);
    printf("Enter number of input symbols: ");
    scanf("%d", &nfa.nSymbols);

    // Initialize NFA
    initNFA(&nfa, nfa.nStates, nfa.nSymbols);

    // Input transitions
    int nTransitions;
    printf("Enter number of transitions: ");
    scanf("%d", &nTransitions);
    for (int i = 0; i < nTransitions; i++) {
        int fromState, symbol, toState;
        printf("Enter transition (fromState symbol toState): ");
        scanf("%d %d %d", &fromState, &symbol, &toState);
        addTransition(&nfa, fromState, symbol, toState);
    }

    // Input accepting states
    int nAccepting;
    printf("Enter number of accepting states: ");
    scanf("%d", &nAccepting);
    for (int i = 0; i < nAccepting; i++) {
        int state;
        printf("Enter accepting state: ");
        scanf("%d", &state);
        setAcceptingState(&nfa, state);
    }

    // Convert NFA to DFA
    convertNFAtoDFA(&nfa, &dfa);

    // Display the DFA
    displayDFA(&dfa);

    return 0;
}
