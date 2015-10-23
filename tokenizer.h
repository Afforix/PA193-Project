#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

#include <string>

class tokenizer
{

private:
    std::string _contents;
    std::string::iterator _iter;

    /**
     * @brief process string tokens
     * @param iterator
     */
    token procstr();

public:

    /**
     * @brief read the json input file
     * @param path to the file
     */
    bool init(const char* path_);

    /**
     * @brief get next token from the json
     * @return token
     */
    token get_token();
};

#endif // TOKENIZER_H
