#include <string>
#include <cerrno>
#include <iostream>

#include "tokenize.h"

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
        std::cout << *_iter;
    }

    token tok(T_STR, "placeholder");
    return(tok);
}

