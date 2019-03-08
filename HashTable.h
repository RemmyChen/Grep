/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  HashTable.h
 *  Complete HashTable Class Interface
 *  Modified By (UTLN): rchen07
 *           On       : 11/30/2017
 *
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>

#include "FileStorage.h"

struct WordInfo {
		std::string caseSensitiveWord;
		int fileNo;
		int lineNo;

        WordInfo() 
        {
        		caseSensitiveWord = "";
                fileNo = -1;
                lineNo = -1;
        }
        WordInfo(std::string casesensitiveword, int fileno, int lineno)
        {
                caseSensitiveWord = casesensitiveword;
        		fileNo = fileno;
                lineNo = lineno;
        }
};


typedef std::string   KeyType;
typedef WordInfo      ValueType;

class HashTable
{

public:
        HashTable(); /* constructor */
        ~HashTable(); /* destructor */

        /* inserts words and their information into hash table */
		void insert(KeyType key, std::string filepath, int fileno, std::string wordphrase, int lineno);
        
        /* looks up and prints words and their information */
        void lookup(std::string UorLcase, KeyType word);

private:

    	struct TableEntry {
                bool isEmpty;
                KeyType key;
                std::vector<ValueType> *samewords;
        };

	    static const int INITIAL_TABLE_SIZE = 3;
        int currentTableSize;
        int numItemsInTable;

	    TableEntry *theTable;
        FileStorage theFileStorage;

        /* generates hash value */
        int generateHashValue(KeyType key);

        /* prints query results or message if word can't be found */
        void print(std::string sensitivity, KeyType word, TableEntry &entry);

        /*  */
        int printHelper(std::string sensitivity, KeyType word, TableEntry &entry);

        /* takes out leading and trailing non-alphanumeric characters from input */
		std::string stripNonAlphaNum(std::string input);

        /* makes input all lower case */
        std::string allLower(std::string input);

        /* deletes vectors pointed to by hash table entries */
		void clear();

        /* expands hash table */
        void expand();
        
};

#endif