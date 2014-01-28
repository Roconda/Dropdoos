/*
 * Settings.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tim
 */

#include "Settings.h"
#include <string>

#include "stdio.h"
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
	#define pathSepp '\\'
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
	#define pathSepp '/'
#endif

Settings::Settings(){
	// Set working dir
	if (!GetCurrentDir(rootDir, sizeof(rootDir))){
		//TODO: Throw exception
	}

	for(int i=0; i<sizeof(rootDir); i++) {
		if(rootDir[i] == '\0'){
			rootDir[i] = pathSepp;
			rootDir[i+1] = '\0';
			break;
		}
	}
};

const char* Settings::getCwd() {
	return rootDir;
}
