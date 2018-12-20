all: Node.h Buffer.h Iterator.h Node.cpp Iterator.cpp Buffer.cpp
	g++ main.cpp -o a.out Node.cpp Buffer.cpp Iterator.cpp
node: Node.h Node.cpp
	g++ -Wall -o testNode testNode.cpp Node.cpp -std=c++11
iter: Iterator.h Iterator.cpp Node.h Node.cpp
	g++ -Wall -o testIterator testIterator.cpp Iterator.cpp Node.cpp -std=c++11
