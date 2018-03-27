/*
 * Params_Parser.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: anael
 */

#include "Params_Parser.h"

parsed_Params parse_params(int argc, char* argv[]) {
	parsed_Params par;
	par.inPath="";
	par.outPath="";
    if (argc < 5)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Not enough arguments." << std::endl <<"Usage is -in <data_location> -out <output_location>"<<std::endl; // Inform the user of how to use the program
        std::cout << "optionnal argument : -ref sym or -ref cp defines reference behaviour (copies full files or creates symbolic links)"<<std::endl; // Inform the user of how to use the program
        std::cin.get(); //Just to keep the console open after execution so user can read error msg
        exit(0);
    				}
    if (argc > 7)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
            std::cout << argc << " arguments were given " << std::endl;
        std::cout << "Too many arguments." << std::endl <<"Usage is -in <data_location> -out <output_location>"<<std::endl; // Inform the user of how to use the program
        std::cout << "optionnal argument : -ref sym or -ref cp defines reference behaviour (copies full files or creates symbolic links)"<<std::endl; // Inform the user of how to use the program
            std::cin.get();
            exit(0);
        			}
    else
    		{ // if we got enough parameters...
        for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
                                          * Note that we're starting on 1 because we don't need to know the
                                          * path of the program, which is stored in argv[0] */
            if (i + 1 != argc) // Check that we haven't finished parsing already
            {
                if (argv[i] == (std::string)"-in")
                {
                    // We know the next argument *should* be the path to data:
                	par.inPath = argv[i + 1];
                	++i;
                }
                else if (argv[i] == (std::string)"-out")
                {
                	par.outPath = argv[i + 1];
                	++i;
                }
                else if (argv[i] == (std::string)"-ref")
                                {
                                	par.ref=argv[i + 1];
                                	if((par.ref!="cp")and(par.ref!="sym")){
                                		        std::cout << "optionnal argument : -ref sym or -ref cp defines reference behaviour (copies full files or creates symbolic links)"<<std::endl; // Inform the user of how to use the program
                                		std::cout<<"Reference parameter -ref "<< argv[i + 1]<<" not supported. Symbolic links will be used"<<std::endl;
                                		par.ref="sym";
                                	}
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
        if((par.inPath=="")or(par.outPath=="")){
        	std::cout<<"Invalid arguments"<<std::endl<<"Usage is -in <data_location> -out <output_location>"<<std::endl; // Inform the user of how to use the program
            std::cout << "optionnal argument : -ref sym or -ref cp defines reference behaviour (copies full files or creates symbolic links)"<<std::endl; // Inform the user of how to use the program
                std::cin.get();
                exit(0);
        }
        if(par.ref==""){
                                        		        std::cout << "optionnal argument : -ref sym or -ref cp defines reference behaviour (copies full files or creates symbolic links"<<std::endl; // Inform the user of how to use the program
                                        		std::cout<<"Reference parameter -ref not provided. Symbolic links will be used"<<std::endl;
                                        		par.ref="sym";
}return par;
}
}

