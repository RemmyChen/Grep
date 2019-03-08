/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  gerp.cpp
 *  Complete Gerp Class Implementation
 *  Modified By (UTLN): rchen07
 *           On       : 11/27/2017
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include<vector>
#include <dirent.h>

#include "Gerp.h"

using namespace std;


/*  default constructor, takes no parameters, 
    calls empty hash table. */
Gerp::Gerp()
{
    filePath = "";
    fileNo = 0;
}


/*  destructor, frees heap memory. */
Gerp::~Gerp()
{
}


/*  PURPOSE: index words in files in 
    given directory 
    RETURN: void
    PARAMETERS: string */
void Gerp::index(string directoryToIndex)
{
    FSTree theTree(directoryToIndex);
    DirNode *root = theTree.getRoot();
    DirNode *current = root;
    fileNo = 0;
    climb(current, root);
}


/*  PURPOSE: takes query search order 
    RETURN: void
    PARAMETERS: istream input */
void Gerp::takeorder(std::istream &input)
{
    string word;
    while (input >> word) {
        if (word == "@q" || word == "@quit") {
            return;
        }
        else if (word == "@i" || word == "@insensitive") { 
            input >> word;
            theHashTable.lookup("insensitive", word); 
        }
        else {
            theHashTable.lookup("sensitive", word);
        }
        cout << "Query? ";
    }
}


/**********************************************************************/
/*                      Private member functions                      */
/**********************************************************************/


/*  PURPOSE: climbs FSTree to each file 
    RETURN: void
    PARAMETERS: pter to current node and pter to root */
void Gerp::climb(DirNode *aNode, DirNode *theRoot)
{
    if (aNode->isEmpty()) {
        return;
    }
    if (aNode->hasFiles()) {
        for (int i = 0; i < aNode->numFiles(); i++) {
            if (aNode->getName() == theRoot->getName()) {
                savePath(aNode, i, vector<string>());
                fileNo++; 
                processFile();						        
            }
            else {
                DirNode *temp = aNode;
                vector<string> tempPath;
                tempPath.push_back(temp->getFile(i));
                while (temp->getName() != theRoot->getName()) {
                    tempPath.push_back(temp->getName());
                    temp = temp->getParent();
                }
                savePath(temp, i, tempPath);
                fileNo++; 
                processFile();						
            }
        }
    }
    if (aNode->hasSubDir()) {
        for (int i = 0; i < aNode->numSubDirs(); i++)
            climb(aNode->getSubDir(i), theRoot);
    }
}


/*  PURPOSE: saves filepath
    RETURN: void
    PARAMETERS: pter to node, int file number, 
    string of path that is not at root, boolean 
    to determine if file is at root or not */
void Gerp::savePath(DirNode *someNode, int j, vector<string> somePath)
{
    filePath = someNode->getName();
    
    if (someNode->getName()[someNode->getName().length() - 1] != '/') {
        filePath += "/";
    }

    if (somePath.size() > 0) {
        for (int i = somePath.size() - 1; i > 0; i--) {
            filePath += somePath[i] + "/";
        }
        filePath += somePath[0];
    }
    else {
        filePath += someNode->getFile(j);
    }
}


/*  PURPOSE: opens file, inserts each word and its
    information into the hash table.
    RETURN: void
    PARAMETERS: none */
void Gerp::processFile()
{
	ifstream input;
    char wordPhrase[256];
    int lineNo = 0;
    string key;

    input.open(filePath);

    if (not input.is_open()) {
        report_unopen();
    }
    while (input.getline(wordPhrase, 256)) {
        istringstream iss(wordPhrase);
        lineNo++;
        while(iss >> key) {
            theHashTable.insert(key, filePath, fileNo, wordPhrase, lineNo);
        }
    }
    input.close();
}


/*  PURPOSE: prints error when folder can't open
    RETURN: void
    PARAMETERS: none */
void Gerp::report_unopen()
{
    cerr << "Unable to open file" << endl;
    exit(1);
}