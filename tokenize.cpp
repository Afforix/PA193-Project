#include "tokenize.h"

void tokenizer::init(const char* path_)
{
        _ifs.open(path_, std::ifstream::in);
}

tokenizer::~tokenizer()
{
    if (_ifs.is_open())
        _ifs.close();
}

