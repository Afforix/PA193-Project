#ifndef UTF8_VALIDATOR_H
#define UTF8_VALIDATOR_H

#include <fstream>

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
    utf8_validator() = delete;
    static bool validate(std::ifstream& file);
};

#endif // UTF8_VALIDATOR_H
