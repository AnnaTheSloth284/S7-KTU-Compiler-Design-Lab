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

char queue[100];
char s[100];
char ind = '1';
int count2 = 1;
FILE *fp1,*fp2;

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

void formatter(char post[100],char stack[100]){
int top = -1, j = 0, front = -1;
int n = strlen(s), i = 0;
while(s[i] != '\0'){
if(s[i] == '('){
top++;
stack[top] = s[i];
}
else if(isalpha(s[i])){
post[j++] = s[i];
}
else if(precedence(s[i])){
while(precedence(stack[top]) >= precedence(s[i])){
post[j++] = stack[top--];
}
top++;
stack[top] = s[i];
}
else if(s[i] == ')'){
while(stack[top] != '('){
post[j++] = stack[top--];
}
top--;
}
i++;
}
while(top!=-1){
post[j++] = stack[top--];
}
post[j] = '\0';
printf("Postfix expression: %s\n", post);
i = 0;
while(post[i] != '\0'){
if(precedence(post[i])){
char a = queue[front--];
char b = queue[front--];

if(isdigit(a) && isdigit(b)){
fprintf(fp1,"%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
//fprintf(fp1,"%c\tt%c\tt%c\tt%d\n", post[i], b, a, count2);
}
else if(isdigit(b)){
fprintf(fp1,"%c\tt%c\t%c\tt%c\n", post[i], b, a, ind);
//fprintf(fp1,"%c\tt%c\t%c\tt%d\n", post[i], b, a, count2);
}
else if(isdigit(a)){
fprintf(fp1,"%c\t%c\tt%c\tt%c\n", post[i], b, a, ind);
//fprintf(fp1,"%c\t%c\tt%c\tt%d\n", post[i], b, a, count2);
}
else{
fprintf(fp1,"%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
//fprintf(fp1,"%c\t%c\t%c\tt%d\n", post[i], b, a, count2);
}
fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);
//fprintf(fp2,"%d\t%c\t%c\t%c\n", count2, post[i], b, a);
front++;
queue[front] = ind;
ind++;
count2++;
}
else{
front++;
queue[front] = post[i];
}
i++;
}
}

void main(){
    int count;
    fp1 = fopen( "quadruple-format.txt","w");
    fp2 = fopen( "triple-format.txt","w");
    fprintf(fp1,"QUADRUPLE\nOP\tO1\tO2\tRES\n");
    fprintf(fp2,"TRIPLE\nIN\tOP\tO1\tO2\n");

    printf("Enter the number of expressions:");
    scanf("%d",&count);

    int k;
    for(k=0;k<count;k++){
        memset(queue, '\0', sizeof(queue));
        memset(s, '\0', sizeof(s));
        char post[100], stack[100];
        printf("Infix expression: ");
        scanf("%s", s);
        formatter(post, stack);
    }

}
