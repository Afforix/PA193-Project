
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

/*
// XXX ignore extra parameters?

is_hexadecimal_256bits
is_iso8601_datetime
is_architecture
is_os
is_integer
// XXX config can be null
is_user_group
is_port_spec
is_env_spec

*/

bool
check_fields (std::shared_ptr<json_value> val_)
{
	bool ret = true;

	// XXX test
	if (is_os ("freebsd")) {
		std::cout << "freebsd je" << std::endl;
	}

	if (is_os ("linux")) {
		std::cout << "linux je" << std::endl;
	}

	if (is_os ("darwin")) {
		std::cout << "darwin je" << std::endl;
	}

	if (is_os ("lunex")) {
		std::cout << "lunex je" << std::endl;
	} else {
		std::cout << "lunex neni" << std::endl;
	}

	// XXX required in config

	// XXX - C style
	#define REQ_LENGTH 9
	std::string required_in_root[] = {"\"id\"", "\"created\"", "\"os\"",
	"\"parent\"", "\"Size\"", "\"architecture\"", "\"author\"",
	"\"checksum\"", "\"config\""};

	if (val_->jtype() == json_type::J_OBJECT) {
		for (int i = 0; i < REQ_LENGTH; i++) {
			if (!std::static_pointer_cast <json_object>(val_)->contains (required_in_root[i])) {
				std::cerr << "doesn't contain " << required_in_root[i] << std::endl;
				ret = false;
			}
		}
	} else {
		ret = false;
	}

	return ret;
}


