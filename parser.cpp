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

#include "json_parser.h"
#include "analysis.h"

#include <iostream>


int main(int argc, char const* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./parser [json to parse]" << std::endl;
        return 0;
    }

    std::shared_ptr< json_value > root;
    try
    {
        root = json_parser::parseFile(argv[1]);
    }
    catch (const std::exception &e)
    { // parsing failed
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    if (!do_semantic_analysis (root)) {
        std::cerr << "Semantics is incorrect" << std::endl;
        return 2;
    }

    std::cout << root->to_string() << std::endl;

    return 0;
}

