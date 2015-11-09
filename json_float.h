#ifndef JSON_FLOAT
#define JSON_FLOAT

#include "json_value.h"

/**
 * @brief JSON floating point number.
 */
class json_float : public json_value
{
    long double _val;

public:
    explicit json_float(long double num) : _val(num) {}
    virtual json_type jtype() const { return json_type::J_DOUBLE; }

    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << _val;
    }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }

    /**
     * @brief returns contained value
     * @return floating point number
     */
    long double value() const { return _val; }
};

#endif // JSON_FLOAT

