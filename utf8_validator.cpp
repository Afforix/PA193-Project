#include "utf8_validator.h"


bool utf8_validator::validate(std::ifstream &file_)
{
    if (!file_.good())
    {
        return false;
    }

    auto it = std::istreambuf_iterator<char>(file_);
    const auto END = std::istreambuf_iterator<char>();

    while (it != END)
    {
        unsigned char c = static_cast<unsigned char>(*it);

        if (c <= 0x7f)
        { // ASCII character
            ++it;
            continue;
        }

        int numOnes = leadingOnes(c);
        if (numOnes == 1 || numOnes > 4)
        { // invalid number of leading ones
            return false;
        }

        unsigned int utfChar = c & (0xff >> numOnes);
        if (utfChar == 0)
        { // unneccessarily long sequence of bytes (e.g. 11000000 00000001)
            return false;
        }

        // following bytes must start with bits 10
        for (int i = 1; i < numOnes; ++i)
        {
            utfChar = (utfChar << 6) | (c & 0x3f);
            if (++it == END || (static_cast<unsigned char>(*it) & 0xc0) != 0x80)
            {
                return false;
            }
        }

        if (utfChar > 0x10FFFF)
        { // too large number according to RFC 3629
            return false;
        }
    }

    return true;
}
