//
//  intermediate-code-generator.c
//  compiler-design-lab
//
//  Created by Anna Ann Mathew on 03/08/24.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

char s[100], post[100], stack[100], queue[100];
int top = -1, j = 0, front = -1;

int precedence(char c){
    if(c == '+' || c == '-'){
        return 1;
    }
    else if(c == '*' || c == '/'){
        return 2;
    }
    else if(c == '^'){
        return 3;
    }
    else{
        return 0;
    }
}

void postfix(){
    int n = strlen(s), i = 0;
    // While end of input string
    while(s[i] != '\0'){
        // if '(' push to stack
        if(s[i] == '('){
            top++;
            stack[top] = s[i];
        }
        // if alphabet append to output
        else if(isalpha(s[i])){
            post[j++] = s[i];
        }
        // else if operator
        else if(precedence(s[i])){
            // keep on popping as long as precednece (stack[top]) >= precednce(operator)
            while(precedence(stack[top]) >= precedence(s[i])){
                post[j++] = stack[top--];
            }
            // increment top and set stack top to operator
            top++;
            stack[top] = s[i];
        }
        // else if ')'
        else if(s[i] == ')'){
            // keep on popping as long as stack[top]!= '('
            while(stack[top] != '('){
                post[j++] = stack[top--];
            }
            // decrement top
            top--;
        }
        // go to next input character
        i++;
    }
    // pop remaining stack
    while(top!=-1){
        post[j++] = stack[top--];
    }
    //append end char to output
    post[j] = '\0';
}

void main(){
    int i = 0;
    char ind = '1';
    
    FILE *fp,*fp1,*fp2,*fp3;
    fp = fopen( "3addr.txt","w");
    fp1 = fopen( "quadraple.txt","w");
    fp2 = fopen( "triple.txt","w");
    fprintf(fp,"Three Address\n");
    fprintf(fp1,"Quadruple\nOP\tO1\tO2\tRES\n");
    fprintf(fp2,"Triple\nIN\tOP\tO1\tO2\n");
    fp3=fopen( "cd5inp.txt","r");
    printf("Input the string: ");
    
    postfix();
    while((fscanf(fp3,"%s",s))!=EOF)
    {
    postfix();
    printf("Infix : %s \nPostfix : %s\n", s, post);
    // while the postfix outputs end of string isnt reached'
    while(post[i] != '\0'){
        // if operator
        if(precedence(post[i])){
            // pop last two operands from queue
            char a = queue[front--];
            char b = queue[front--];

            fprintf(fp,"t%c = t%c %c t%c\n", ind, b, post[i], a);
            fprintf(fp1,"%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
            fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);
            
            front++;
            queue[front] = ind;
            ind++;
        }
        // for operands, i.e., alphabets, add to queue
        else{
            front++;
            queue[front] = post[i];
        }
        i++;
    }
    }
}
