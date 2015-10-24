#include <string>
#include <fstream>

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

class token
{
    token_type _type; // bracket, string...
    std::string _text; // text of string

public:

    /**
     * @brief token ctor for non-strings
     * @param type_
     */
    token(token_type type_)
        : _type(type_)
    {}

    /**
     * @brief token ctor for strings
     * @param type_
     * @param text_
     */
    token(token_type type_, const std::string& text_)
        : _type(type_), _text(text_)
    {}

    /**
     * @brief type
     * @return token type
     */
    token_type type() const { return _type; }

    /**
     * @brief text
     * @return text of string token
     */
    const std::string& text() const { return _text; }

    /**
     * @brief print contents of token
     */
    void print();
};

