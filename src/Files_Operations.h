/*
 * Files_Operations.h
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */

#ifndef FILES_OPERATIONS_H_
#define FILES_OPERATIONS_H_

#include "Params_Parser.h"

#include <utility>      // std::pair, std::make_pair
#include <vector>
#include <experimental/filesystem>
#include <string>
namespace fs = std::experimental::filesystem;

/**
 * This structure contains the vector of all still unsorted data folders
 * (paired with relative folder - one CT with one PET) and will be emptied during the process)
 * unprocessedFolders. first will be a CT folder path and unprocessedFolders.second will be a PET folder path
 */
static std::vector<std::pair<fs::path, fs::path>> unprocessedFolders;

void genSetFolders(parsed_Params par, std::string ref);
void pairRelatedFolders(std::vector<fs::path> allDataPaths);
fs::path findMask(fs::path parentFolder);
fs::path findScans(fs::path parentFolder);
void writeData(const fs::path writePath, fs::path scans,fs::path mask, std::string nameExtension, std::string ref);
std::vector<std::pair<fs::path,fs::path>> pairRelatedFiles(fs::path CTPath, fs::path PETPath);
std::string findBetween(std::string to_search, std::string before,std::string after);
#endif
