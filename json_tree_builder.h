#ifndef JSON_TREE_BUILDER
#define JSON_TREE_BUILDER

#include "token.h"
#include "json_types.h"

#include <memory>
#include <stdexcept>

class json_tree_builder
{
    std::shared_ptr< json_value > _current;
    std::vector< std::shared_ptr< json_value > > _parents;

    bool _finished{false};

    bool accept_colon   {false};
    bool accept_comma   {false};
    bool accept_end     {true};
    bool accept_name    {true}; // key in object
    bool accept_value   {false};

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
            catch (const std::exception &e)
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


    bool process_first(const token &token_);
    bool insert_to_object(const token &token_);
    bool insert_to_array(const token &token_);

public:
    bool is_finished() const { return _finished; }
    std::shared_ptr< json_value > get_root() { return _current; }
    bool add(const token &token_);
};

#endif // JSON_TREE_BUILDER

