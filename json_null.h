#ifndef JSON_NULL
#define JSON_NULL

#include "json_value.h"

/**
 * @brief The json_null class
 */
class json_null : public json_value
{
public:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << to_string();
    }

    virtual json_type jtype() const { return json_type::J_NULL; }

    virtual std::string to_string() const
    {
        return "null";
    }
};

#endif // JSON_NULL

