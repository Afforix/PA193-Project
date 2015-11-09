#ifndef JSON_VALUE
#define JSON_VALUE

#include "json_type.h"

#include <memory> // shared_ptr
#include <sstream>

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
    json_value() = default;
    virtual ~json_value() = default;
    virtual json_type jtype() const = 0;
    virtual std::string to_string() const = 0;
    virtual void to_string(std::stringstream& stream_, size_t depth = 0) const = 0;
};

#endif // JSON_VALUE

