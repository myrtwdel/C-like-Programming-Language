%option noyywrap

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>

#include "parser.tab.h"
int nline;
void comments();
void yyerror(const char* err);


%}

%option yylineno

%x COMMENT


%%
[ \t]		                    ;


"\n"				            {return T_NEWLINE;}




		
	 								

"INTEGER"						{return T_INTEGER;}
"CHAR"							{return T_CHAR;}
"STRING"						   {return T_STRING;}

"IF"                       {return T_IF;}
"THEN"                     {return T_THEN;}
"ELSE"                     {return T_ELSE;}
"ELSEIF"                   {return T_ELSEIF;}
"ENDIF"		               {return T_ENDIF;}
"FOR"                      {return T_FOR;}
"TO"                       {return T_TO;}
"STEP"							{return T_STEP;}
"ENDFOR"				   		{return T_ENDFOR;}
"WHILE"					   	{return T_WHILE;}
"ENDWHILE"						{return T_ENDWHILE;}
"SWITCH"						   {return T_SWITCH;}
"CASE"							{return T_CASE;}
"DEFAULT:"						{return T_DEFAULT;}
"ENDSWITCH"						{return T_ENDSWITCH;}

"PROGRAM"						{return T_PROGRAM;}
"FUNCTION"						{return T_FUNCTION;}
"VARS"							{return T_VARS;}
"END_FUNCTION"					{return T_END_FUNCTION;}
"RETURN"						   {return T_RETURN;}
"STARTMAIN"						{return T_STARTMAIN;}
"ENDMAIN"						{return T_ENDMAIN;}
"TYPEDEF" 		        		{return T_TYPEDEF;}
"STRUCT"				         {return T_STRUCT;}
"ENDSTRUCT"						{return T_ENDSTRUCT;}

"BREAK"       					{return T_BREAK;}
"PRINT"							{return T_PRINT;}



"/\*[\s\S]*?\*/"				{return T_MLCOMM;}

"=="                       {return T_COMPOP;}
"!="						   	{return T_COMPOP;}
"="                        {return T_ASS;}
":="                       {return T_FOROP;}
">"								{return T_COMPOP;}
"<"								{return T_COMPOP;}

"AND"                      {return T_ANDOP;}
"OR"                       {return T_OROP;}
"+"                        {return T_ADDOP;}
"-"								{return T_ADDOP;}
"*"                        {return T_MULOP;}
"/"								{return T_MULOP;}
"^"								{return T_POWOP;}


";"								{return T_SEMIC;}
":"								{return T_COLON;}
"("								{return T_BRA_OPEN;}
")"								{return T_BRA_CLOSE;}
"["								{return T_AGG_OPEN;}
"]"								{return T_AGG_CLOSE;}
","								{return T_COMMA;}
"."                        {return T_DOT;}
"/*"           				{ comments(); }

	



\'(.)*\'			            {return T_SCONST;}

[0-9]+				         {return T_ICONST;}
			
[a-zA-Z][a-zA-Z0-9_]*		{return T_IDENTIFIER;}



	





.								   {yyerror("Unknown character.\n");}


%%



void comments()
{

   char c;
   
   for (;;)
    {  
    while((c=input())!='*' && c!=EOF)
 {
 if (c=='\n') nline++;
  }
 
if(c==EOF) break;
         c=input();
     
         if (c=='/') break;

    }  

}





