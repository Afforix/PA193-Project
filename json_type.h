#ifndef JSON_TYPE
#define JSON_TYPE

/**
 * @brief Enum representing types of JSON nodes.
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

#endif // JSON_TYPE

