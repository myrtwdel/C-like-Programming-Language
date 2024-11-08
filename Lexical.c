%{

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tok.h"




void yyerror(const char* err);

char stringBuffer[];

%}

//Counts the lines of the text
%option yylineno

//Exclusive state for String
%x STRING

//Exclusive state for Comment
%x COMMENT


DIGIT		[0-9]
LETTER		[a-zA-Z]
ALPHANUM	[a-zA-Z0-9]

IDENTIFIER	[a-zA-Z_][a-zA-Z0-9_]*
ICONST		[+-]?[1-9][0-9]* | 0


%%

/* RULES */

//Spacebar, Tab, Newline:
[ \t\n]		                    ;


//Key words:
"INTEGER"						return T_INTEGER;
"CHAR"							return T_CHAR;
"STRING"						return T_STRING;

"IF"                            return T_IF;
"THEN"                          return T_THEN;
"ELSE"                          return T_ELSE;
"ELSEIF"                        return T_ELSEIF;
"FOR"                           return T_FOR;
"TO"                            return T_TO;
"STEP"							return T_STEP;
"ENDFOR"						return T_ENDFOR;
"WHILE"							return T_WHILE;
"ENDWHILE"						return T_ENDWHILE;
"SWITCH"						return T_SWITCH;
"DEFAULT"						return T_DEFAULT;
"ENDSWITCH"						return T_ENDSWITCH;

"PROGRAM"						return T_PROGRAM;
"FUNCTION"						return T_FUNCTION;
"VARS"							return T_VARS;
"END_FUNCTION"					return T_END_FUNCTION;
"RETURN"						return T_RETURN;
"STARTMAIN"						return T_STARTMAIN;
"ENDMAIN"						return T_ENDMAIN;

"BREAK"       					return T_BREAK;
"PRINT"							return T_PRINT;

//Comment:
"%"							    { BEGIN(COMMENT); }
<COMMENT>(\n)					{ INITIAL(COMMENT); return T_COMM; }
<COMMENT>.						{ }

//Operators:
"=="                            return T_EQUOP;
"!="							return T_EQUOP;
"="                             return T_ASS;
":="                            return T_FOROP;
">"								return T_COMPOP;
"<"								return T_COMPOP;

"AND"                           return T_ANDOP;
"OR"                            return T_OROP;
"+"                             return T_ADDOP;
"-"								return T_ADDOP;
"*"                             return T_MULOP;
"/"								return T_MULOP;
"^"								return T_POWOP;

//Other tokens:
";"								return T_SEMIC;
":"								return T_COLON;
"("								return T_BRA_OPEN;
")"								return T_BRA_CLOSE;
"["								return T_AGG_OPEN;
"]"								return T_AGG_CLOSE;
","								return T_COMMA;

//Identifier:
{IDENTIFIER}					return T_IDENTIFIER;

//Constants:
{ICONST}						return T_ICONST;
\'[a-zA-Z0-9]\'					return T_CCONST;
\'[!@#$%^&*()]\'				return T_CCONST;
\'(([^\\]) | (\\[nt]))\'		return T_CCONST;

//String:
\"								{ BEGIN(STRING); } 
<STRING>\"						{ BEGIN(INITIAL); return T_SCONST; }
<STRING>(\\\n)					{ } 
<STRING>(\\. | [^"\\])			{ if(strlen(yyyext) == 2 && strcmp(yytext[0], "\\") == 0){
										if(strcmp(yytext[1], "\\n")){
											strcat(stringBuffer, "\n");
										}
										else if(strcmp(yytext[1], "\\t")){
											strcat(stringBuffer, "\t");
										}
										else {
											strcat(stringBuffer, &yytext[1]);
										}
									}	
								  else {
								  		strcat(stringBuffer, yytext); 
								  	}
								}
<STRING>(\n)					{ yyerror("New line without \\. \n"); }
<STRING><<EOF>>					{ yyerror("End of string without closing. \n"); }
<STRING>.						{ yyerror("Unknown character.\n"); }

//Any other case:
.								yyerror("Unknown character.\n");

//End of fine -> return 0;
<<EOF>>							return T_EOF;


%%

int main(int argc, char *argv[]){
	
	int token;
	
	if(argc > 1){
		yyin = fopen(argv[1], "r");
		if(yyin == NULL){
			perror("Error opening file.");
			return -1;
		}	
	}
	
	do{
		token = yylex();
	}while(token != T_EOF);
	
	fclose(yyin);
	yyterminate();
		
}

void yyerror(const char* err){
	printf("Error in line %d:\t %s \n", yylineno, err);
}





