#include "json_object.h"


class json_object::icase_lookup
{
    const std::string _string;

    /**
     * @brief Case insensitive string equality test.
     * @param a_ string
     * @param b_ string
     * @return true if the strings are case insensitive equal
     */
    static bool icase_equal(const std::string &a_, const std::string &b_)
    {
        return std::equal(a_.begin(), a_.end(), b_.begin(),
                          [](char c1_, char c2_)
        {
            return std::tolower(c1_) == std::tolower(c2_);
        });
    }

public:
    icase_lookup(const std::string &s_)
        : _string(s_)
    {}

    bool operator ()(const object_children_t::value_type &val_)
    {
        return icase_equal(_string, val_.first);
    }
};


void json_object::to_string(std::stringstream &ss_, size_t depth_) const
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


std::shared_ptr< json_value > json_object::find(const std::string& key_) const
{
    auto value_it = std::find_if(_pairs.begin(),
                                 _pairs.end(),
                                 icase_lookup(key_));

    if (value_it != _pairs.end())
        return (*value_it).second;
    else
        return nullptr;
}


