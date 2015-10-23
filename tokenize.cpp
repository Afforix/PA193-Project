#include <string>
#include <cerrno>

#include "tokenize.h"

void tokenizer::init(const char* path_)
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
        }

        _iter = _contents.begin();
}

token tokenizer::get_token()
{
    token tok(T_STR, "placeholder");

    return(tok);
}

