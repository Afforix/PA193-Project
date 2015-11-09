#ifndef JSON_VALUE
#define JSON_VALUE

#include "json_type.h"

#include <memory> // shared_ptr
#include <sstream>

/**
 * @brief Abstract class with interface for JSON values.
 */
class json_value
{
protected:
    /**
     * @brief indent
     * @param num size of indent
     * @return creates indentation spaces
     */
    static std::string indent(size_t num_)
    {
        return std::string(4*num_, ' ');
    }

public:
    json_value() = default;
    virtual ~json_value() = default;

    /**
     * @brief Identifies what type is stored in this JSON node.
     * @return type of node
     */
    virtual json_type jtype() const = 0;

    /**
     * @brief Converts json value to string representation.
     * @return pretty print string
     */
    virtual std::string to_string() const = 0;

    /**
     * @brief Converts json value to string representation.
     * @param ss_ stream where string will be stored
     * @param depth_ indentation
     */
    virtual void to_string(std::stringstream& stream_, size_t depth_ = 0) const = 0;
};

#endif // JSON_VALUE

