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
		std::string nameComplement);

#endif /* SRC_GENERATE_FILE_NAMES_H_ */
