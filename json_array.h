#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "json_value.h"

#include <vector>

/**
 * @brief JSON array value.
 */
class json_array : public json_value
{
    std::vector< std::shared_ptr< json_value > > _values;

public:
    using array_children_t = std::vector< std::shared_ptr< json_value > >;

    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const;
    virtual json_type jtype() const { return json_type::J_ARRAY; }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << std::boolalpha;
        to_string(ss);

        return ss.str();
    }

    /**
     * @brief children
     * @return values contained in the JSON array
     */
    const array_children_t& children() const { return _values; }

    /**
     * @brief insert
     * @param val_ value to be inserted into the JSON array
     */
    void insert(const std::shared_ptr< json_value > &val_)
    {
        _values.push_back(val_);
    }
};

#endif // JSON_ARRAY_H
