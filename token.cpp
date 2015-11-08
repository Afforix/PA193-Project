#include <string>
#include <cerrno>
#include <iostream>

#include "token.h"

std::string token::to_string()
{
    switch(this->type()) {
        case T_EOF:
            return "EOF";
        case T_ERR:
            return "ERROR";
        case T_LBRACE:
            return "{";
        case T_RBRACE:
            return "}";
        case T_LBRACKET:
            return "[";
        case T_RBRACKET:
            return "]";
        case T_COLON:
            return ":";
        case T_COMMA:
            return ",";
        case T_NULL:
            return "null";
        case T_TRUE:
            return "true";
        case T_FALSE:
            return "false";
        case T_STR:
            return "string " + this->text();
        case T_NUM:
            return "number " + this->text();
        default:
            return "unknown token";
    }
}

