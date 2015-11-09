#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <fstream>

/**
 * @brief Types of tokens.
 */
enum token_type {
    T_EOF,      // End Of File
    T_ERR,      // Error
    T_LBRACE,   // { left brace
    T_RBRACE,   // } right brace
    T_LBRACKET, // [ left bracket
    T_RBRACKET, // ] right bracket
    T_COLON,    // : colon
    T_COMMA,    // , comma
    T_STR,      // string enclosed in double quotes
    T_NUM,      // number
    T_NULL,     // null
    T_TRUE,     // true
    T_FALSE     // false
};

/**
 * @brief Tokens containing type and possibly string value.
 */
class token
{
    token_type _type; // bracket, string...
    std::string _text; // text of string, number

public:

    /**
     * @brief token ctor for non-strings/non-numbers
     * @param type_ non-string/non-number token
     */
    explicit token(token_type type_)
        : _type(type_)
    {}

    /**
     * @brief token ctor for strings and numbers
     * @param type_ token type
     * @param text_ value
     */
    token(token_type type_, const std::string& text_)
        : _type(type_), _text(text_)
    {}

    /**
     * @brief type of token
     * @return token type
     */
    token_type type() const { return _type; }

    /**
     * @brief text value
     * @return text of string/number token
     */
    const std::string& text() const { return _text; }

    /**
     * @brief Converts token to string.
     */
    std::string to_string();
};

#endif // TOKEN_H
