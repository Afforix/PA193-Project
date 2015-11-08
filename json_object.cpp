#include "json_object.h"


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
    auto value_it = _pairs.find(key_);

    if (value_it != _pairs.end())
        return (*value_it).second;
    else
        return nullptr;
}
