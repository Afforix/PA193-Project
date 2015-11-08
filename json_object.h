#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "json_value.h"

/**
 * @brief The json_object class
 */
class json_object : public json_value
{
    std::map< const std::string, std::shared_ptr< json_value > > _pairs;
    std::string _last_key;

public:
    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const;
    std::shared_ptr< json_value > find(const std::string& key_) const;

    virtual json_type jtype() const { return json_type::J_OBJECT; }

    const object_children_t& children() const { return _pairs; }

    bool contains(const std::string &key_) const
    {
        return _pairs.find(key_) != _pairs.cend();
    }

    void insert(const std::string &s_)
    {
        _last_key = s_;
    }

    void insert(const std::shared_ptr< json_value > &val_)
    {
        _pairs[_last_key] = val_;
        _last_key.clear();
    }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << std::boolalpha;
        to_string(ss);

        return ss.str();
    }

};

#endif // JSON_OBJECT_H
