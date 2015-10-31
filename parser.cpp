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

#include "tokenizer.h"
#include "json_tree.h"
#include "analysis.h"

#include <iostream>


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
        std::cerr << "Unable to open " << argv[1] << ". Exiting." << endl;
        return 1;
    }

    int err = 0;

    json_tree root;

    while (true)
    {
         token tok = json.get_token();
         //tok.print();

         if (tok.type() == T_EOF) {
             // we are out of tokens, but tree is not finished
             if (!root.is_finished()) {
                 err = 1;
             }
             break;
         } else if (tok.type() == T_ERR) {
             err = 2;
             break;
         }

         // can't add token to the tree
         if (!root.add(tok)) {
             err = 1;
             break;
         }
    }

    // if there are any problems, write them
    if (err == 0) {
#ifndef DISABLE_SEMANTIC_ANALYSIS
        if (!check_fields_root (root.get_root())) {
			std::cerr << "Semantics is incorrect" << std::endl;
			err = 3;
		}


#endif
    } else if (err == 1) {
        std::cerr << "Syntax is incorrect" << std::endl;
    } else if (err == 2) {
        std::cerr << "Lexems are incorrect" << std::endl;
    } else {
        std::cerr << "Some unexpected error occured" << std::endl;
    }

    if (!err) {
        std::cout << root.get_root()->to_string() << std::endl;

		//printf("%x\n", root.get_root()->jtype());
	}


    return 0;
}
