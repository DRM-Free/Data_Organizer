/*
 * Params_Parser.h
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */

#ifndef PARAMS_PARSER_H_
#define PARAMS_PARSER_H_

#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <utility>      // std::pair, std::make_pair
#include <string>
/**
 * @return first char* is input path
 * @return first char* is output path
 *
 */
std::pair<char*,char*> parse_params(int argc, char* argv[]) {
    if (argc < 5)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Not enough arguments." << std::endl <<"Usage is -in <data_location> -out <output_location>\n"; // Inform the user of how to use the program
        std::cin.get(); //Just to keep the console open after execution so user can read error msg
        exit(0);
    				}
    if (argc > 5)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
            std::cout << "Too many arguments." << std::endl <<"Usage is -in <data_location> -out <output_location>\n"; // Inform the user of how to use the program
            std::cout << argc << " arguments were given " << std::endl;
            std::cin.get();
            exit(0);
        			}
    else
    		{ // if we got enough parameters...
        char* dataPath;
        char* outPath;
        for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
                                          * Note that we're starting on 1 because we don't need to know the
                                          * path of the program, which is stored in argv[0] */
            if (i + 1 != argc) // Check that we haven't finished parsing already
            {
                if (argv[i] == (std::string)"-in")
                {
                    // We know the next argument *should* be the path to data:
                	dataPath = argv[i + 1];
                	++i;
                }
                else if (argv[i] == (std::string)"-out")
                {
                	outPath = argv[i + 1];
                	++i;
                }
                else
                {
                    std::cout << "Invalid argument :"<< argv[i] << std::endl; // Inform the user of how to use the program
                    std::cout << "Usage is -in <data_location> -out <output_location>"; // Inform the user of how to use the program

            std::cin.get();
                    exit(0);
                }
            }
        }
std::pair<char*,char*> ret=std::make_pair(dataPath,outPath);
return ret;
    }
}




#endif /* PARAMS_PARSER_H_ */
