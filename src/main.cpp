/*
 * main.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */


#include "Params_Parser.h"
#include "Files_Operations.h"
#include "Tests.h"
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <limits>
#include <experimental/filesystem> //SEE requires c++17 AND most recent g++ compiler setup

namespace fs = std::experimental::filesystem;
// When passing char arrays as parameters they must be pointers
int main(int argc, char* argv[]) {
//#define test
#ifndef test
parsed_Params par = parse_params(argc,argv);
std::cout<<"Data will be loaded from " << par.inPath << " And output will be in " << par.outPath << std::endl;
std::cout<<"Output folder current content will be lost" << std::endl;
std::cout<<"Confirm ?" << std::endl;
std::string user_choice;
std::getline(std::cin,user_choice);
if(user_choice==(std::string)"\0" or user_choice==(std::string)"y"){ //User acceptance
	std::cout << "Proceeding to file operations" << std::endl;
	fs::path out=par.outPath;
	if(fs::exists(out)){
	fs::remove_all(fs::path(out));
	fs::create_directory(fs::path(out));}
	else{
	fs::create_directory(fs::path(out));}
	genSetFolders(par,par.ref);
	std::cout<<"Done"<<std::endl;
}

else{
std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //empties cin buffer
	std::cout << "Aborting" <<std::endl;
    std::cin.get();
            exit(0);
}
return 0;
#else
//For testing
testFileNames();
return 0;


#endif
}
