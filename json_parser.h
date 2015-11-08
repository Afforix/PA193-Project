#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "tokenizer.h"
#include "json_tree_builder.h"

#include <stdexcept>
#include <memory>

class json_parser
{
public:
    json_parser() = delete;
    static std::shared_ptr< json_value > parseFile(const std::string &name_)
    {
        tokenizer t;
        t.init(name_);

        json_tree_builder builder;

        while (true)
        {
            token tok = t.get_token();

            if (tok.type() == T_EOF) {
                if (builder.is_finished())
                {
                    break;
                }
                else
                { // we are out of tokens, but tree is not finished
                    throw std::logic_error("unexpected end of file");
                }
            } else if (tok.type() == T_ERR) {
                throw std::logic_error("invalid contents in JSON file");
            }

            // can't add token to the tree
            if (!builder.add(tok)) {
                throw std::logic_error("invalid JSON structure, unexpected token: " + tok.to_string());
            }
        }

        return builder.get_root();
    }
};

#endif // JSON_PARSER_H
