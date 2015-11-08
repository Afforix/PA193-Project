#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "json_value.h"

/**
 * @brief The json_array class
 */
class json_array : public json_value
{
    std::vector< std::shared_ptr< json_value > > _values;

public:
    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const;

    virtual json_type jtype() const { return json_type::J_ARRAY; }

    const array_children_t& children() const { return _values; }

    void insert(const std::shared_ptr< json_value > &val_)
    {
        _values.push_back(val_);
    }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << std::boolalpha;
        to_string(ss);

        return ss.str();
    }
};

#endif // JSON_ARRAY_H
