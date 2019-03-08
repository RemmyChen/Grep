/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  FileStorage.h
 *  Complete FileStorage Class Interface
 *  Modified By (UTLN): rchen07
 *           On       : 11/30/2017
 *
 */

#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <iostream>
#include <string>
#include <vector>


struct Line {
        std::string wordPhrase;
        int lineNo;

        Line()
        {
                wordPhrase = "";
                lineNo = 0;
        }
        Line(std::string wordphrase, int lineno)
        {
                wordPhrase = wordphrase;
                lineNo = lineno;
        }
};


class FileStorage
{

public:

		FileStorage(); /* constructor */
		~FileStorage(); /* destructor */

                /* Saves incoming document lines and filepaths (without repetition).
                Checks if filepath has already been stored. */
		void save(std::string filepath, int fileno, std::string wordphrase, int lineno);
		
                /* Prints word's filepath, line number, and line. */
                void print(int fileno, int lineno);

private:

		struct File {
                        std::string filePath;
                        int fileNo;
                        std::vector<Line> wordPhrases;

                        File()
                        {
                        	filePath = "";
                                fileNo = 0;
                        	wordPhrases = std::vector<Line>();
                        }
                        File(std::string filepath, int fileno, std::string wordphrase, int lineno)
                        {
                        	filePath = filepath;
                                fileNo = fileno;
                        	wordPhrases = std::vector<Line>();
                        	wordPhrases.push_back({wordphrase, lineno});
                        }
                };

		std::vector<File> theStorage;

                /* Saves incoming document lines (without repetition).
                Checks if document line has already been stored. */
                void checkLine(int fileno, std::string wordphrase, int lineno);
        
};

#endif