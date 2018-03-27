/*
 * Files_Operations.h
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */

#ifndef FILES_OPERATIONS_H_
#define FILES_OPERATIONS_H_

#include <utility>      // std::pair, std::make_pair
#include <vector>
#include <experimental/filesystem> //SEE requires c++17 AND most recent g++ compiler setup

namespace fs = std::experimental::filesystem;

/**
 * This structure contains the vector of all still unsorted data folders
 * (paired with relative folder - one CT with one PET) and will be emptied during the process)
 * unprocessedFolders. first will be a CT folder path and unprocessedFolders.second will be a PET folder path
 */
static std::vector<std::pair<fs::path, fs::path>> unprocessedFolders;

void genSetFolders(std::pair<char*,char*> parsed_params);
void pairRelatedFolders(std::vector<fs::path> allDataPaths);
fs::path findMask(fs::path parentFolder);
fs::path findScans(fs::path parentFolder);
void writeOrganizedData_symLink(fs::path writePath, fs::path CTScans,
		fs::path PETScans, fs::path CTMask, fs::path PETMask);
std::vector<std::pair<fs::path,fs::path>> pairRelatedFiles(fs::path CTPath, fs::path PETPath);

#endif
