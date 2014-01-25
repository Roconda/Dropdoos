/*
 * Settings.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tim
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define MAX_APPENDED_SIZE 2048

#include "stdio.h"

class Settings {
	public:
		static Settings& getInstance() {
			static Settings instance;

			return instance;
		}

		const char* getCwd();
	private:
		Settings();
		Settings(Settings const&);
		void operator=(Settings const&);

		// properties
		char rootDir[FILENAME_MAX];
		char* cwd[MAX_APPENDED_SIZE];

};

#endif /* SETTINGS_H_ */
