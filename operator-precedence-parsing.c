//
//  operator-precedence-4.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 03/08/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OPERATORS 100
#define MAX_INPUT_LEN 100

char precedence_table[MAX_OPERATORS][MAX_OPERATORS];

void def_precedence_table() {
    memset(precedence_table, 0, sizeof(precedence_table));

    precedence_table['*']['+'] = 2;
    precedence_table['*']['-'] = 2;
    precedence_table['/']['+'] = 2;
    precedence_table['/']['-'] = 2;
    precedence_table['^']['*'] = 2;
    precedence_table['^']['/'] = 2;
    precedence_table['^']['+'] = 2;
    precedence_table['^']['-'] = 2;

    precedence_table['+']['+'] = 1;
    precedence_table['-']['-'] = 1;
    precedence_table['*']['*'] = 1;
    precedence_table['/']['/'] = 1;
}

int compare_precedence(char op1, char op2) {
    return precedence_table[op1][op2];
}

void operator_precedence_parsing(char input[]) {
    int i=0;
    int top = 1;
    char stack[MAX_INPUT_LEN], output[MAX_INPUT_LEN];
    stack[0]='$';
    strcat(input, "$");
    //printf("%s",input);
while(input[i]!='$'){
int j = i;
if (isalpha(input[i])) {
            stack[top] = input[i];
            printf("%s\t\t",stack);
            int k = i+1;
            while(input[k]!='$'){
            printf("%c",input[k]);
            k++;
            }
            printf("$\t\t");
            printf("SHIFT\n");
            i++;top++;
        }
        else {
        if(j==2){
        stack[top] = input[i];
        printf("%s\t\t",stack);
            int k = i+1;
            while(input[k]!='$'){
            printf("%c",input[k]);
            k++;
            }
            printf("$\t\t");
            printf("SHIFT\n");
            i++;top++;
        }
        else{
        if(compare_precedence(stack[top-2],input[i])==2 || compare_precedence(stack[top-2],input[i])==1){
        stack[top-1]=' ';
        stack[top-2]=' ';
        top--;
        top--;
        printf("%s\t\t",stack);
            int k = i+1;
            while(input[k]!='$'){
            printf("%c",input[k]);
            k++;
            }
            printf("$\t\t");
            printf("REDUCE\n");
        stack[top]=input[i];
    printf("%s\t\t",stack);
            k = i+1;
            while(input[k]!='$'){
            printf("%c",input[k]);
            k++;
            }
            printf("$\t\t");
            printf("SHIFT\n");
        i++;top++;
        }
        else{
        stack[top] = input[i];
        printf("%s\t\t",stack);
            int k = i+1;
            while(input[k]!='$'){
            printf("%c",input[k]);
            k++;
            }
            printf("$\t\t");
            printf("SHIFT\n");
            i++;top++;
        }
        }
       
        }
       
}
if(top!=1){
while(top>1){
stack[top-1]=' ';
        stack[top-2]=' ';
        top--;
        top--;
        printf("%s\t\t",stack);
            printf("$\t\t");
            printf("REDUCE\n");
}
}
}

int main() {
    char input[MAX_INPUT_LEN];

    def_precedence_table();

    printf("Enter the input string: ");
    scanf("%s", input);

    operator_precedence_parsing(input);

    return 0;
}
