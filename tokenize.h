#include <string>
#include <fstream>

enum token_type {
    T_EOF,
    T_ERR,
    T_LBRACE,
    T_RBRACE,
    T_LBRACKET,
    T_RBRACKET,
    T_LPAREN,
    T_RPAREN,
    T_COLON,
    T_COMMA,
    T_STR,
    T_NUM
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
};

class tokenizer
{
    std::ifstream _ifs;

public:

    /*
     * @brief tokenizer cleanup
     */
    ~tokenizer();

    void init(const char* path_);

    /**
     * @brief get next token from the json
     * @return token
     */
    token get_token();
};

