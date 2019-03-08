#VARIABLE DEFINITIONS
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g3

#RULES

##WEEK2: FINAL EXECUTABLE
gerp: DirNode.o FSTree.o FileStorage.o HashTable.o Gerp.o main.o
	${CXX} ${LDFLAGS} -o gerp DirNode.o FSTree.o FileStorage.o HashTable.o Gerp.o main.o

FileStorage.o: FileStorage.cpp FileStorage.h
HashTable.o: HashTable.cpp HashTable.h 
Gerp.o: Gerp.cpp Gerp.h HashTable.h FSTree.h DirNode.h
main.o: Gerp.h

##CLEAN
clean:
	rm -rf ./gerp *.o *.dSYM

##SUBMISSION
provideFirstWeek:
	provide comp15 proj2part2 FSTreeTraversal.cpp \
		stringProcessing.h \stringProcessing.cpp

provideSecondWeek:
	provide comp15 proj2part3 README Makefile FileStorage.cpp FileStorage.h \
		HashTable.cpp HashTable.h Gerp.cpp Gerp.h main.cpp testHashTable.cpp

##WEEK1: STRINGPROCESSING
testString: stringProcessing.o testStringProcessing.o
	${CXX} ${LDFLAGS} -o testString stringProcessing.o testStringProcessing.o

stringProcessing.o: stringProcessing.cpp stringProcessing.h
testStringProcessing.o: testStringProcessing.cpp stringProcessing.h

##WEEK1: TREE TRAVERSAL
treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o treeTraversal FSTreeTraversal.o FSTree.o DirNode.o

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h

##WEEK2: HASHTABLE
testHashTable: HashTable.o testHashTable.o
	${CXX} ${LDFLAGS} -o testHashTable HashTable.o testHashTable.o

HashTable.o: HashTable.cpp HashTable.h
testHashTable.o: testHashTable.cpp HashTable.h

