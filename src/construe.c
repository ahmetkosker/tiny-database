#include "construe.h"

static int is_int(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < 0x30 || str[i] > 0x39)
            return -1;
    }
    return (strlen(str) == 0) ? -1 : 0;
}

statement_kind_t parse_statement(char *statement, void **p)
{
    select_statement_t *po;
    char temp[1000];
    temp[0] = 0;
    statement_parser_state_t state = PARSER_STATE_COMMAND;
    int temp_len;
    char c;
    char *before;
    for (int i = 0; i < strlen(statement); i++)
    {
        c = statement[i];
        int de = strlen(statement);
        temp_len = strlen(temp);
        temp[temp_len] = c;
        temp[temp_len + 1] = 0;
        if (state == PARSER_STATE_COMMAND && c == ' ')
        {
            temp[strlen(temp) - 1] = 0;
            if (!strcmp(temp, "SELECT"))
            {
                state = PARSER_STATE_SELECT;
            }
            else if (!strcmp(temp, "UPDATE"))
            {
                state = PARSER_STATE_UPDATE;
            }
            else
            {
                printf("syntax error at %d expected one of SELECT, UPDATE\n", i);
                return STATEMENT_KIND_ERROR;
            }
            temp[0] = 0;
            state = PARSER_STATE_SELECT;
        }
        else if (state == PARSER_STATE_SELECT && c == ' ')
        {
            temp[strlen(temp) - 1] = 0;
            *p = malloc(sizeof(select_statement_t));
            po = (select_statement_t *)*p;
            po->column_name = (char *)malloc(sizeof(char) * strlen(temp) + 1);
            strcpy(po->column_name, temp);
            temp[0] = 0;
            state = PARSER_STATE_FROM;
        }
        else if (state == PARSER_STATE_FROM && c == ' ')
        {
            temp[strlen(temp) - 1] = 0;
            if (!strcmp(temp, "FROM"))
            {
                state = PARSER_STATE_SELECT_TABLE_NAME;
            }
            else
            {
                printf("syntax error at %ld FROM expected\n", i - strlen(temp) + 1);
                return STATEMENT_KIND_ERROR;
            }
            temp[0] = 0;
        }
        else if (state == PARSER_STATE_SELECT_TABLE_NAME && (c == ' ' || i == strlen(statement) - 1))
        {
            temp[strlen(temp) - 1] = 0;
            po->table_name = (char *)malloc(sizeof(char) * strlen(temp) + 1);
            strcpy(po->table_name, temp);
            if (i == strlen(statement) - 1)
            {
                return STATEMENT_KIND_SELECT;
            }
            state = PARSER_STATE_SELECT_WHERE;
            temp[0] = 0;
        }
        else if (state == PARSER_STATE_SELECT_WHERE && c == ' ')
        {
            temp[strlen(temp) - 1] = 0;
            if (!strcmp(temp, "WHERE"))
            {
                state = PARSER_STATE_SELECT_WHERE_COLUNM_NAME;
                temp[0] = 0;
            }
            else
            {
                printf("syntax error at %d WHERE expected\n", i);
                return STATEMENT_KIND_ERROR;
            }
        }
        else if (state == PARSER_STATE_SELECT_WHERE_COLUNM_NAME && c == '=')
        {
            temp[strlen(temp) - 1] = 0;
            po->where.column_name = (char *)malloc(sizeof(char) * strlen(temp) + 1);
            state = PARSER_STATE_SELECT_WHERE_VALUE;
            strcpy(po->where.column_name, temp);
            temp[0] = 0;
        }
        else if (state == PARSER_STATE_SELECT_WHERE_VALUE)
        {
            if (c == '\'')
            {
                state = PARSER_STATE_SELECT_WHERE_VALUE_STRING;
                temp[0] = 0;
            }
            else
            {
                state = PARSER_STATE_SELECT_WHERE_VALUE_INT;
            }
        }
        else if (state == PARSER_STATE_SELECT_WHERE_VALUE_STRING && strlen(statement) - 1 == i)
        {
            if (c == '\'')
            {
                po->where.value = (char *)malloc(sizeof(char) * strlen(temp) + 1);
                temp[strlen(temp) - 1] = 0;
                strcpy(po->where.value, temp);
                return STATEMENT_KIND_SELECT;
            }
            printf("syntax error at %d: expected '\n", i);
            return STATEMENT_KIND_ERROR;
        }
        else if (state == PARSER_STATE_SELECT_WHERE_VALUE_INT && strlen(statement) - 1 == i)
        {
            if (is_int(temp))
            {
                printf("syntax error at %ld: expected an integer\n", i - strlen(temp));
                return STATEMENT_KIND_ERROR;
            }
            po->where.value = (char *)malloc(sizeof(char) * strlen(temp) + 1);
            strcpy(po->where.value, temp);
            return STATEMENT_KIND_SELECT;
        }
    }
}

int main()
{
    select_statement_t *po;
    statement_kind_t a = parse_statement("SELECT tzaer FROM asdswqefawdas WHERE name='ahmet'", (void **)&po);
    printf("%s %s %s %s\n", po->column_name, po->table_name, po->where.column_name, po->where.value);
    return 0;
}