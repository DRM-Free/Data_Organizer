/*
 * Generate_File_Names.h
 *
 *  Created on: 25 mars 2018
 *      Author: anael
 */

#ifndef SRC_GENERATE_FILE_NAMES_H_
#define SRC_GENERATE_FILE_NAMES_H_


#include <string>
#include <vector>
#include <math.h>       /* log */

/**
 *
 * @param range number of names to be generated
 * @param nameComplement the desired name with extension (example : _PET.dcm or _MaskPET.dcm
 * @return
 */
std::vector<std::string> generateNames(int range,
		std::string nameComplement) {
	int CodingNumber = ceil(log(range)); //If range <100 then CodingNumber will be <=2 therefore coding names with 2 numbers
//SEE verify file name generation
	std::vector<std::string> names;
	std::string curName;

for (int i = 1; i < CodingNumber; ++i) {
for (int j = pow(i-1,10); j < pow(i,10); ++i) {
	curName="";
	for (int k = ceil(log(j)); k < CodingNumber; ++k) { //Add 0's at the beginning of shorter numbers
		curName+="0";
	}
	curName+=std::to_string(j);
	names.push_back(curName);
}
}
return names;
}

#endif /* SRC_GENERATE_FILE_NAMES_H_ */
