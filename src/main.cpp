#include <iostream>
#include "inverted_index.h"

int main(){
	InvertedIndex index;

	index.addDocument(101, "Wireless mouse and keyboard for gaming");
	index.addDocument(102, "Wired mouse for work and gaming");
	index.addDocument(103, "Wireless mouse for gaming");
	index.addDocument(104, "Wired keyboard for office work");

	std::unordered_map<int, int> result1 = index.searchTerm("wireless");
	std::unordered_map<int, int> result2 = index.searchTerm("mouse");
	std::unordered_map<int, int> result3 = index.searchTerm("gaming");

	std::cout << "Documents containing 'wireless': ";
	for( const auto& [docId, freq] : result1) {
		std::cout << "(Doc Id: " << docId << ", Frequency: " << freq << ") ";
	}
	std::cout << "\n";

	std::cout << "Documents containing 'mouse': ";
	for( const auto& [docId, freq] : result2) {
		std::cout << "(Doc Id: " << docId << ", Frequency: " << freq << ") ";
	}
	std::cout << "\n";

	std::cout << "Documents containing 'gaming': ";
	for( const auto& [docId, freq] : result3) {
		std::cout << "(Doc Id: " << docId << ", Frequency: " << freq << ") ";
	}
	std::cout << "\n";
}

