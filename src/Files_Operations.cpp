/*
 * Files_Operations.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */



#include "Files_Operations.h"
#include "Generate_File_Names.h"
#include <utility>      // std::pair, std::make_pair
#include <string>
#include <iostream>

/**
 * First processing step : finds all data folders
 *
 */
std::vector<fs::path> findFolders(fs::path dataFolder) {
	std::vector<fs::path> allDataPaths;
	for (auto& p : fs::directory_iterator(dataFolder)) {
		allDataPaths.push_back(fs::path(p));
	}
	std::cout << allDataPaths.size() << " Data folders were found" << std::endl;
	return allDataPaths;
}


/**
 * Second processing step : pair those folders with their relative of other imaging modality
 *
 */
void pairRelatedFolders(std::vector<fs::path> allDataPaths) {
	fs::path CTPath;
	std::string CT = "";
	fs::path PETPath;
	std::string PET = "";

	while (allDataPaths.begin() != allDataPaths.end()) {
		for (auto path = allDataPaths.begin(); path != allDataPaths.end();
				++path) {

			if (path == allDataPaths.begin()) {

				std::string firstPath = *path;
				if (firstPath.find("_PET") != std::string::npos) {
					PETPath = firstPath;
					PET = PETPath;
					int PETNameEnds = CT.find("_");
					PET.erase(PET.begin() + PETNameEnds, PET.end()); //erases the _PET part from path name
				}
				if (firstPath.find("_CT") != std::string::npos) {
					CTPath = firstPath;
					CT = CTPath;
					int CTNameEnds = CT.find("_");
					CT.erase(CT.begin() + CTNameEnds, CT.end()); //erases the _CT part from path name
				}

			}

			else if (CTPath == "") {
				CTPath = *path;
		CT = CTPath;
		int CTNameEnds = CT.find("_");
		CT.erase(CT.begin() + CTNameEnds, CT.end()); //erases the _CT part from path name
				if (CT == PET) { //A match was found, let's put that in unprocessedFolders
					unprocessedFolders.push_back(
							std::make_pair(CTPath, PETPath));
					//SEE do not forget to remove found elements from allDataPaths so it gets empty !
					allDataPaths.erase(allDataPaths.begin());
					allDataPaths.erase(path);
				}
				else { //There is no match, CTPath will be changed next iteration
					CTPath = "";
				}
			}
			else if (PETPath == "")
			{
				PETPath = *path;
				PET = PETPath;
				int PETNameEnds = CT.find("_");
				PET.erase(PET.begin() + PETNameEnds, PET.end()); //erases the _PET part from path name
				if (CT == PET) { //A match was found, let's put that in unprocessedFolders
					unprocessedFolders.push_back(
							std::make_pair(CTPath, PETPath));
					//SEE do not forget to remove found elements from allDataPaths so it gets empty !
					allDataPaths.erase(allDataPaths.begin());
					allDataPaths.erase(path);
				} else { //There is no match, CTPath will be changed next iteration
					PETPath = "";
				}
			}
		}
	}
}

/**
 * third processing step : creates relevant folders with base name Set_ and desired content
 * @params : first char* is original data location, second char* is desired organized data location
 */
void genSetFolders(std::pair<char*,char*> parsed_params){
	fs::path pIn=parsed_params.first;
	fs::path pOutIn=parsed_params.second;
	pairRelatedFolders(findFolders(pIn));
	for (auto f = unprocessedFolders.begin(); f != unprocessedFolders.end();
			++f) {
		fs::path CTPath = f->first;
		fs::path PETPath = f->second;
		fs::path CTMask = findMask(CTPath);
		fs::path PETMask = findMask(PETPath);
		fs::path CTScans = findScans(CTPath);
		fs::path PETScans = findScans(PETPath);
		fs::path writePath(parsed_params.second);
		//Time to write all those files somewhere !
		writeOrganizedData_symLink(writePath, CTScans, PETScans, CTMask,
				PETMask);
}
}

void pairRelatedFiles(std::vector<fs::path> unprocessedFolders) {
}

fs::path findMask(fs::path parentFolder) {
	for (auto& p : fs::recursive_directory_iterator(parentFolder)) {
		fs::path curPath = fs::path(p);
		if (curPath.extension() == ".dcm") { //We have found a dicom file. Is it a mask or a scan file ? Not known yet
			//SEE Modify here if masks are not found properly
			if (curPath.parent_path().stem() == "secondary") {
				return curPath;
			}
		}
	}
	std::cerr << "Mask Was not found" << std::endl;
	return "";
}


fs::path findScans(fs::path parentFolder) {
	for (auto& p : fs::recursive_directory_iterator(parentFolder)) {
		fs::path curPath = fs::path(p);
		if (curPath.extension() == ".dcm") { //We have found a dicom file. Is it a mask or a scan file ? Not known yet
			//SEE Modify here if scans are not found properly
			if (curPath.parent_path().stem() != "secondary") {
				return curPath;
			}
		}
	}
	std::cerr << "Scans were not found" << std::endl;
	return "";
}

/**
 * Writes organized symbolic links to data files to targetPath folder
 * @param targetPath where to write data
 * @param CTScans Path to ctscan dicoms
 * @param PETScans Path to petscan dicoms
 * @param CTMask Path to ctscan mask
 * @param PETMask Path to petscan dicom
 */
void writeOrganizedData_symLink(fs::path targetPath, fs::path CTScans,
		fs::path PETScans, fs::path CTMask, fs::path PETMask) {
	std::cout << "Writing to folder " << targetPath << std::endl;
//TODO complete file writing
}

