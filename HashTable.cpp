/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  HashTable.cpp
 *  Complete HashTable Class Implementation
 *  Modified By (UTLN): rchen07
 *           On       : 11/30/2017
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>

#include "HashTable.h"

using namespace std;


/*  default constructor, takes no parameters, 
    initializes empty hash table. */
HashTable::HashTable()
{
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    theTable      = new TableEntry[currentTableSize];

    for (int i = 0; i < currentTableSize; i++) {
        theTable[i].isEmpty = true;
        theTable[i].key     = "";
        theTable[i].samewords = NULL;
    }
}


/* destructor, frees heap memory. */
HashTable::~HashTable()
{
    clear();
}


/*  PURPOSE: uses C++ std library implementation of hash function. 
    RETURN: hash value
    PARAMETERS: key to hash */
static size_t hashValue(KeyType key)
{
    return std::hash<string>{}(key);
}


/*  PURPOSE: inserts words and their information into hash table. 
    RETURN: void
    PARAMETERS: word, filepath, phrase that word is in,
    and line number where word is found */
void HashTable::insert(KeyType key, string filepath, int fileno, string wordphrase, int lineno)
{
    if (stripNonAlphaNum(key).length() == 0) {
        return;
    }
    theFileStorage.save(filepath, fileno, wordphrase, lineno);
	if (numItemsInTable >= (6 * currentTableSize) / 10) { 
        expand();
    }
    int hashvalue = generateHashValue(key);
    theTable[hashvalue].key = allLower(stripNonAlphaNum(key));
    if (theTable[hashvalue].samewords == NULL) {
        theTable[hashvalue].samewords = new std::vector<ValueType>();
    }
    bool wordSameFileSameLineExists = false;
    size_t prevNo = 0;
    if (theTable[hashvalue].samewords->size() > 0) {
        prevNo = theTable[hashvalue].samewords->size() - 1;
        if ((*theTable[hashvalue].samewords)[prevNo].fileNo == fileno 
            && (*theTable[hashvalue].samewords)[prevNo].lineNo == lineno) {
            wordSameFileSameLineExists = true;
        }
    }
    if (!wordSameFileSameLineExists) {
        theTable[hashvalue].samewords->push_back({stripNonAlphaNum(key), fileno, lineno});   
    }
    theTable[hashvalue].isEmpty = false;
    numItemsInTable++;
}


/*  PURPOSE: looks up and prints words and their information. 
    RETURN: void
    PARAMETERS: string (sensitive or insensitive), query word */
void HashTable::lookup(string sensitivity, KeyType word)
{
    int hashvalue = generateHashValue(word);
    print(sensitivity, stripNonAlphaNum(word), theTable[hashvalue]);
}


/**********************************************************************/
/*                      Private member functions                      */
/**********************************************************************/


/*  PURPOSE: generates hash value. 
    RETURN: int hash value
    PARAMETERS: key to generate hash value from */
int HashTable::generateHashValue(KeyType key)
{
    string streamlinedKey = allLower(stripNonAlphaNum(key));
    int hashvalue = hashValue(streamlinedKey) % currentTableSize;

    while (!theTable[hashvalue].isEmpty 
        && theTable[hashvalue].key != streamlinedKey) {
        hashvalue = (hashvalue + 1) % currentTableSize;        
    }

    return hashvalue;
}


/*  PURPOSE: prints query results or message if word can't be found. 
    RETURN: void
    PARAMETERS: string (sensitive or insensitive), query 
    word, entry that instances of the word are stored in */
void HashTable::print(string sensitivity, KeyType word, TableEntry &entry)
{
    if (entry.isEmpty) {
        if (sensitivity == "insensitive") {
            cout << word << " Not Found." << endl;
            return;
        }
        else {
            cout << word << " Not Found. Try with @insensitive or @i." << endl;
            return;
        }
    }
    int counter = printHelper(sensitivity, word, entry);
    if (sensitivity == "insensitive") { 
        if (counter == 0) {
            cout << word << " Not Found." << endl;
        }
    }
    else { 
        if (counter == 0) {
            cout << word << " Not Found. Try with @insensitive or @i." << endl;
        }
    }   
}


/*  PURPOSE: helps print query results depending on sensitivity. 
    RETURN: int (word occurence count)
    PARAMETERS: string (sensitive or insensitive), query 
    word, entry that instances of the word are stored in */
int HashTable::printHelper(string sensitivity, KeyType word, TableEntry &entry)
{
    int counter = 0;

    for (size_t i = 0; i < entry.samewords->size(); i++) {
        if (sensitivity == "sensitive") {    
            if (word == (*entry.samewords)[i].caseSensitiveWord) {
                int fileno = (*entry.samewords)[i].fileNo;
                int lineno = (*entry.samewords)[i].lineNo;
                theFileStorage.print(fileno, lineno);
            }
        }
        else {
            int fileno = (*entry.samewords)[i].fileNo;
            int lineno = (*entry.samewords)[i].lineNo;
            theFileStorage.print(fileno, lineno);
        }
        counter++;
    }

    return counter;
}


/*  PURPOSE: takes out leading and trailing 
    non-alphanumeric characters from input. 
    RETURN: string without leading and trailing
    non-alphanumeric characters
    PARAMETERS: input string */
string HashTable::stripNonAlphaNum(string input)
{
    int i = 0;

    while (input.length() > 0 && !isalnum(input[i]) && input[i] != '\0') {
        input = input.erase(i, 1);
    }

    while (input.length() > 0 && !isalnum(input[input.length() - 1])) {
        input = input.erase(input.length() - 1, 1);
    }

    return input;
}


/*  PURPOSE: makes input all lower case. 
    RETURN: lower case string
    PARAMETERS: input string */
string HashTable::allLower(string input)
{
    for (size_t i = 0; i < input.length(); i++) {
        if (isalpha(input[i])) {
            input[i] = tolower(input[i]) - 'a';
        }
    }
    return input;
}


/*  PURPOSE: frees all vectors 
    pointed to by table entries. 
    RETURN: void
    PARAMETERS: none */
void HashTable::clear()
{
    if (theTable != NULL) {
        for (int i = 0; i < currentTableSize; i++) {
            if (theTable[i].samewords != NULL) {
                delete theTable[i].samewords;
            }
        }
        delete [] theTable;
    }
}


/*  PURPOSE: expands hash table. 
    RETURN: void
    PARAMETERS: none */
void HashTable::expand()
{
    int newTableSize = currentTableSize * 2 + 1;
    TableEntry *tempTable = new TableEntry[newTableSize];

    for (int i = 0; i < newTableSize; i++) {
        tempTable[i].isEmpty = true;
        tempTable[i].key     = "";
        tempTable[i].samewords   = NULL;
    }

    for (int j = 0; j < currentTableSize; j++) {
        if (!theTable[j].isEmpty) {
            KeyType key = theTable[j].key;
            int hashvalue = hashValue(key) % (newTableSize);
                        
            while (!tempTable[hashvalue].isEmpty) { 
                hashvalue = (hashvalue + 1) % (newTableSize);        
            }

            tempTable[hashvalue].key = key;
            tempTable[hashvalue].samewords = theTable[j].samewords;
            tempTable[hashvalue].isEmpty = false;
        }
    }

    delete [] theTable;
    theTable = tempTable;
    currentTableSize = newTableSize;
}