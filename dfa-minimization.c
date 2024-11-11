#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26

// Transition table for DFA and grouping table
int dfa[MAX_STATES][MAX_SYMBOLS];
int grouping[MAX_STATES][MAX_STATES];   // Grouping table
int numStates, numSymbols;
int finalStates[MAX_STATES];
int numFinalStates;

void initializeGroups(int groups[]) {
    // Step 3: Initially assign groups: final states in one group, non-final in another
    for (int i = 0; i < numStates; i++) {
        groups[i] = 2;  // Default to non-final group
    }
    for (int i = 0; i < numFinalStates; i++) {
        groups[finalStates[i]] = 1;  // Final states assigned to group 1
    }
}

// Function to check if two states have the same grouping for all symbols
int areSameGroup(int state1, int state2, int groups[]) {
    for (int symbol = 0; symbol < numSymbols; symbol++) {
        int toState1 = dfa[state1][symbol];
        int toState2 = dfa[state2][symbol];
        if (groups[toState1] != groups[toState2]) {
            return 0;  // Not the same group if any transition goes to different groups
        }
    }
    return 1;  // Same group for all symbols
}

// Refine groups until no further distinction is possible
void minimizeDfa() {
    int groups[MAX_STATES];
    int newGroups[MAX_STATES];
    int groupCount = 2;  // Start with 2 groups: final and non-final

    initializeGroups(groups);

    int changed;
    do {
        changed = 0;
        int newGroupCounter = 1;

        // Step 4: Assign new group numbers based on current groupings
        for (int i = 0; i < numStates; i++) {
            newGroups[i] = -1;  // Initialize to unassigned
        }

        for (int i = 0; i < numStates; i++) {
            if (newGroups[i] == -1) {  // Unassigned, create a new group
                newGroups[i] = newGroupCounter;
                for (int j = i + 1; j < numStates; j++) {
                    if (groups[i] == groups[j] && areSameGroup(i, j, groups)) {
                        newGroups[j] = newGroupCounter;  // Assign to the same new group
                    }
                }
                newGroupCounter++;
            }
        }

        // Check if any change happened in grouping
        for (int i = 0; i < numStates; i++) {
            if (groups[i] != newGroups[i]) {
                changed = 1;  // There was a change in grouping
                break;
            }
        }

        // Update groups with new groups for the next iteration
        for (int i = 0; i < numStates; i++) {
            groups[i] = newGroups[i];
        }
        groupCount = newGroupCounter - 1;

    } while (changed);  // Repeat until no changes in group assignments

    // Step 6: Print the minimized DFA groups and transitions
    printf("\nMinimized DFA Transition Table (Grouped States):\n");
    printf("Groups:\n");
    for (int g = 1; g <= groupCount; g++) {
        printf("Group %d: ", g);
        for (int i = 0; i < numStates; i++) {
            if (groups[i] == g) {
                printf("q%d ", i);
            }
        }
        printf("\n");
    }

    printf("\nTransitions for Minimized DFA:\n");
    for (int g = 1; g <= groupCount; g++) {
        int representative = -1;
        for (int i = 0; i < numStates; i++) {
            if (groups[i] == g) {
                representative = i;
                break;
            }
        }
        if (representative != -1) {
            printf("Group %d (represents q%d): ", g, representative);
            for (int symbol = 0; symbol < numSymbols; symbol++) {
                int toState = dfa[representative][symbol];
                printf("On '%c' -> Group %d ", 'a' + symbol, groups[toState]);
            }
            printf("\n");
        }
    }
}

int main() {
    int numTransitions, fromState, toState;
    char transitionSymbol;

    // Read the number of DFA states and symbols
    printf("Enter the number of states in the DFA: ");
    scanf("%d", &numStates);
    printf("Enter the number of symbols: ");
    scanf("%d", &numSymbols);

    // Initialize DFA transition table
    memset(dfa, -1, sizeof(dfa));  // Use -1 to indicate no transition

    // Read DFA transitions
    printf("Enter the number of transitions in the DFA: ");
    scanf("%d", &numTransitions);
    printf("Enter transitions (from_state to_state symbol):\n");
    for (int i = 0; i < numTransitions; i++) {
        scanf("%d %d %c", &fromState, &toState, &transitionSymbol);
        int symbolIndex = transitionSymbol - 'a';
        dfa[fromState][symbolIndex] = toState;
    }

    // Read final states
    printf("Enter the number of final states: ");
    scanf("%d", &numFinalStates);
    printf("Enter final states: ");
    for (int i = 0; i < numFinalStates; i++) {
        scanf("%d", &finalStates[i]);
    }

    // Minimize DFA
    minimizeDfa();

    return 0;
}
