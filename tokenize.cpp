#include <string>
#include <cerrno>
#include <iostream>

#include "tokenize.h"

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
            std::cout << "T_STR " << this->text() << std::endl;
            break;
        case T_NUM:
            std::cout << "T_NUM " << this->text() << std::endl;
            break;
    }
}

bool tokenizer::init(const char* path_)
{
        /*
         * inspired by second example from here
         * http://insanecoding.blogspot.ca/2011/11/how-to-read-in-file-in-c.html
         */
        std::ifstream is(path_);
        if (is)
        {
            is.seekg(0, std::ios::end);
            _contents.resize(is.tellg());
            is.seekg(0, std::ios::beg);
            is.read(&_contents[0], _contents.size());
            is.close();
        } else {
            return false;
        }

        _iter = _contents.begin();
        return true;
}

token tokenizer::get_token()
{
    for (; _iter < _contents.end(); _iter++)
    {
        switch(*_iter) {
            case '\0':
                {
                    token tok(T_ERR);
                    _iter++;
                    return tok;
                }
            case ' ': case '\t': case '\n': case '\r':
                break; // skip whitespace
            case '{':
                {
                     token tok(T_LBRACE);
                    _iter++;
                     return tok;
                }
            case '}':
                {
                     token tok(T_RBRACE);
                    _iter++;
                     return tok;
                }
            case '[':
                {
                     token tok(T_LBRACKET);
                    _iter++;
                     return tok;
                }
            case ']':
                {
                     token tok(T_RBRACKET);
                    _iter++;
                     return tok;
                }
            case ':':
                {
                     token tok(T_COLON);
                    _iter++;
                     return tok;
                }
            case ',':
                {
                     token tok(T_COMMA);
                    _iter++;
                     return tok;
                }
        }
    }

    token tok(T_EOF);
    return tok;
}

