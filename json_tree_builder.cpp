#include "json_tree_builder.h"

bool json_tree_builder::process_first(const token &token_)
{
    auto jval = to_value(token_);
    if (jval == nullptr || (jval->jtype() != json_type::J_OBJECT && jval->jtype() != json_type::J_ARRAY))
    { // object or array expected
        return false;
    }
    _current = jval; // object or array
    _accept_value = _current->jtype() == json_type::J_ARRAY;

    return true;
}


bool json_tree_builder::insert_to_object(const token &token_)
{
    auto obj = std::static_pointer_cast< json_object >(_current);

    switch (token_.type())
    {
    case T_STR:
        if (_accept_name)
        {
            if (obj->contains(token_.text()))
                return false; // duplicit key name

            obj->insert(token_.text());
            _accept_colon = true;
            _accept_comma = false;
            _accept_name = false;
            _accept_value = false;
            _accept_end = false;

            return true;
        }
        else if (_accept_value)
        {
            auto str = to_value(token_);
            obj->insert(str);

            _accept_colon = false;
            _accept_comma = true;
            _accept_name = false;
            _accept_value = false;
            _accept_end = true;

            return true;
        }
        else
        { // unexpected token
            return false;
        }
        break;
    case T_COLON:
        if (_accept_colon)
        {
            _accept_colon = false;
            _accept_comma = false;
            _accept_end = false;
            _accept_name = false;
            _accept_value = true;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_LBRACE: // new object
        if (_accept_value)
        {
            auto new_obj = to_value(token_);
            _parents.push(_current);
            _current = new_obj;
            obj->insert(new_obj);

            _accept_colon = false;
            _accept_comma = false;
            _accept_end = true;
            _accept_name = true;
            _accept_value = false;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_COMMA:
        if (_accept_comma)
        {
            _accept_colon = false;
            _accept_comma = false;
            _accept_end = true; // not valid JSON
            _accept_name = true;
            _accept_value = false;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_LBRACKET: // new array
        if (_accept_value)
        {
            auto new_arr = to_value(token_);
            _parents.push(_current);
            _current = new_arr;
            obj->insert(new_arr);

            _accept_colon = false;
            _accept_comma = false;
            _accept_end = true;
            _accept_name = false;
            _accept_value = true;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_RBRACE:
        if (_accept_end)
        {
            if (_parents.empty())
            { // parsing successfully finished
                _finished = true;
                return true;
            }

            _current = _parents.top();
            _parents.pop();

            _accept_colon = false;
            _accept_comma = true;
            _accept_end = true;
            _accept_name = true;
            _accept_value = _current->jtype() == json_type::J_ARRAY;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_TRUE:
    case T_FALSE:
    case T_NULL:
    case T_NUM:
        if (_accept_value)
        {
            obj->insert(to_value(token_));

            _accept_colon = false;
            _accept_comma = true;
            _accept_end = true;
            _accept_name = false;
            _accept_value = false;

            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false; // unexpected token
    }

    return false; // should not get here
}


bool json_tree_builder::insert_to_array(const token &token_)
{
    auto arr = std::static_pointer_cast< json_array >(_current);

    switch (token_.type())
    {
    case T_COMMA:
        if (_accept_comma)
        {
            _accept_comma = false;
            _accept_end = false;
            _accept_value = true;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_RBRACKET:
        if (_accept_end)
        {
            if (_parents.empty())
            { // parsing successfully finished
                _finished = true;
                return true;
            }

            _current = _parents.top();
            _parents.pop();

            _accept_colon = false;
            _accept_comma = true;
            _accept_end = true;
            _accept_name = false;
            _accept_value = _current->jtype() == json_type::J_ARRAY;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_LBRACE:
    case T_LBRACKET:
        if (_accept_value)
        {
            auto new_val = to_value(token_);
            _parents.push(_current);
            _current = new_val;
            arr->insert(new_val);

            _accept_colon = false;
            _accept_comma = false;
            _accept_end = true;
            _accept_name = true;
            _accept_value = new_val->jtype() == json_type::J_ARRAY;

            return true;
        }
        else
        {
            return false;
        }
        break;
    case T_STR:
    case T_NUM:
    case T_TRUE:
    case T_FALSE:
    case T_NULL:
        if (_accept_value)
        {
            arr->insert(to_value(token_));
            _accept_comma = true;
            _accept_end = true;
            _accept_value = false;

            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false; // unexpected token
    }

    return false; // should not get here
}

/**
 * @brief add
 * @param token_
 * @return true if token is expected
 */
bool json_tree_builder::add(const token &token_)
{
    if (_finished) // do not accept new tokens
        return false;

    if (_current == nullptr)
    { // first token
        return process_first(token_);
    }
    else if (_current->jtype() == json_type::J_OBJECT)
    {
        return insert_to_object(token_);
    }
    else
    {
        return insert_to_array(token_);
    }
}
