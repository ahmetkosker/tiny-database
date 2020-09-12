/* example SELECT statement


SELECT column_name | * FROM table_name [WHERE column_name=value]
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum statement_parser_state_t
{
    PARSER_STATE_COMMAND,
    PARSER_STATE_SELECT,
    PARSER_STATE_UPDATE,
    PARSER_STATE_SET,
    PARSER_STATE_SELECT_TABLE_NAME,
    PARSER_STATE_UPDATE_TABLE_NAME,
    PARSER_STATE_SELECT_WHERE,
    PARSER_STATE_SELECT_WHERE_COLUNM_NAME,
    PARSER_STATE_SELECT_WHERE_VALUE,
    PARSER_STATE_SELECT_WHERE_VALUE_STRING,
    PARSER_STATE_SELECT_WHERE_VALUE_INT,
    PARSER_STATE_UPDATE_WHERE,
    PARSER_STATE_UPDATE_WHERE_COLUNM_NAME,
    PARSER_STATE_UPDATE_WHERE_VALUE,
    PARSER_STATE_UPDATE_WHERE_VALUE_STRING,
    PARSER_STATE_UPDATE_WHERE_VALUE_INT,
    PARSER_STATE_FROM
} statement_parser_state_t;

typedef enum statement_kind_t
{
    STATEMENT_KIND_SELECT,
    STATEMENT_KIND_UPDATE,
    STATEMENT_KIND_ERROR
} statement_kind_t;

typedef struct condition_t
{
    char *column_name;
    char *value;
} condition_t;

typedef struct select_statement_t
{
    char *column_name;
    char *table_name;
    condition_t where;
} select_statement_t;

statement_kind_t parse_statement(char *statement, void **p);