#ifndef JSON_VALUE
#define JSON_VALUE

#include <map>
#include <vector>
#include <memory> // shared_ptr
#include <sstream>
#include <algorithm> // for_each


/**
 * @brief The json_type enum
 */
enum class json_type
{
    J_OBJECT,
    J_ARRAY,
    J_STRING,
    J_BOOL,
    J_NULL,
    J_INT,
    J_DOUBLE
};

/**
 * @brief The json_value class
 */
class json_value
{
protected:
    static std::string indent(size_t num)
    {
        return std::string(4*num, ' ');
    }

public:

    using object_children_t = std::map< const std::string, std::shared_ptr< json_value > >;
    using array_children_t = std::vector< std::shared_ptr< json_value > >;

    json_value() = default;
    virtual ~json_value() = default;
    virtual json_type jtype() const = 0;
    virtual std::string to_string() const = 0;
    virtual void to_string(std::stringstream& stream_, size_t depth = 0) const = 0;
};


/**
 * @brief The json_object class
 */
class json_object : public json_value
{
    std::map< const std::string, std::shared_ptr< json_value > > _pairs;
    std::string _last_key;

public:
    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const
    {
        ss_ << '{';

        if (!_pairs.empty())
        {
            auto it = _pairs.begin();
            ss_ << std::endl << indent(depth_+1) << (*it).first << " : ";
            (*it).second->to_string(ss_, depth_+1);

            for (++it ; it != _pairs.end(); ++it)
            {
                ss_ << ',' << std::endl << indent(depth_+1) << (*it).first << " : ";
                (*it).second->to_string(ss_, depth_+1);
            }

            ss_ << std::endl << indent(depth_);
        }

        ss_ << '}';
    }

    virtual json_type jtype() const { return json_type::J_OBJECT; }

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

    const object_children_t& children() const { return _pairs; }

    std::shared_ptr< json_value > find(const std::string& key_) const
    {
        auto value_it = _pairs.find(key_);

        if (value_it != _pairs.end())
            return (*value_it).second;
        else
            return nullptr;
    }
};


/**
 * @brief The json_array class
 */
class json_array : public json_value
{
    std::vector< std::shared_ptr< json_value > > _values;

public:
    virtual void to_string(std::stringstream &ss_, size_t depth_ = 0) const
    {
        ss_ << '[';

        if (!_values.empty())
        {
            auto it = _values.begin();
            ss_ << std::endl << indent(depth_+1);
            (*it)->to_string(ss_, depth_+1);

            for (++it ; it != _values.end(); ++it)
            {
                ss_ << ',' << std::endl << indent(depth_+1);
                (*it)->to_string(ss_, depth_+1);
            }

            ss_ << std::endl << indent(depth_);
        }

        ss_ << ']';
    }

    virtual json_type jtype() const { return json_type::J_ARRAY; }

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

    const array_children_t& children() const { return _values; }
};


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


/**
 * @brief The json_null class
 */
class json_null : public json_value
{
public:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << to_string();
    }

    virtual json_type jtype() const { return json_type::J_NULL; }

    virtual std::string to_string() const
    {
        return "null";
    }
};


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


/**
 * @brief The json_float class
 */
class json_float : public json_value
{
    long double _val;

protected:
    virtual void to_string(std::stringstream &ss_, size_t) const
    {
        ss_ << _val;
    }

public:
    json_float(long double num) : _val(num) {}
    virtual json_type jtype() const { return json_type::J_DOUBLE; }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }

    long double value() const { return _val; }
};

#endif // JSON_VALUE

