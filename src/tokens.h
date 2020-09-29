#ifndef TINYDB_TOKENS_H
#define TINYDB_TOKENS_H
enum token_type_t
{
    T_SELECT = 1,
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

#endif