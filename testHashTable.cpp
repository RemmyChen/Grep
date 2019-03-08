/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  testHashTable.cpp
 *  Test first version of HashTable (contained repetitions) implementation.
 *  Modified By (UTLN): rchen07
 *           On       : 11/15/2017
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

#include "HashTable.h"

using namespace std;


struct WordData {
        string   title;
        WordInfo info;
};

void run_tests(WordData words[], int numWords);


int main()
{
        WordData words[] = {
                            {"we", {"we", "/we/me/", "this is a test", 104}},
                            {"wish", {"wish", "/make/a/", "this is a test", 128}},
                            {"you", {"you", "/i/ok/", "this is a test", 129}},
                            {"a", {"a", "/apple/for/", "this is a test", 109 }},
                            {"merry", {"merry", "/santa/", "this is a test", 126}},
                            {"christmas", {"christmas", "/cold/", "this is a test", 116}},
                            {"we", {"wE", "/again/", "this is a test", 115}},
                            {"wish", {"wISh", "/i/", "this is a test", 117}},
                            {"you", {"YOU", "/you/stop/", "this is a test", 105}},
                            {"a", {"A", "/aaa/", "this is a test", 127}},
                            {"happy", {"happy", "/oh/so/", "this is a test", 127}},
                            {"new", {"new", "/smells/like/", "this is a test", 127}},
                            {"year", {"year", "/rooster/", "this is a test", 127}}
                           };
        int numWords = sizeof(words) / sizeof(WordData);

        run_tests(words, numWords);

        return 0;
}

/*  PURPOSE: hashes words and prints results
    RETURN: void
    PARAMETERS: WordData struct and int */
void run_tests(WordData words[], int numWords)
{
        HashTable wordDB;
        
        cout << "Inserting keys:";
        for (int i = 0; i < numWords; ++i) {
                cout << " \"" << words[i].title << "\"";
                wordDB.insert(words[i].title, words[i].info);
        }
        cout << endl;

        wordDB.print();
        cout << endl;
}