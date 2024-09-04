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

char ip_sym[15];
int ip_ptr = 0, n = 0;

void e();
void e_prime();
void t();
void t_prime();
void f();
void advance();

void e() {
    t();
    e_prime();
}

void e_prime() {
    if (ip_sym[ip_ptr] == '+') {
        advance();
        t();
        e_prime();
    }
}

void t() {
    f();
    t_prime();
}

void t_prime() {
    if(ip_sym[ip_ptr] == '*'){
advance();
        f();
        t_prime();
        }
}

void f() {
    if (isalpha(ip_sym[ip_ptr])) {
        advance();
    } else if (ip_sym[ip_ptr] == '(') {
        advance();
        e();
        if (ip_sym[ip_ptr] == ')') {
            advance();
        } else {
            printf("\n\tBracket missing\n");
            n=1;
        }
    } else {
        printf("\n\tSyntax error\n");
        n=1;
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
    printf("\nEnter the input expression: ");
    scanf("%s", ip_sym);
    e();
    if(strlen(ip_sym)==ip_ptr && n==0) printf("Accepted\n");
    else printf("Rejected");
    return 0;
}
