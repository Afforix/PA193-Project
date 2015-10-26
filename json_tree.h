#ifndef JSON_TREE
#define JSON_TREE

#include "token.h"

class json_tree
{
public:
    bool add(const token &token_) { return false; }
    bool is_finished() const { return false; }
};

#endif // JSON_TREE

