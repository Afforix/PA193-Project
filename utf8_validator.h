#ifndef UTF8_VALIDATOR_H
#define UTF8_VALIDATOR_H

#include <fstream>

/**
 * @brief The utf8_validator class validates if input is valid UTF-8 document.
 */
class utf8_validator
{
    /**
     * @brief leadingOnes counts most significant ones in a byte,
     * for example in byte 11010100 there are two
     * @param c byte to examine
     * @return number of leading ones
     */
    static int leadingOnes(unsigned char c)
    {
        int i = 0;
        while ((c & 0x80) != 0)
        {
            ++i;
            c <<= 1;
        }

        return i;
    }

public:

    /**
     * @brief utf8_validator - utility class
     */
    utf8_validator() = delete;

    /**
     * Checks if given file contains valid UTF-8.
     * @param file file to read
     * @return true if contains valid UTF-8 contents
     */
    static bool validate(std::ifstream& file_);
};

#endif // UTF8_VALIDATOR_H
