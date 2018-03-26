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
	fs::path pOut=parsed_params.second;
	pairRelatedFolders(findFolders(pIn));
	int foldersToWrite=unprocessedFolders.size();
	std::vector<std::string> foldersNames=generateNames(foldersToWrite,std::string("_Set")); //Generate names for _Set folders too !
		fs::path CTPath;
		fs::path PETPath;
		fs::path CTMask;
		fs::path PETMask;
		fs::path CTScans;
		fs::path PETScans;
		fs::path writePath;
		std::string curName;
	for (auto f = unprocessedFolders.begin(); f != unprocessedFolders.end();++f) {
		CTPath = f->first;
		PETPath = f->second;
		CTMask = findMask(CTPath);
		PETMask = findMask(PETPath);
		CTScans = findScans(CTPath);
		PETScans = findScans(PETPath);
		writePath=fs::path(parsed_params.second);
		//Time to write all those files somewhere !
		writePath/=foldersNames[f-unprocessedFolders.begin()]; //Choose the proper name number
		writeOrganizedData_symLink(writePath, CTScans, PETScans, CTMask,
				PETMask);
}
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
	std::cerr << "A mask Was not found" << std::endl;
	return "";
}


fs::path findScans(fs::path parentFolder) {
	for (auto& p : fs::recursive_directory_iterator(parentFolder)) {
		fs::path curPath = fs::path(p);
		if (curPath.extension() == ".dcm") { //We have found a dicom file. Is it a mask or a scan file ? Not known yet
			//SEE Modify here if scans are not found properly
			if (curPath.parent_path().stem() == "DICOM") {
				return curPath;
			}
		}
	}
	std::cerr << "Some scans were not found" << std::endl;
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
void writeOrganizedData_symLink(const fs::path writePath, fs::path CTScans,
		fs::path PETScans, fs::path CTMask, fs::path PETMask) {
	std::cout << "Writing to folder " << writePath << std::endl;
	fs::create_directory(writePath); //creates a directory with desired #number_Set name
	int CTNumber=0;
	int PETNumber=0;
	for (auto& p : fs::directory_iterator(CTScans)) {
CTNumber++;
	}
	for (auto& p : fs::directory_iterator(PETScans)) {
PETNumber++;
	}
if(CTNumber!=PETNumber){ //SEE just a quick check that there is a proper number of files to pair, otherwise exits
	std::cerr<<"For this set, number of Pet scans and CT scans found are different : "<< std::endl<<CTScans<<std::endl<<PETScans<<std::endl<<"Write process aborted"<<std::endl;
    std::cin.get();
            exit(0);
}
	std::vector<std::string> CTNames=generateNames(CTNumber,std::string("_CT")); //Generate CT names
	std::vector<std::string> PETNames=generateNames(PETNumber,std::string("_Pet")); //Generate PET names
	fs::path curPath;
	std::vector<std::pair<fs::path,fs::path>> pairedFiles=pairRelatedFiles(CTScans,PETScans);
for (auto p = pairedFiles.begin(); p != pairedFiles.end(); ++p) {
		curPath=writePath;
		curPath/=CTNames[p-pairedFiles.begin()]; //Choose the proper name number
	    fs::create_symlink(p->first, curPath); //Creates symbolic link with target the path to CT image file
		curPath=writePath;
		curPath/=PETNames[p-pairedFiles.begin()]; //Choose the proper name number
	    fs::create_symlink(p->second, curPath);  //Creates symbolic link with target the path to PET image file
}}

std::vector<std::pair<fs::path,fs::path>> pairRelatedFiles(fs::path CTPath, const fs::path PETPath){
std::vector<std::pair<fs::path,fs::path>> pairedFiles; //First element of pair : CT image path. Second element : path to PET image file
	fs::path curCTPath; //Path to CT image file to be added to pairedFiles
	fs::path curPETPath; //Path to PET image file to be added to pairedFiles
	std::pair<fs::path,fs::path> curPair; //Curent pair to be added (made from curCTPath and curPETPath
for (auto ct : fs::directory_iterator(CTPath)) {
	curPETPath=PETPath;
	curCTPath=ct;
	curPETPath=curCTPath.stem();
	/**
	 *
	 *SEE Program takes for granted that files are paired properly (both CT and PET files exist with same name). If not the case, problems will occur
	 *SEE A full research for paired files is considered too costly but can still be implemented here
	*/
	curPETPath/=curCTPath.filename(); //Appends proper file name to PETPath
curPair=std::make_pair(curCTPath,curPETPath);
pairedFiles.push_back(curPair);
}
return pairedFiles;
}
