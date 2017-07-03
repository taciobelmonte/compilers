%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int num_lines = 1;

%}
 
digito          [0-9]
letra           [a-zA-Z]
ID				({letra})(_|{letra}|{digito})*
whitespace		[ ]
delimitador		[\t]
ws				{delimitador}+
		
%%

{ws}													/*Ignora*/
{digito}+												{printf("DEC \"%s\" %d \n", yytext, num_lines);}
let|def|if|else|while|return|break|continue 			{printf("KEY \"%s\" %d \n", yytext, num_lines);}
"("														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
")"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"{"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"}"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"["														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"]"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"="														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
","														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
";"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"<="													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
">="													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"=="													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"!="													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"&&"													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"||"													{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"!"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"+"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"-"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"*"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"/"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
"<"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
">"														{printf("SYM \"%s\" %d \n", yytext, num_lines);}
{ID}													{printf("ID \"%s\" %d \n", yytext, num_lines);}
\n 														{++num_lines;}
{whitespace}+											/*Remove espaços em branco*/
"//".* 													/*Remove comentarios de uma linha*/
.														{printf("\"%s\"\n", yytext);return -2;}
<<EOF>>													{return -1;}

%%
int yywrap();

int main(int argc, char** argv){
	int num = 0;
	int token = -1;
	
	yyin  = fopen( argv[1], "r" ); 
	yyout = fopen( argv[2], "w" ); 

	do{
		token = yylex();
		
		if(token == -1){
           break;
         }else if(token == -2){
           return 0;
         }
         else if(yyleng == 0){
             printf("\n[ERRO] Lexema não pertence a linguagem.");
         }
         else{
           printf("identificou\n");
       	}
	
	}while( token != EOF);

	fclose(yyout);
    fclose(yyin);
	
	return 0;
}

int yywrap(){
	return 1;
}