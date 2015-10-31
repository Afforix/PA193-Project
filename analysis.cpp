#include "json_tree.h"
#include "json_value.h"

#include <iostream>


bool
is_os (std::string os)
{
    if (os == "linux" || os == "darwin" || os == "freebsd") {
        return true;
    }
    return false;
}

bool
is_architecture (std::string arch)
{
    if (arch == "386" || arch == "amd64" || arch == "arm") {
        return true;
    }
    return false;
}

bool
is_hexadecimal_256bits (std::string s)
{
    int s_size = s.size();

    if (s_size != 32) {
        return false;
    }

    for (int i = 0; i < s_size; i++)
    {
        if ( !isxdigit(s[i]) ) {
            return false;
        }
    }
    return true;
}


/*
// XXX ignore extra parameters or not?

//is_hexadecimal_256bits
is_iso8601_datetime
//is_architecture
//is_os
is_integer // XXX probably not necessary; change syntax analysis?
// XXX config can be null
is_user_group
is_port_spec
is_env_spec

*/

bool
check_fields_root (std::shared_ptr<json_value> val_)
{
    bool ret = true;

    // XXX required in config

    // XXX - C style
    #define ROOT_ITEMS_LENGTH 9
    std::string root_items[] = {"\"id\"", "\"created\"", "\"os\"",
    "\"parent\"", "\"Size\"", "\"architecture\"", "\"author\"",
    "\"checksum\"", "\"config\""};

    if (val_->jtype() == json_type::J_OBJECT) {
        for (int i = 0; i < ROOT_ITEMS_LENGTH; i++) {
            if (!std::static_pointer_cast <json_object>(val_)->contains (root_items[i])) {
                std::cerr << "doesn't contain " << root_items[i] << std::endl;
                ret = false;
            }
        }
    } else {
        ret = false;
    }

    return ret;
}

bool
check_fields_config (json_object config)
{



}
