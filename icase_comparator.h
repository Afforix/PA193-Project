#ifndef ICASE_COMPARATOR
#define ICASE_COMPARATOR

#include <cctype>
#include <algorithm>

/**
 * @brief The icase_comparator class privides case insensitive
 * comparator of strings.
 */
class icase_comparator
{
    /**
     * @brief Case insensitive string comparison.
     * @param a_ string
     * @param b_ string
     * @return true if the the first string is case insensitive "smaller"
     */
    static bool icase_less(const std::string &a_, const std::string &b_)
    {
        return std::lexicographical_compare(a_.begin(), a_.end(),
                                            b_.begin(), b_.end(),
                                            [](char ca_, char cb_)
        {
            return std::tolower(ca_) < std::tolower(cb_);
        });
    }

public:
    bool operator ()(const std::string &a_, const std::string &b_) const
    {
        return icase_less(a_, b_);
    }
};

#endif // ICASE_COMPARATOR

