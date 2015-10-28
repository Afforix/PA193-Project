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
    static constexpr const char *TAB = "    ";
    static void indent(std::string &str_)
    {

    }

public:
    json_value() = default;
    virtual ~json_value() = default;
    virtual std::string str() const = 0;
    virtual json_type jtype() const = 0;
    virtual std::string to_string() const = 0;
};


/**
 * @brief The json_object class
 */
class json_object : public json_value
{
    std::map< const std::string, std::shared_ptr< json_value > > _pairs;
    std::string _last_key;

public:
    virtual std::string str() const { return "json_object"; }
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
        ss << std::boolalpha << '{';

        if (!_pairs.empty())
        {
            auto it = _pairs.begin();
            ss << std::endl << (*it).first << " : " << (*it).second->to_string();
            ++it;

            std::for_each(it,
                          _pairs.end(),
                          [&ss](const auto &v_)
            {
                ss << ',' << std::endl << v_.first << " : " << v_.second->to_string();
            });
            ss << std::endl;
        }
        ss << '}';

        return ss.str();
    }
};


/**
 * @brief The json_array class
 */
class json_array : public json_value
{
    std::vector< std::shared_ptr< json_value > > _values;

public:
//    json_array() {}
    virtual std::string str() const { return "json_array"; }
    virtual json_type jtype() const { return json_type::J_ARRAY; }

    void insert(const std::shared_ptr< json_value > &val_)
    {
        _values.push_back(val_);
    }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << std::boolalpha << '[';

        if (!_values.empty())
        {
            auto it = _values.begin();
            ss << std::endl << *it;
            ++it;

            std::for_each(it,
                          _values.end(),
                          [&ss](const auto &v_)
            {
                ss << ',' << std::endl << v_->to_string();
            });
            ss << std::endl;
        }

        ss << ']';

        return ss.str();
    }
};


/**
 * @brief The json_string class
 */
class json_string : public json_value
{
    const std::string _str;
public:
    json_string(const std::string& s_) : _str(s_) {}
    virtual std::string str() const { return "json_string"; }
    virtual json_type jtype() const { return json_type::J_STRING; }

    virtual std::string to_string() const
    {
        return _str;
    }
};


/**
 * @brief The json_bool class
 */
class json_bool : public json_value
{
    const bool _val;
public:
    json_bool(bool b_) : _val(b_) {}
    virtual std::string str() const { return "json_bool"; }
    virtual json_type jtype() const { return json_type::J_BOOL; }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }
};


/**
 * @brief The json_null class
 */
class json_null : public json_value
{
public:
    virtual std::string str() const { return "json_null"; }
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
public:
    json_int(long long int num) : _val(num) {}
    virtual std::string str() const { return "json_int"; }
    virtual json_type jtype() const { return json_type::J_INT; }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }
};


/**
 * @brief The json_float class
 */
class json_float : public json_value
{
    long double _val;
public:
    json_float(long double num) : _val(num) {}
    virtual std::string str() const { return "json_float"; }
    virtual json_type jtype() const { return json_type::J_DOUBLE; }

    virtual std::string to_string() const
    {
        return std::to_string(_val);
    }
};

#endif // JSON_VALUE

