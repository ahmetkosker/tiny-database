/* Decalring two counters one for number  
of lines other for number of characters */
%{ 
#include "tokens.h"
%} 
  
/***rule 1 counts the number of lines,  
rule 2 counts the number of characters  
and rule 3 specifies when to stop  
taking input***/
%% 
"SELECT"    {return T_SELECT;} 
"WHERE"     {return T_WHERE;}
"UPDATE"    {return T_UPDATE;}
"SET"       {return T_SET;}
"FROM"      {return T_FROM;}
"="         {return T_EQUAL;}
[0-9]+      {return T_INT;}
[^"= ]+     {return T_NAME;}
\"[^"]*\"   {return T_STRING;} 

<<EOF>>     {return T_EOF;}
%% 

  
/*** User code section***/
int yywrap(){} 
int main()
{   
    int yy = yylex();
    while (yy != T_EOF)
    {
        printf("%d ", yy);
        yy = yylex();
    }
} 