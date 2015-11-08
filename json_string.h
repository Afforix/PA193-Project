#ifndef JSON_STRING
#define JSON_STRING

#include "json_value.h"


/**
 * @brief The json_string class
 */
class json_string : public json_value
{
    const std::string _str;

protected:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << _str;
    }

public:
    json_string(const std::string& s_) : _str(s_) {}
    virtual json_type jtype() const { return json_type::J_STRING; }

    virtual std::string to_string() const
    {
        return _str;
    }

    const std::string& value() const { return _str; }
};

#endif // JSON_STRING

