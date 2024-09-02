#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char code[10][30], str[20], opr[10];
    int i = 0, k = 0;
    FILE *fp1, *fp2;

    fp1 = fopen("/Users/theblithesomesloth/Downloads/input.txt", "r");
    if (fp1 == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fp2 = fopen("/Users/theblithesomesloth/Downloads/result.txt", "w");
    if (fp2 == NULL) {
        perror("Error opening result file");
        fclose(fp1);
        return EXIT_FAILURE;
    }

    char op, fir[10], sec[10], res[10];

    while (fscanf(fp1, " %c %s %s %s", &op, fir, sec, res) == 4) {
        printf("%c %s %s %s\n", op, fir, sec, res);

        switch (op) {
            case '+':
                strcpy(opr, "ADD ");
                i = 0;
                break;
            case '-':
                strcpy(opr, "SUB ");
                i = 0;
                break;
            case '*':
                strcpy(opr, "MUL ");
                i = 1;
                break;
            case '/':
                strcpy(opr, "DIV ");
                i = 1;
                break;
            default:
                fprintf(stderr, "Unknown operator: %c\n", op);
                continue; // Skip this line
        }

        if (strlen(fir) == 2) {
            if (fir[1] == '1')
                fprintf(fp2, "MOV AX,CH\n");
            else if (fir[1] == '2')
                fprintf(fp2, "MOV AX,CL\n");
            else if (fir[1] == '3')
                fprintf(fp2, "MOV AX,DH\n");
            else if (fir[1] == '4')
                fprintf(fp2, "MOV AX,DL\n");
        } else {
            fprintf(fp2, "MOV AX,[%s]\n", fir);
        }

        if (strlen(sec) == 2) {
            if (sec[1] == '1')
                fprintf(fp2, "MOV BX,CH\n");
            else if (sec[1] == '2')
                fprintf(fp2, "MOV BX,CL\n");
            else if (sec[1] == '3')
                fprintf(fp2, "MOV BX,DH\n");
            else if (sec[1] == '4')
                fprintf(fp2, "MOV BX,DL\n");
        } else {
            fprintf(fp2, "MOV BX,[%s]\n", sec);
        }

        if (i == 0) {
            fprintf(fp2, "%sAX,BX\n", opr);
        } else {
            fprintf(fp2, "%sBX\n", opr);
        }

        if (strlen(res) == 2) {
            if (res[1] == '1')
                fprintf(fp2, "MOV CH,AX\n");
            else if (res[1] == '2')
                fprintf(fp2, "MOV CL,AX\n");
            else if (res[1] == '3')
                fprintf(fp2, "MOV DH,AX\n");
            else if (res[1] == '4')
                fprintf(fp2, "MOV DL,AX\n");
        } else {
            fprintf(fp2, "MOV %s,AX\n", res);
        }

        k++;
    }

    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS;
}
