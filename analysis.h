#include "json_value.h"

#include <iostream>

bool check_fields_root (std::shared_ptr<json_value> val_);
bool check_fields_config (json_object config);

bool is_os (std::string os);
bool is_architecture (std::string arch);
bool is_hexadecimal_256bits (std::string s);
