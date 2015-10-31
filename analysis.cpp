
#include "json_tree.h"
#include "json_value.h"

#include <iostream>

bool
check_fields (std::shared_ptr<json_value> val_)
{
	bool ret = true;

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


