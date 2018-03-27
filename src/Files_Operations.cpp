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
 * First processing step : find and pair data folders with their relative of other imaging modality
 *
 */
void pairRelatedFolders(fs::path dataFolder) {
	int nbFolders=0;
	for (auto& p : fs::directory_iterator(dataFolder)) {
		nbFolders++;
	}
	std::cout << nbFolders << " Data folders were found" << std::endl;
	/**
	 *
	 *SEE Program takes for granted that data folders are paired properly (both _CT and _PET folders exist with same name). If not the case, problems will occur
	 *SEE A full research for paired folders is considered too costly but can still be implemented here
	*/

		std::pair<fs::path,fs::path> curPair;
		fs::path CTPath;
		fs::path PETPath;
		std::string curPath;
		uint PETNameEnds;
	for (auto &p : fs::directory_iterator(dataFolder)) {
		curPath=fs::path(p);
		PETNameEnds=curPath.find("_PET");
		if (curPath.find("_PET")!=std::string::npos){ //This is a PET data folder
			PETPath=curPath;
			curPath.erase(curPath.begin()+PETNameEnds+1,curPath.end()); //Removes the _PET part in folder name
curPath+="CT";
CTPath=curPath;
curPair=std::make_pair(CTPath,PETPath);
unprocessedFolders.push_back(curPair);
		}
	}
}

/**
 * second processing step : creates relevant folders with base name Set_ and desired content
 * @params : first char* is original data location, second char* is desired organized data location
 */
void genSetFolders(std::pair<char*,char*> parsed_params){
	fs::path pIn=parsed_params.first;
	fs::path pOut=parsed_params.second;
	pairRelatedFolders(pIn);
	int foldersToWrite=unprocessedFolders.size();
	std::vector<std::string> foldersNames=generateNames(foldersToWrite,std::string("Patient_")); //Generate names for _Set folders too !
		fs::path CTPath;
		fs::path PETPath="";
		fs::path CTMask="";
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
		if((CTPath!="")and( PETPath!="")and (CTMask!="")and (PETMask!="")){
		writePath=fs::path(parsed_params.second);
		//Time to write all those files somewhere !
		writePath/=foldersNames[f-unprocessedFolders.begin()]; //Choose the proper name number
		writeOrganizedData_symLink(writePath, CTScans, CTMask, "CT");
		writeOrganizedData_symLink(writePath, PETScans, PETMask, "PET");
		}
//		void writeOrganizedData_symLink(const fs::path writePath, fs::path scans,fs::path mask, std::string nameExtension) {

}
}


fs::path findMask(fs::path parentFolder) {
	for (auto p : fs::recursive_directory_iterator(parentFolder)) {
		fs::path curPath = fs::path(p);
		if (curPath.extension() == ".dcm") { //We have found a dicom file. Is it a mask or a scan file ? Not known yet
			//SEE Modify here if masks are not found properly
//			std::cout<<"A mask file was found at location :" <<std::endl;
//			std::cout<<curPath<<std::endl;
			if (curPath.parent_path().parent_path().stem() == "secondary") {
				return curPath;
			}
		}
	}
	std::cerr << "A mask Was not found for this data folder :" << std::endl;
	std::cerr<<parentFolder<<std::endl;
	std::cerr << "Excluding this patient folder from output" << std::endl;
    return fs::path("");}


fs::path findScans(fs::path parentFolder) {
	for (auto& p : fs::recursive_directory_iterator(parentFolder)) {
		fs::path curPath = fs::path(p);
		if (curPath.extension() == ".dcm") { //We have found a dicom file. Is it a mask or a scan file ? Not known yet
			//SEE Modify here if scans are not found properly
			if (curPath.parent_path().parent_path().stem() == "DICOM") {
				return curPath.parent_path();
			}
		}
	}
	std::cerr << "Scans were not found for this data folder :" << std::endl;
	std::cerr<<parentFolder<<std::endl;
	std::cerr << "Excluding this patient folder from output" << std::endl;
    return fs::path("");}

//TODO modify code to put images from different modalities in different folders

/**
 * Writes organized symbolic links to data files to targetPath folder
 *
 */
//TODO only write one type of imaging modality per folder
void writeOrganizedData_symLink(const fs::path writePath, fs::path scans,fs::path mask, std::string nameExtension) {
	//SEE nameExtension must not have an '_', just let writeOrganizedData_symLink handle separators
	int ScansNumber=0;
	for (auto& p : fs::directory_iterator(scans)) {
		ScansNumber++;
	}
fs::path write=writePath;
write/=nameExtension;
	std::cout << "Writing to folder " << write << std::endl;
	if(!fs::exists(writePath)){
		fs::create_directory(writePath);
	}
		fs::create_directory(write);

	fs::path curPath;
	std::vector<std::string> Names=generateNames(ScansNumber,std::string(nameExtension)); //Generate CT names
		std::string maskName=nameExtension;
		maskName+="_RTSTRUCT";
		curPath=write;
curPath/=maskName;
	    fs::create_symlink(mask, curPath);  //Creates symbolic link with target the path to mask image file
		curPath=writePath;
		int namePos=0;
	    for (auto sc : fs::directory_iterator(scans)) {
	//SEE Here symbolic links are written
	//TODO Maybe replace absolute path links with relative path links so that result folders can be moved later on
		curPath=write;
		curPath/=Names[namePos]; //Choose the proper name number
	    namePos++;
	    fs::create_symlink(sc, curPath); //Creates symbolic link with target the path to CT image file
}}

std::vector<std::pair<fs::path,fs::path>> pairRelatedFiles(const fs::path CTPath, const fs::path PETPath){
std::vector<std::pair<fs::path,fs::path>> pairedFiles; //First element of pair : CT image path. Second element : path to PET image file
	fs::path curCTPath; //Path to CT image file to be added to pairedFiles
	fs::path curPETPath; //Path to PET image file to be added to pairedFiles
	std::pair<fs::path,fs::path> curPair; //Curent pair to be added (made from curCTPath and curPETPath
for (auto ct : fs::directory_iterator(CTPath)) {
	/**
	 *
	 *SEE Program takes for granted that files are paired properly (both CT and PET files exist with same name). If not the case, problems will occur
	 *SEE A full research for paired files is considered too costly but can still be implemented here
	*/
	curCTPath=ct;
	curPETPath=PETPath;
	curPETPath/=curCTPath.filename(); //Appends proper file name to PETPath
curPair=std::make_pair(curCTPath,curPETPath);
pairedFiles.push_back(curPair);
}
return pairedFiles;
}
