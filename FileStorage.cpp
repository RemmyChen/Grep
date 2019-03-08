/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  FileStorage.cpp
 *  Complete FileStorage Class Implementation
 *  Modified By (UTLN): rchen07
 *           On       : 11/30/2017
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "FileStorage.h"

using namespace std;


/*  default constructor, nothing to do. */
FileStorage::FileStorage()
{
}


/* destructor, nothing to do. */
FileStorage::~FileStorage()
{
}


/*  PURPOSE: saves incoming document lines and filepaths (without repetition).
	Checks if filepath has already been stored.
    RETURN: void
    PARAMETERS: information on document lines and filepaths to store. */
void FileStorage::save(string filepath, int fileno, string wordphrase, int lineno)
{
	bool filePathExists = false;
	size_t prevNo = 0;

	if (theStorage.size() > 0) {
		prevNo = theStorage.size() - 1;
		if (theStorage[prevNo].filePath == filepath) {
			filePathExists = true;
			checkLine(prevNo, wordphrase, lineno);
		}
	}

	if (!filePathExists) {
		theStorage.push_back({filepath, fileno, wordphrase, lineno});
	}
}


/*  PURPOSE: prints word's filepath, line number, and line. 
    RETURN: void
    PARAMETERS: word's file and line numbers. */
void FileStorage::print(int fileno, int lineno)
{
	for (size_t i = 0; i < theStorage.size(); i++) {
		if (theStorage[i].fileNo == fileno) {
			cout << theStorage[i].filePath << ":";
			fileno = i;
		}
	}
    cout << lineno << ": ";
    for (size_t j = 0; j < theStorage[fileno].wordPhrases.size(); j++) {
    	if (theStorage[fileno].wordPhrases[j].lineNo == lineno) {
    		cout << theStorage[fileno].wordPhrases[j].wordPhrase << endl; 
    	}
    }
}


/**********************************************************************/
/*                      Private member functions                      */
/**********************************************************************/


/*  PURPOSE: saves incoming document lines without repetition.
	Checks if line had already been stored.
    RETURN: void
    PARAMETERS: information on document lines to store. */
void FileStorage::checkLine(int fileno, string wordphrase, int lineno)
{
	bool wordPhraseExists = false;
	size_t prevNo = 0;

	if (theStorage[fileno].wordPhrases.size() > 0) {
		prevNo = theStorage[fileno].wordPhrases.size() - 1;
		if (theStorage[fileno].wordPhrases[prevNo].wordPhrase == wordphrase) {
			wordPhraseExists = true;
		}
	}

	if (!wordPhraseExists) {
		theStorage[fileno].wordPhrases.push_back({wordphrase, lineno});
	}
}
