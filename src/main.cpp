#include <iostream>
#include "inverted_index.h"

int main(){
	InvertedIndex index;

	index.addDocument(101, "Wireless mouse and keyboard for gaming");
	index.addDocument(102, "Wired mouse for work and gaming");
	index.addDocument(103, "Wireless mouse for gaming");
	index.addDocument(104, "Wired keyboard for office work");

	std::vector<int> result1 = index.searchTerm("wireless");
	std::vector<int> result2 = index.searchTerm("mouse");
	std::vector<int> result3 = index.searchTerm("gaming");

	std::cout << "Documents containing 'wireless': ";
	for( int docId : result1) {
		std::cout << docId << " ";
	}
	std::cout << "\n";

	std::cout << "Documents containing 'mouse': ";
	for( int docId : result2) {
		std::cout << docId << " ";
	}
	std::cout << "\n";

	std::cout << "Documents containing 'gaming': ";
	for( int docId : result3) {
		std::cout << docId << " ";
	}
	std::cout << "\n";
}

