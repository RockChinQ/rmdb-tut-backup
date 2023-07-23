/* keywords are case insensitive */
%option caseless
/* we don't need yywrap() function */
%option noyywrap
/* we don't need yyunput() function */
%option nounput
/* we don't need input() function */
%option noinput
/* enable location */
%option bison-bridge
%option bison-locations

%{
#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <climits>

// automatically update location
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for (int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 1; \
        } else { \
            yylloc->last_column++; \
        } \
    }

%}

alpha [a-zA-Z]
digit [0-9]
white_space [ \t]+
new_line "\r"|"\n"|"\r\n"
sign "+"|"-"
identifier {alpha}(_|{alpha}|{digit})*
value_int {sign}?{digit}+
value_float {sign}?{digit}+\.({digit}+)?
value_string '[^']*'
value_datetime '{digit}{4}-{digit}{2}-{digit}{2}\x20{digit}{2}:{digit}{2}:{digit}{2}'
single_op ";"|"("|")"|","|"*"|"="|">"|"<"|"."

%x STATE_COMMENT

%%
    /* block comment */
"/*" { BEGIN(STATE_COMMENT); }
<STATE_COMMENT>"*/" { BEGIN(INITIAL); }
<STATE_COMMENT>[^*] { /* ignore the text of the comment */ }
<STATE_COMMENT>\* { /* ignore *'s that aren't part of */ }
    /* single line comment */
"--".* { /* ignore single line comment */ }
    /* white space and new line */
{white_space} { /* ignore white space */ }
{new_line} { /* ignore new line */ }
    /* keywords */
"SHOW" { return SHOW; }
"BEGIN" { return TXN_BEGIN; }
"COMMIT" { return TXN_COMMIT; }
"ABORT" { return TXN_ABORT; }
"ROLLBACK" { return TXN_ROLLBACK; }
"TABLES" { return TABLES; }
"CREATE" { return CREATE; }
"TABLE" { return TABLE; }
"DROP" { return DROP; }
"DESC" { return DESC; }
"INSERT" { return INSERT; }
"INTO" { return INTO; }
"VALUES" { return VALUES; }
"DELETE" { return DELETE; }
"FROM" { return FROM; }
"WHERE" { return WHERE; }
"UPDATE" { return UPDATE; }
"SET" { return SET; }
"SELECT" { return SELECT; }
"INT" { return INT; }
"BIGINT" { return BIGINT; }
"CHAR" { return CHAR; }
"FLOAT" { return FLOAT; }
"DATETIME" { return DATETIME; }
"INDEX" { return INDEX; }
"AND" { return AND; }
"JOIN" {return JOIN;}
"EXIT" { return EXIT; }
"HELP" { return HELP; }
"ORDER" { return ORDER; }
"BY" {  return BY;  }
"ASC" { return ASC; }
"LIMIT" { return LIMIT; }
"COUNT" { return COUNT; }
"MAX" { return MAX; }
"MIN" { return MIN; }
"SUM" { return SUM; }
"AS" { return AS; } 
    /* operators */
">=" { return GEQ; }
"<=" { return LEQ; }
"<>" { return NEQ; }
{single_op} { return yytext[0]; }
    /* id */
{identifier} {
    yylval->sv_str = yytext;
    return IDENTIFIER;
}
    /* literals */
{value_int} {
    int64_t bigint = atoll(yytext);
    if(bigint > INT_MAX || bigint < INT_MIN) {
        yylval->sv_str = yytext;
        return VALUE_BIGINT;
    }else {
        yylval->sv_int = atoi(yytext);
        return VALUE_INT;
    }
}
{value_float} {
    yylval->sv_float = atof(yytext);
    return VALUE_FLOAT;
}

{value_datetime} {
    yylval->sv_str = std::string(yytext + 1, strlen(yytext) - 2);
    return VALUE_DATETIME;
}

{value_string} {
    yylval->sv_str = std::string(yytext + 1, strlen(yytext) - 2);
    return VALUE_STRING;
}

    /* EOF */
<<EOF>> { return T_EOF; }
    /* unexpected char */
. { std::cerr << "Lexer Error: unexpected character " << yytext[0] << std::endl; }
%%
