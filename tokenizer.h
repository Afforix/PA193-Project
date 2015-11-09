#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

#include <string>

/**
 * @brief The tokenizer class performs lexical analysis and converts
 * stream of characters into tokens.
 */
class tokenizer
{

private:
    /**
     * @brief _contents file we read
     */
    std::ifstream _contents;
    /**
     * @brief _iter position in the file
     */
    std::istreambuf_iterator<char> _iter;


    /**
     * Instance variable indicating if error occurred. If so, no other actions
     * will be performed and every other call of get_token() will result to
     * T_ERR.
     */
    bool _err;

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
     * @brief simple function verifying if character c_ is in str_
     * @param str_ string
     * @param c_ character to test
     * @return true if str_ contains c_
     */
    bool contains(const std::string& str_, char c_);

public:

    /**
     * @brief tokenizer ctor
     */
    tokenizer() : _err(false) {}

    /**
     * @brief Open the JSON input file.
     * @param path_ path to the file
     */
    void init(const std::string &path_);

    /**
     * @brief get next token from the json
     * @return token
     */
    token get_token();
};

#endif // TOKENIZER_H

