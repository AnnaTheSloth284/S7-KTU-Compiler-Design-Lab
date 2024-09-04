#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(){
  FILE *ip;
  FILE *op;
  FILE *symTab;
  int lno = 0;
  int token = 0;
  int j = 0;
  int i, flag;
  char ch, lexeme[20];
  ip = fopen("ip.txt","r");
  op = fopen("op.txt","w");
  symTab = fopen("symtab.txt","w");
  int intab = 0;
  char symtab[30][30];
  int tokenj = 0;
  char keyword[30][30] = {"int","main","if","else","do","while","fprintf","FILE","char","fopen","fclose","isalpha","isalnum","strcmp","return","feof","fgetc","sprintf","break"};
  fprintf(op,"Refer no.\t Token\t\t\t\t Lexeme\t\t\t\t  Line No.\n");
  fprintf(op,"--------------------------------------------------------------------------------------------------------------\n");

  while(!feof(ip))
  {
    i=0;
    flag=0;
    ch=fgetc(ip);
    intab = 0;
    if(isalpha(ch))
    {
      lexeme[i]=ch;
      i++;
      ch=fgetc(ip);

      while(isalnum(ch) && ch!=' ')
      {
        lexeme[i]=ch;
        i++;
        ch=fgetc(ip);
      }

      lexeme[i]='\0';

      for(j=0;j<=30;j++)
      {
        if(strcmp(lexeme,keyword[j])==0)
        {
          flag=1;
          break;
        }
      }

      if(flag==1)
      {
        fprintf(op,"%7s\t\t %7s\t\t\t Keyword\t\t\t%7d\n"," ",lexeme,lno);
      }

      else
      {
        for(j=0;j<=30;j++)
        {
          if(strcmp(lexeme,symtab[j])==0)
          {
            intab = 1;
            fprintf(op,"%7d\t\t %7s\t\t\t Identifier\t\t\t%7d\n",j,lexeme,lno);
          }
        }
        if(intab==0){
          sprintf(symtab[token],"%s", lexeme);
          fprintf(symTab,"%7d\t\t %7s\n",token,lexeme);
          fprintf(op,"%7d\t\t %7s\t\t\t Identifier\t\t\t%7d\n",token,lexeme,lno);
          token++;
        }
        i++;
      }
    }

    else if( ch=='<' || ch=='>' || ch=='=')
    {
      fprintf(op,"%7s\t\t %7s\t\t\t Relational Operator\t\t%7d\n"," ",lexeme,lno);
    }

    else if( ch=='+' || ch== '-' || ch=='*' || ch=='/' )
    {
      fprintf(op,"%7s\t\t %7s\t\t\t Arithmetic Operator\t\t%7d\n"," ",lexeme,lno);
    }

    else if(ch=='\n')
    {
      lno++;
    }
  }
fclose(ip);
fclose(op);
return 0;
}
