#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26

// Global structures for NFA and DFA transitions
int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];   // NFA transition table
int dfa[MAX_STATES][MAX_SYMBOLS];               // DFA transition table
int deltas[MAX_STATES][MAX_SYMBOLS];            // Track NFA transitions in DFA formation
int dfaStates[MAX_STATES][MAX_STATES];          // DFA states as a combination of NFA states
int dfaStateCount = 0;                          // Count of DFA states
int numStates, numSymbols;

// Function to check if a state combination exists in DFA
int findDfaState(int stateSet[]) {
    for (int i = 0; i < dfaStateCount; i++) {
        int match = 1;
        for (int j = 0; j < numStates; j++) {
            if (dfaStates[i][j] != stateSet[j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;  // Existing DFA state found
    }
    return -1;  // New DFA state
}

// Function to add a new DFA state from a set of NFA states
int addDfaState(int stateSet[]) {
    for (int i = 0; i < numStates; i++) {
        dfaStates[dfaStateCount][i] = stateSet[i];
    }
    return dfaStateCount++;  // Increment DFA state count
}

// Function to calculate DFA from NFA
void convertNfaToDfa() {
    int stateSet[MAX_STATES] = {0};
    stateSet[0] = 1;  // Initial DFA state is the NFA start state

    int initialDfaState = addDfaState(stateSet);  // Add initial state to DFA

    for (int currentDfaState = 0; currentDfaState < dfaStateCount; currentDfaState++) {
        for (int symbol = 0; symbol < numSymbols; symbol++) {
            int newStateSet[MAX_STATES] = {0};  // New state set for this symbol

            // Step 3: Calculate the union of transitions for current DFA state and symbol
            for (int i = 0; i < numStates; i++) {
                if (dfaStates[currentDfaState][i]) {
                    for (int j = 0; j < numStates; j++) {
                        if (nfa[i][symbol][j]) {
                            newStateSet[j] = 1;  // Include state j in the new DFA state set
                            deltas[i][symbol] = 1;  // Mark transition
                        }
                    }
                }
            }

            // Step 4: Check if this state set is already in the DFA
            int existingStateIndex = findDfaState(newStateSet);
            if (existingStateIndex == -1) {
                existingStateIndex = addDfaState(newStateSet);  // Add new DFA state
            }
            dfa[currentDfaState][symbol] = existingStateIndex;  // Record DFA transition
        }
    }
}

// Function to print the DFA transition table
void printDfaTable() {
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfaStateCount; i++) {
        printf("DFA state %d: ", i);
        for (int j = 0; j < numSymbols; j++) {
            printf("On '%c' -> DFA state %d ", 'a' + j, dfa[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numTransitions, fromState, toState;
    char transitionSymbol;

    // Read the number of NFA states and symbols (excluding epsilon)
    printf("Enter the number of states in the NFA: ");
    scanf("%d", &numStates);
    printf("Enter the number of symbols (excluding epsilon): ");
    scanf("%d", &numSymbols);

    // Initialize NFA and DFA tables
    memset(nfa, 0, sizeof(nfa));
    memset(dfa, -1, sizeof(dfa));       // Use -1 to indicate no transition
    memset(deltas, 0, sizeof(deltas));  // Track transitions for DFA construction
    memset(dfaStates, 0, sizeof(dfaStates));

    // Read NFA transitions
    printf("Enter the number of transitions in the NFA: ");
    scanf("%d", &numTransitions);
    printf("Enter transitions (from_state to_state symbol):\n");
    for (int i = 0; i < numTransitions; i++) {
        scanf("%d %d %c", &fromState, &toState, &transitionSymbol);
        int symbolIndex = transitionSymbol - 'a';
        nfa[fromState][symbolIndex][toState] = 1;
    }

    // Convert NFA to DFA
    convertNfaToDfa();

    // Print the DFA transition table
    printDfaTable();

    return 0;
}
