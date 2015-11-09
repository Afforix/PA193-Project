#ifndef JSON_TREE_BUILDER
#define JSON_TREE_BUILDER

#include "token.h"
#include "json_types.h"

#include <memory>
#include <stack>
#include <stdexcept>

/**
 * @brief Builder accepts tokens from lexical analysis
 * and builds JSON tree structure.
 */
class json_tree_builder
{
    // currently processed object/array
    std::shared_ptr< json_value > _current;
    // recursion
    std::stack< std::shared_ptr< json_value > > _parents;

    bool _finished{false};

    bool _accept_colon   {false};
    bool _accept_comma   {false};
    bool _accept_end     {true};
    bool _accept_name    {true}; // key in object
    bool _accept_value   {false};

    /**
     * @brief Converts fort token of a value to its corresponding node,
     * e.g. '[' becomes JSON array.
     * @param t_ first token of a value
     * @return pointer to the newly created JSON value
     */
    static std::shared_ptr< json_value > to_value(const token &t_)
    {
        switch (t_.type())
        {
        case T_STR:
            return std::make_shared< json_string >(t_.text());
        case T_TRUE:
            return std::make_shared< json_bool >(true);
        case T_FALSE:
            return std::make_shared< json_bool >(false);
        case T_NULL:
            return std::make_shared< json_null >();
        case T_NUM:
            try
        {
            if (t_.text().find_first_of(".eE") == std::string::npos)
            { // integer
                return std::make_shared< json_int >(std::stoll(t_.text()));
            }
            else
            { // floating
                return std::make_shared< json_float >(std::stold(t_.text()));
            }
        }
            catch (const std::exception&)
            {
                throw std::logic_error("number too large: " + t_.text());
            }

        case T_LBRACKET:
            return std::make_shared< json_array >();
        case T_LBRACE:
            return std::make_shared< json_object >();
        default:
            return nullptr;
        }
    }


    /**
     * @brief Processes the first token, determines if the document's
     * root is of type object or array.
     *
     * @param token_ from which type of the root is determined.
     * @return true if token represents object or array
     */
    bool process_first(const token &token_);

    /**
     * @brief Tries to insert given token into the currently processed node.
     * @param token_ token
     * @return true if token was expected
     */
    bool insert_to_object(const token &token_);

    /**
     * @brief Tries to insert given token into the currently processed node.
     * @param token_ token
     * @return true if token was expected
     */
    bool insert_to_array(const token &token_);

public:
    json_tree_builder() = default;

    /**
     * @brief Tries to add token into the JSON tree in construction.
     * @param token_ token
     * @return true if token was expected
     */
    bool add(const token &token_);

    /**
     * @brief is_finished
     * @return true if valid JSON structure has been built
     */
    bool is_finished() const { return _finished; }

    /**
     * @brief Root of JSON document.
     * @return root of valid JSON document, or nullptr if valid JSON
     * has not yet been built
     */
    std::shared_ptr< json_value > get_root() const
    {
        return _finished ?_current : nullptr;
    }
};

#endif // JSON_TREE_BUILDER

