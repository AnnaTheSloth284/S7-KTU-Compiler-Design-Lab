//
//  recursive-descent-parser.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 29/07/24.
//

// C program to Construct of recursive descent parsing for
// the following grammar
// E->TE’
// E’->+TE/@
// T->FT’
// T`->*FT’/@
// F->(E)/id where @ represents null character

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

char ip_sym[15], op[50], tmp[50];
int ip_ptr = 0, n = 0;

void e();
void e_prime();
void t();
void t_prime();
void f();
void advance();

void e() {
    strcpy(op, "TE'");
    printf("E=%-25s", op);
    printf("E->TE'\n");
    t();
    e_prime();
}

void e_prime() {
    int i, l, m = 0;
    memset(tmp, 0, sizeof(tmp));
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[m++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (m = 0; m < l && op[m] != 'E'; m++)
        ;
    if (ip_sym[ip_ptr] == '+') {
        i = m + 2;
        do {
            op[i + 2] = op[i];
            i++;
        } while (i <= l);
        op[m++] = '+';
        op[m++] = 'T';
        op[m++] = 'E';
        op[m++] = 39;
        printf("E=%-25s", op);
        printf("E'->+TE'\n");
        advance();
        t();
        e_prime();
    } else {
        op[m] = 'e';
        for (i = m + 1; i <= strlen(op); i++)
            op[i] = op[i + 1];
        printf("E=%-25s", op);
        printf("E'->e\n");
    }
}

void t() {
    int i, l, m = 0;
    memset(tmp, 0, sizeof(tmp));
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[m++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (m = 0; m < l && op[m] != 'T'; m++)
        ;
    i = m + 1;
    do {
        op[i + 2] = op[i];
        i++;
    } while (i < l);
    op[m++] = 'F';
    op[m++] = 'T';
    op[m++] = 39;
    printf("E=%-25s", op);
    printf("T->FT'\n");
    f();
    t_prime();
}

void t_prime() {
    int i, l, m = 0;
    memset(tmp, 0, sizeof(tmp));
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[m++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (m = 0; m < l && op[m] != 'T'; m++)
        ;
    if (ip_sym[ip_ptr] == '*') {
        i = m + 2;
        do {
            op[i + 2] = op[i];
            i++;
        } while (i < l);
        op[m++] = '*';
        op[m++] = 'F';
        op[m++] = 'T';
        op[m++] = 39;
        printf("E=%-25s", op);
        printf("T'->*FT'\n");
        advance();
        f();
        t_prime();
    } else {
        op[m] = 'e';
        for (i = m + 1; i <= strlen(op); i++)
            op[i] = op[i + 1];
        printf("E=%-25s", op);
        printf("T'->e\n");
    }
}

void f() {
    int i, l, m = 0;
    memset(tmp, 0, sizeof(tmp));
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[m++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (m = 0; m < l && op[m] != 'F'; m++)
        ;
    if (isalpha(ip_sym[ip_ptr])) {
        op[m] = 'i';
        printf("E=%-25s", op);
        printf("F->i\n");
        advance();
    } else if (ip_sym[ip_ptr] == '(') {
        advance();
        e();
        if (ip_sym[ip_ptr] == ')') {
            advance();
            i = m + 2;
            do {
                op[i + 2] = op[i];
                i++;
            } while (i <= l);
            op[m++] = '(';
            op[m++] = 'E';
            op[m++] = ')';
            printf("E=%-25s", op);
            printf("F->(E)\n");
        } else {
            printf("\n\tSyntax error\n");
            exit(1);
        }
    } else {
        printf("\n\tSyntax error\n");
        exit(1);
    }
}

void advance() {
    ip_ptr++;
}

int main() {
    int i;
    printf("\nGrammar without left recursion");
    printf("\n\t\t E->TE' \n\t\t E'->+TE'|e \n\t\t T->FT' ");
    printf("\n\t\t T'->*FT'|e \n\t\t F->(E)|i");
    printf("\n Enter the input expression: ");
    scanf("%s", ip_sym);
    printf("Expressions");
    printf("\t Sequence of production rules\n");
    e();
    for (i = 0; i < strlen(ip_sym); i++) {
        if (ip_sym[i] != '+' && ip_sym[i] != '*' && ip_sym[i] != '(' &&
            ip_sym[i] != ')' && ip_sym[i] != 'i') {
            printf("\nSyntax error\n");
            break;
        }
    }
    printf("\n");
    return 0;
}
