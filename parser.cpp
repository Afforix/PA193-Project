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
#include "tokenize.h"

using namespace std;

int main(int argc, char const* argv[])
{
    if (argc != 2) {
        cout << "Usage: ./parser [json to parse]" << endl;
        return 0;
    }

    tokenizer json;
    json.init(argv[1]); // TODO error handling

    return 0;
}
