#include <string>
#include <cerrno>
#include <iostream>

#include "token.h"

void token::print()
{
    switch(this->type()) {
        case T_EOF:
            std::cout << "T_EOF" << std::endl;
            break;
        case T_ERR:
            std::cout << "T_ERR" << std::endl;
            break;
        case T_LBRACE:
            std::cout << "T_LBRACE" << std::endl;
            break;
        case T_RBRACE:
            std::cout << "T_RBRACE" << std::endl;
            break;
        case T_LBRACKET:
            std::cout << "T_LBRACKET" << std::endl;
            break;
        case T_RBRACKET:
            std::cout << "T_RBRACKET" << std::endl;
            break;
        case T_COLON:
            std::cout << "T_COLON" << std::endl;
            break;
        case T_COMMA:
            std::cout << "T_COMMA" << std::endl;
            break;
        case T_STR:
            std::cout << "T_STR     " << this->text() << std::endl;
            break;
        case T_NUM:
            std::cout << "T_NUM     " << this->text() << std::endl;
            break;
    }
}

