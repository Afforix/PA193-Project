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
     * Instance variable indicating if error occurred. If so, no other actions
     * will be performed and every other call of get_token() will result to
     * T_ERR.
     */
    bool err;

    /**
     * @brief process string tokens
     */
    token procstr();

    /**
     * @brief process number tokens
     */
    token procnum();

    /**
     * @brief process null/true/false tokens
     */
    token procntf();

    /**
     * @brief simple function verifying if c is in str
     * @param str - reference string
     * @param c - character to test
     */
    bool contains(const std::string& str, char c);

public:

    /**
     * @brief tokenizer ctor
     */
    tokenizer();

    /**
     * @brief read the json input file
     * @param path_ to the file
     */
    bool init(const char* path_);

    /**
     * @brief get next token from the json
     * @return token
     */
    token get_token();
};

#endif // TOKENIZER_H

