/*
 *  PA193 Secure coding principles and practices
 *
 *  Autumn 2015    Term Project
 *
 *  Group L
 *  Bartos, Milan
 *  Kotvan, Peter
 *  Plch, Matej
 *
 */

#include <iostream>
#include "tokenizer.h"

using namespace std;

int main(int argc, char const* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./parser [json to parse]" << endl;
        return 0;
    }

    tokenizer json;

    if (!json.init(argv[1]))
    {
        std::cerr << "Unable to open " << argv[1] << ". Exitting." << endl;
        return 1;
    }

    while (true)
    {
         token tok = json.get_token();
         tok.print();
         if (tok.type() == T_EOF || tok.type() == T_ERR)
             break;

    }

    return 0;
}
