#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "json_value.h"

#include <map>

/**
 * @brief JSON object value.
 */
class json_object : public json_value
{
    std::map< const std::string, std::shared_ptr< json_value > > _pairs;
    std::string _last_key;

public:
    using object_children_t = std::map< const std::string, std::shared_ptr< json_value > >;

    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const;
    virtual json_type jtype() const { return json_type::J_OBJECT; }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << std::boolalpha;
        to_string(ss);

        return ss.str();
    }

    /**
     * @brief Find value in the object by its key.
     * @param key_ key to look for
     * @return object associated with the given key
     */
    std::shared_ptr< json_value > find(const std::string& key_) const;

    /**
     * @brief returns children of the object
     * @return map of children
     */
    const object_children_t& children() const { return _pairs; }

    /**
     * @brief Tells if the key is contained in the object.
     * @param key_ key to look for
     * @return true if the value was found
     */
    bool contains(const std::string &key_) const
    {
        return _pairs.find(key_) != _pairs.cend();
    }

    /**
     * Both insert methods are used during syntactic analysis,
     * having only one method for inserting key/value pair was
     * not found to be practical for parsing.
     *
     * @brief insert key into the object
     * @param s_ key
     */
    void insert(const std::string &s_)
    {
        _last_key = s_;
    }

    /**
     * Both insert methods are used during syntactic analysis,
     * having only one method for inserting key/value pair was
     * not found to be practical for parsing.
     *
     * @brief insert value for previously inserted key
     * @param val_
     */
    void insert(const std::shared_ptr< json_value > &val_)
    {
        _pairs[_last_key] = val_;
        _last_key.clear();
    }
};

#endif // JSON_OBJECT_H
