/*
 * Files_Operations.h
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */

#ifndef FILES_OPERATIONS_H_
#define FILES_OPERATIONS_H_

#include <utility>      // std::pair, std::make_pair
#include <experimental/filesystem> //SEE requires c++17

namespace fs = std::experimental::filesystem;

void genSetFolders(std::pair<char*,char*> parsed_params);


#endif


