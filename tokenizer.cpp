#include "tokenizer.h"
#include "utf8_validator.h"

#include <cctype>
#include <stdexcept>

static const std::string FIRST  = "123456789";
static const std::istreambuf_iterator<char> END{};


void tokenizer::init(const std::string &path_)
{
    _contents.open(path_);
    if (!_contents.good())
    {
        throw std::runtime_error("unable to open file " + path_);
    }

    if (!utf8_validator::validate(_contents))
    {
        _contents.close();
        throw std::logic_error("invalid UTF-8 encoding");
    }

    // rewind
    _contents.clear();
    _contents.seekg(0, std::ios::beg);

    _iter = std::istreambuf_iterator<char>(_contents);
}


bool tokenizer::contains(const std::string& str_, char c_)
{
    return str_.find(c_) != std::string::npos;
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
    for (; _iter != END; ++_iter)
    {
        if (*_iter >= 0 && *_iter <= 0x1F)
        { // control characters are not allowed in strings
            break;
        }

        switch(*_iter)
        {
        case '\"':
            str.push_back(*_iter);
            _iter++;

            return token(T_STR, str);
        case '\\':
            str.push_back(*_iter);
            _iter++;
            if (_iter == END) {
                _err = true;
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
                    if (_iter == END){
                        _err = true;
                        return token(T_ERR);
                    }

                    if (std::isxdigit(*_iter)){
                        str.push_back(*_iter);
                    } else {
                        _err = true;
                        return token(T_ERR);
                    }
                }

            } else {
                _err = true;
                return token(T_ERR);
            }
            break;
        default:
            str.push_back(*_iter);
            break;
        }
    }

    _err = true;
    return token(T_ERR);
}


token tokenizer::procnum()
{
    std::string num;
    bool exp = false;
    bool dot = false;
    bool epm = false;

    /*
     * Read the number token. Return T_ERR if it does not comply with
     * specifications at http://json.org/.
     */
    if(*_iter == '-') {
        num.push_back(*_iter);
        _iter++;
        if (_iter == END) {
            _err = true;
            return token(T_ERR);
        }

        if (!std::isdigit(*_iter)) {
            _err = true;
            return token(T_ERR);
        }
    }

    if (this->contains(FIRST, *_iter)) {
        num.push_back(*_iter);
        _iter++;
    } else if(*_iter == '0') {
        num.push_back(*_iter);
        _iter++;
        if (_iter == END) {
            _err = true;
            return token(T_ERR);
        }

        if (this->contains("eE", *_iter)) {
            num.push_back(*_iter);
            exp = true;
            dot = true;
            _iter++;

            if (_iter == END){
                _err = true;
                return token(T_ERR);
            } else if (*_iter == '+' || *_iter == '-') {
                epm = true;
                num.push_back(*_iter);
                _iter++;
                if (_iter == END) {
                    _err = true;
                    return token(T_ERR);
                }
                if (std::isdigit(*_iter)) {
                    num.push_back(*_iter);
                    _iter++;
                } else {
                    _err = true;
                    return token(T_ERR);
                }
            } else if (std::isdigit(*_iter)) {
                num.push_back(*_iter);
                epm = true;
                _iter++;
            } else {
                _err = true;
                return token(T_ERR);
            }
        } else if (*_iter == '.') {
            num.push_back(*_iter);
            dot = true;
            _iter++;
            if (_iter == END) {
                _err = true;
                return token(T_ERR);
            }

            if (std::isdigit(*_iter)) {
                num.push_back(*_iter);
                _iter++;
            } else {
                _err = true;
                return token(T_ERR);
            }
        } else if (!std::isalnum(*_iter)) {
            return token(T_NUM, num);
        } else {
            _err = true;
            return token(T_ERR);
        }
    } else {
        _err = true;
        return token(T_ERR);
    }

    for (; _iter != END; ++_iter)
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
            if (!dot && !exp) {
                dot = true;
            } else {
                _err = true;
                return token(T_ERR);
            }
            num.push_back(*_iter);

            _iter++;
            if (_iter == END){
                _err = true;
                return token(T_ERR);
            } else if (std::isdigit(*_iter)) {
                dot = true;
                num.push_back(*_iter);
            } else {
                _err = true;
                return token(T_ERR);
            }
            break;
        }
        case 'e': case 'E':
        {
            if (!exp) {
                exp = true;
            } else {
                _err = true;
                return token(T_ERR);
            }
            num.push_back(*_iter);

            _iter++;
            if (_iter == END){
                _err = true;
                return token(T_ERR);
            } else if (*_iter == '+' || *_iter == '-') {
                epm = true;
                num.push_back(*_iter);
                _iter++;
                if (_iter == END) {
                    _err = true;
                    return token(T_ERR);
                }
                if (std::isdigit(*_iter)) {
                    num.push_back(*_iter);
                } else {
                    _err = true;
                    return token(T_ERR);
                }
            } else if (std::isdigit(*_iter)) {
                dot = true;
                num.push_back(*_iter);
            } else {
                _err = true;
                return token(T_ERR);
            }
            break;
        }
        case '+': case '-':
        {
            if (exp && !epm) {
                epm = true;
                num.push_back(*_iter);
            } else {
                _err = true;
                return token(T_ERR);
            }
        }
        default:
        {
            return token(T_NUM, num);
        }
        }
    }

    _err = true;
    return token(T_ERR);
}


token tokenizer::procntf()
{
    std::string tok = "";
    tok.push_back(*_iter);

    if (*_iter == 'n') {
        for (int i=0; i<3; i++) {
            if (++_iter == END) {
                _err = true;
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
            if (++_iter == END) {
                _err = true;
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
            if (++_iter == END) {
                _err = true;
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
    if (_err) { // Do not continue if T_ERR has already occurred.
        return token(T_ERR);
    }

    /*
     * Iterate over input json string and with each call return next token. In
     * case of error return T_ERR.
     */
    for (; _iter != END; ++_iter)
    {
        // skip whitespace
        if (std::isspace(*_iter)) {
            continue;
        }

        switch(*_iter)
        {
        case '\0':
        {
            _err = true;
            return token(T_ERR);
        }
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
            _err = true;
            return token(T_ERR);
        }
    }

    return token(T_EOF);
}

