#ifndef JSON_NULL
#define JSON_NULL

#include "json_value.h"

/**
 * @brief JSON null.
 */
class json_null : public json_value
{
public:
    virtual json_type jtype() const { return json_type::J_NULL; }

    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << to_string();
    }

    virtual std::string to_string() const
    {
        return "null";
    }
};

#endif // JSON_NULL

