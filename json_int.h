#ifndef JSON_INT
#define JSON_INT

#include "json_value.h"

/**
 * @brief JSON integer.
 */
class json_int : public json_value
{
    long long int _val;

public:
    explicit json_int(long long int num) : _val(num) {}
    virtual json_type jtype() const { return json_type::J_INT; }

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
     * @return integer
     */
    long long int value() const { return _val; }
};

#endif // JSON_INT

