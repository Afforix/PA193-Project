#ifndef JSON_VALUE
#define JSON_VALUE

#include <map>
#include <vector>
#include <memory> // shared_ptr


/**
 * @brief The json_type enum
 */
enum class json_type
{
//if needed
};

/**
 * @brief The json_value class
 */
class json_value
{
public:
    json_value() = default;
    virtual ~json_value() = default;
    virtual std::string str() const = 0;
};


/**
 * @brief The json_object class
 */
class json_object : public json_value
{
    std::map< std::string, std::shared_ptr< json_value > > _pairs;

public:
    json_object();
    virtual std::string str() const { return "json_object"; }
};


/**
 * @brief The json_array class
 */
class json_array : public json_value
{
    std::vector< std::shared_ptr< json_value > > _values;

public:
    json_array() {}
    virtual std::string str() const { return "json_array"; }
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
};


/**
 * @brief The json_null class
 */
class json_null : public json_value
{
public:
    virtual std::string str() const { return "json_null"; }
};


/**
 * @brief The json_int class
 */
class json_int : public json_value
{
    long long int _val;
public:
    json_int(const std::string &s_) { /*parse string*/ }
    virtual std::string str() const { return "json_int"; }
};


/**
 * @brief The json_float class
 */
class json_float : public json_value
{
    long double _val;
public:
    json_float(const std::string &s_) { /*parse string*/ }
    virtual std::string str() const { return "json_float"; }
};

#endif // JSON_VALUE

