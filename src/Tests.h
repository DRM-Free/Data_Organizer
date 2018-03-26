/*
 * Tests.h
 *
 *  Created on: Mar 26, 2018
 *      Author: anael
 */

#ifndef SRC_TESTS_H_
#define SRC_TESTS_H_


#include "Generate_File_Names.h"

void testFileNames(){
		std::cout<<"Initiating namegen test with 102 names and name extension _nameTest"<<std::endl;
	std::vector<std::string> names=generateNames(102,"_nameTest");
	for (int pos = 0; pos < names.size(); ++pos) {
		std::cout<<names[pos]<<std::endl;
	}
}




#endif /* SRC_TESTS_H_ */
