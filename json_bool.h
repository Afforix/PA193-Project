#ifndef JSON_BOOL
#define JSON_BOOL

#include "json_value.h"

/**
 * @brief The json_bool class
 */
class json_bool : public json_value
{
    const bool _val;

protected:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << _val;
    }

public:
    json_bool(bool b_) : _val(b_) {}
    virtual json_type jtype() const { return json_type::J_BOOL; }

    virtual std::string to_string() const
    {
        return _val ? "true" : "false";
    }

    bool value() const { return _val; }
};

#endif // JSON_BOOL

