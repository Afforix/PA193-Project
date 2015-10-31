#include "json_tree.h"
#include "json_value.h"

#include <iostream>
#include <regex>


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

bool
is_iso8601_datetime (std::string s)
{
    std::regex date ("^$");

    // XXX
    return true;

    if (std::regex_match (s, date)) {
        return true;
    }
    return false;
}

bool
is_user_group (std::string s)
{
  std::regex uid ("^[0-9]+$");
  std::regex user ("^[a-z_][a-z0-9_-]*[$]?$");
  std::regex user_group ("^[a-z_][a-z0-9_-]*[$]?:[0-9a-zA-Z]+$");
  std::regex uid_guid ("^[0-9]+:[0-9]+$");
  std::regex uid_group ("^[0-9]+:[a-z_][a-z0-9_-]*[$]?$");
  std::regex user_gid ("^[a-z_][a-z0-9_-]*[$]?:[0-9]+$");

  if (std::regex_match (s, uid)) {
      return true;
  }

  if (std::regex_match (s, user)) {
      return true;
  }

  if (std::regex_match (s, user_group)) {
      return true;
  }

  if (std::regex_match (s, uid_guid)) {
      return true;
  }

  if (std::regex_match (s, uid_group)) {
      return true;
  }

  if (std::regex_match (s, user_gid)) {
      return true;
  }

  return false;
}

bool
is_port_spec (std::string s)
{
    std::regex port ("^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
    std::regex udp ("^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])/udp$");
    std::regex tcp ("^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])/tcp$");

    if (std::regex_match (s, port)) {
        return true;
    }

    if (std::regex_match (s, udp)) {
        return true;
    }

    if (std::regex_match (s, tcp)) {
        return true;
    }

    return false;
}

bool
is_env_spec (std::string s)
{
    std::regex env ("^[A-Z]+=[^=]*$");

    if (std::regex_match (s, env)) {
        return true;
    }

    return false;
}

/*
// XXX ignore extra parameters or not?

//is_hexadecimal_256bits
is_iso8601_datetime
//is_architecture
//is_os
is_integer // XXX probably not necessary; change syntax analysis?
// XXX config can be null
//is_user_group
//is_port_spec
//is_env_spec

*/

bool
check_fields_root (std::shared_ptr<json_value> val_)
{
    bool ret = true;

    // XXX testing

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

/*
bool
check_fields_config (std::shared_ptr< json_value > config)
{



}*/
