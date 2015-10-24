#include "tokenizer.h"

tokenizer::tokenizer()
{
    err = false;
}

bool tokenizer::init(const char *path_)
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

inline bool tokenizer::contains(std::string str, char c)
{
    if (str.find_first_of(c) == std::string::npos) {
         return false;
    } else {
        return true;
    }

}

token tokenizer::procstr()
{
    std::string str;
    std::string hexnum = "0123456789ABCDEFabcdef";

    str.push_back(*_iter);
    _iter++;

    for (; _iter != _contents.end(); _iter++)
    {
        switch(*_iter)
        {
            case '\"':
                str.push_back(*_iter);
                _iter++;

                return token(T_STR, str);
            case '\\':
                str.push_back(*_iter);
                _iter++;
                if (_iter == _contents.end()) {
                    err = true;
                    return token(T_ERR);
                }

                if (*_iter=='\"' || *_iter=='\\'
                    || *_iter=='b' || *_iter=='f'
                    || *_iter=='n' || *_iter=='r'
                    || *_iter=='t') {

                    str.push_back(*_iter);

                } else if (*_iter=='u') {

                    str.push_back(*_iter);

                    for (int i = 0; i<4; i++){
                        _iter++;
                        if (_iter == _contents.end()){
                            err = true;
                            return token(T_ERR);
                        }

                        if (this->contains(hexnum, *_iter)){
                            str.push_back(*_iter);
                        } else {
                            err = true;
                            return token(T_ERR);
                        }
                    }

                } else {
                        err = true;
                        return token(T_ERR);
                }
                break;
            default:
                str.push_back(*_iter);
                break;
        }

    }

    err = true;
    return token(T_ERR);
}

token tokenizer::get_token()
{
    if (err) {
        return token(T_ERR);
    }

    for (; _iter != _contents.end(); _iter++)
    {
        switch(*_iter)
        {
            case '\0':
                {
                    err = true;
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
            case '\"':
                {
                    return this->procstr();
                }
        }
    }

    return token(T_EOF);
}

