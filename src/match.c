#include <stdio.h>
#include <stdlib.h>

/*(terminals)
T_SELECT = SELECT
T_NAME = [^ ]+
T_STRING = "[^"]*"
T_INT = [0-9]+
T_UPDATE = UPDATE
T_SET = SET
T_FROM = FROM
T_WHERE = WHERE
T_QUOTE = '\''
T_EQUAL '='

(non_terminals)
S
select_statement
update_statement

grammar = rule+rule+rule+rule...+terminals+non_terminals+starting_non_terminal
rule = non_terminal->combination_off_terminals_and_non_terminals

alphabet = terminal+terminal+terminal...

    
S --> select_statement | update_statement
select_statement --> T_SELECT T_NAME T_FROM T_NAME where_statement
update_statement --> T_UPDATE T_NAME T_SET T_NAME T_EQUAL value where_statement
where_statement --> ϵ | T_WHERE T_NAME T_EQUAL value
value --> T_STRING | T_INT

SELECT name FROM users
T_SELECT T_STRING T_FROM T_STRING


struct a
{

}

*/
int error = 0;

union token_value_t
{
    char *string_value;
    int int_value;
};

enum token_type_t
{
    T_SELECT,
    T_NAME,
    T_STRING,
    T_INT,
    T_UPDATE,
    T_SET,
    T_FROM,
    T_WHERE,
    T_EQUAL,
    T_EOF
};

struct token_t
{
    enum token_type_t type;
    union token_value_t value;
};

enum token_type_t sentence[20] = {T_SELECT, T_NAME, T_FROM, T_NAME, T_WHERE, T_NAME, T_EQUAL, T_INT, T_EOF};
enum token_type_t sentence2[20] = {T_UPDATE, T_NAME, T_SET, T_FROM, T_NAME, T_EQUAL, T_INT, T_WHERE, T_NAME, T_EQUAL, T_INT, T_EOF};

int cursor = 0;

enum token_type_t get_next_token()
{
    enum token_type_t t = sentence2[cursor];
    cursor++;
    return t;
}

enum token_type_t l;
void S();
void select_statement();
void update_statement();
void where_statement();
void value();
void match(enum token_type_t t);

int main()
{
    struct token_t *ahsc = malloc(sizeof(struct token_t));
    //recursive decent parser
    //bütün non terminaller için fonksiyon oluşturulur, terminaller için oluşturulmaz match ile match edilir,
    //terminal fonksiyonlarının içinde kuralın sağındaki ifadeye göre if else oluşturularak uygun non terminal fonksiyonları ve match çağırılır
    l = get_next_token();
    S();
    if (l == T_EOF && error == 0)
        printf("Parsing Successful");
    else
        printf("Parsing failed\n");
}

void S()
{
    switch (l)
    {
    case T_SELECT:
        select_statement();
        break;
    case T_UPDATE:
        update_statement();
        break;
    }
}

void select_statement()
{
    match(T_SELECT);
    match(T_NAME);
    match(T_FROM);
    match(T_NAME);
    where_statement();
}

void update_statement()
{
    match(T_UPDATE);
    match(T_NAME);
    match(T_SET);
    match(T_NAME);
    match(T_EQUAL);
    value();
    where_statement();
}

void where_statement()
{
    switch (l)
    {
    case T_WHERE:
        match(T_WHERE);
        match(T_NAME);
        match(T_EQUAL);
        value();
        break;
    }
}

void value()
{
    switch (l)
    {
    case T_STRING:
        match(T_STRING);
        break;
    case T_INT:
        match(T_INT);
        break;
    }
}

void match(enum token_type_t t)
{
    if (l == t)
    {
        l = get_next_token();
    }
    else
    {
        error = 1;
        printf("Syntax error at %d\n", cursor - 1);
        exit(-1);
    }
}
