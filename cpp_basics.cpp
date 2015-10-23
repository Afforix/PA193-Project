#include "token.h"

// you can use namespaces to hide things from global scope
namespace examples
{

// you can use namespaces to aggregate constants
namespace constants
{
    static const int zero = 0;
    static const std::string arch = "ARM";
}

void constructors()
{
    // usage of constants
    if (constants::zero) {}

    // create local variable
    token simple_token(T_ERR);
    // basicaly same as previous, but longer to write
    token simple_token2 = token(T_ERR);
    // Java style, try to avoid this, because you have to
    // free the pointer manually
    token *simple_token3 = new token(T_ERR);
    delete simple_token3;

    // token with string
    token some_string(T_STR, "loaded_string");

    // get type of the token
    token_type tt = simple_token.type();

    if (tt) {} // to remove unused var warning...

    // get string of the string token
    std::string txt = some_string.text();

    // this is programmer's mistake, result will be empty string
    // because simple_token should not be of type T_STRING
    std::string empty = simple_token.text();
}

// token will be copied, including contained string,
// mostly we do not want this
void pass_data(token /*t*/) {}

// token will be passed as reference, which is basically
// pointer, but you do not need to write * to access the value
void pass_data2(token& t)
{   // change will propagate outside of the function
    t = token(T_ERR);
}

// constant reference, you can't change the given value
void pass_data3(const token& /*t*/) {}

// generally speaking returns copy of the token, but
// in this example compiler creates the data directly where it will be returned
// so it doesn't need to create copy - more speed
token return_data() { return token(T_ERR); }
// other types of return types:
// token& - returns reference, no copy created
// const token& - returns constant reference, no copy created, unmodifiable

}
