/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  gerp.h
 *  Complete Gerp Class Interface
 *  Modified By (UTLN): rchen07
 *           On       : 11/27/2017
 *
 */

#ifndef GERP_H
#define GERP_H

#include <iostream>

#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"


class Gerp
{

public:
        Gerp();   /* default constructor */

        ~Gerp();   /* destructor */

		/* indexes words in files in given directory */
		void index(std::string directoryToIndex);

		/* takes query search orders from istream */
		void takeorder(std::istream &input);

private:

		HashTable theHashTable;
		std::string filePath;
		int fileNo;

		/* climbs file tree to each file in each subdirectory */
		void climb(DirNode *aNode, DirNode *theRoot);

		/* retrieves full filepath */
		void savePath(DirNode *someNode, int j, std::vector<std::string> somePath);
		
		/* opens file, inserts each word and its information into hash table */
		void processFile();

		/* reports error if file can't be opened and exits */
		void report_unopen();


};

#endif