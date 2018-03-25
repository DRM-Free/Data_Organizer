/*
 * main.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */


#include "Params_Parser.h"
#include "Files_Operations.h"

#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <limits>

// When passing char arrays as parameters they must be pointers
int main(int argc, char* argv[]) {
std::pair<char*,char*> parsed_params = parse_params(argc,argv);
std::cout<<"Data will be loaded from " << parsed_params.first << " And output will be in " << parsed_params.second << std::endl;
std::cout<<"Confirm ?" << std::endl;
std::string user_choice;
std::getline(std::cin,user_choice);
if(user_choice==(std::string)"\0" or user_choice==(std::string)"y"){ //User acceptance
	std::cout << "Proceeding to file operations" << std::endl;
	genSetFolders(parsed_params);
}

else{
std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //empties cin buffer
	std::cout << "Aborting" <<std::endl;
    std::cin.get();
            exit(0);
}
return 0;
}
