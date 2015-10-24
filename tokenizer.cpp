#include "tokenizer.h"

#define HEXNUM "0123456789ABCDEFabcdef"
#define FIRST "123456789"
#define DIGIT "0123456789"

tokenizer::tokenizer() {
    /*
     * Instance variable indicating if error occurred. If so, no other actions
     * will be performed and every other call of get_token() will result to
     * T_ERR.
     */
    err = false;
}

bool tokenizer::init(const char *path_)
{
        /*
         * Open the json input file and read it's content. Initialize iterator.
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
    /*
     * Just check if the string str contains char c
     */
    if (str.find_first_of(c) == std::string::npos) {
         return false;
    } else {
        return true;
    }

}

token tokenizer::procstr()
{
    std::string str;

    str.push_back(*_iter);
    _iter++;

    /*
     * Read the string token enclosed in double quotes. Properly process
     * escaped characters. Return T_ERR if string does not comply with
     * specification at http://json.org/.
     */
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
                    || *_iter=='t' || *_iter=='/') {

                    str.push_back(*_iter);

                } else if (*_iter=='u') {

                    str.push_back(*_iter);

                    for (int i = 0; i<4; i++){
                        _iter++;
                        if (_iter == _contents.end()){
                            err = true;
                            return token(T_ERR);
                        }

                        if (this->contains(HEXNUM, *_iter)){
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

token tokenizer::procnum()
{
    std::string num;
    bool exp = false;
    bool dot = false;

    /*
     * Read the number token. Return T_ERR if it does not comply with
     * specifications at http://json.org/.
     */

    if (this->contains(FIRST, *_iter)) {
        num.push_back(*_iter);
        _iter++;
    } else if(*_iter == '0') {
        num.push_back(*_iter);
        _iter++;
        if (_iter != _contents.end() && *_iter == '.') {
            num.push_back(*_iter);
            _iter++;
        } else {
            err = true;
            return token(T_ERR);
        }
    } else if(*_iter == '-') {
        num.push_back(*_iter);
        _iter++;
        if (_iter != _contents.end() && this->contains(DIGIT, *_iter)) {
            num.push_back(*_iter);
            _iter++;
        } else {
            err = true;
            return token(T_ERR);
        }
    } else {
        err = true;
        return token(T_ERR);
    }

    for (; _iter != _contents.end(); _iter++)
    {
        switch(*_iter)
        {
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                {
                    num.push_back(*_iter);
                    break;
                }
            case '.':
                {
                    if (!dot) {
                        dot = true;
                    } else {
                        err = true;
                        return token(T_ERR);
                    }
                    num.push_back(*_iter);

                    _iter++;
                    if (_iter == _contents.end()){
                        err = true;
                        return token(T_ERR);
                    } else if (this->contains(DIGIT, *_iter)) {
                        dot = true;
                        num.push_back(*_iter);
                    } else {
                        err = true;
                        return token(T_ERR);
                    }
                    break;
                }
            case 'e': case 'E':
                {
                    if (!exp) {
                        exp = true;
                    } else {
                        err = true;
                        return token(T_ERR);
                    }
                    num.push_back(*_iter);

                    _iter++;
                    if (_iter == _contents.end()){
                        err = true;
                        return token(T_ERR);
                    } else if (*_iter == '+' || *_iter == '-') {
                        num.push_back(*_iter);
                    } else if (this->contains(DIGIT, *_iter)) {
                        dot = true;
                        num.push_back(*_iter);
                    } else {
                        err = true;
                        return token(T_ERR);
                    }
                    break;
                }
            default:
                {
                    return token(T_NUM, num);
                }
        }
    }

    err = true;
    return token(T_ERR);
}

token tokenizer::procntf()
{
    std::string tok = "";
    tok.push_back(*_iter);

    if (*_iter == 'n') {
        for (int i=0; i<3; i++) {
            if (++_iter == _contents.end()) {
                err = true;
                return token(T_ERR);
            }
            tok.push_back(*_iter);
        }

        if (tok == "null") {
            _iter++;
            return token(T_NULL);
        }

    } else if (*_iter == 't') {
        for (int i=0; i<3; i++) {
            if (++_iter == _contents.end()) {
                err = true;
                return token(T_ERR);
            }
            tok.push_back(*_iter);
        }

        if (tok == "true") {
            _iter++;
            return token(T_TRUE);
        }

    } else if (*_iter == 'f') {
        for (int i=0; i<4; i++) {
            if (++_iter == _contents.end()) {
                err = true;
                return token(T_ERR);
            }
            tok.push_back(*_iter);
        }

        if (tok == "false") {
            _iter++;
            return token(T_FALSE);
        }
    }
    return token(T_ERR);
}

token tokenizer::get_token()
{
    if (err) { // Do not continue if T_ERR has already occurred.
        return token(T_ERR);
    }

    /*
     * Iterate over input json string and with each call return next token. In
     * case of error return T_ERR.
     */
    for (; _iter != _contents.end(); _iter++)
    {
        switch(*_iter)
        {
            case '\0':
                {
                    err = true;
                    return token(T_ERR);
                }
            case ' ': case '\t': case '\n': case '\r':
                break; // skip whitespace
            case '{':
                {
                    _iter++;
                     return token(T_LBRACE);
                }
            case '}':
                {
                    _iter++;
                     return token(T_RBRACE);
                }
            case '[':
                {
                    _iter++;
                     return token(T_LBRACKET);
                }
            case ']':
                {
                    _iter++;
                     return token(T_RBRACKET);
                }
            case ':':
                {
                    _iter++;
                     return token(T_COLON);
                }
            case ',':
                {
                    _iter++;
                     return token(T_COMMA);
                }
            case '\"':
                {
                    return this->procstr();
                }
            case '-': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                {
                    return this->procnum();
                }
            case 'n': case 't': case 'f':
                {
                    return this->procntf();
                }
            default:
                err = true;
                return token(T_ERR);
        }
    }
    return token(T_EOF);
}

