#include "json_array.h"


void json_array::to_string(std::stringstream &ss_, size_t depth_) const
{
    ss_ << '[';

    if (!_values.empty())
    {
        auto it = _values.begin();
        ss_ << std::endl << indent(depth_+1);
        (*it)->to_string(ss_, depth_+1);

        for (++it ; it != _values.end(); ++it)
        {
            ss_ << ',' << std::endl << indent(depth_+1);
            (*it)->to_string(ss_, depth_+1);
        }

        ss_ << std::endl << indent(depth_);
    }

    ss_ << ']';
}
