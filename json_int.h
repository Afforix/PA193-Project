#ifndef JSON_INT
#define JSON_INT

#include "json_value.h"

/**
 * @brief The json_int class
 */
class json_int : public json_value
{
    long long int _val;

protected:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << _val;
    }

public:
    json_int(long long int num) : _val(num) {}
    virtual json_type jtype() const { return json_type::J_INT; }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }

    long long int value() const { return _val; }
};

#endif // JSON_INT

