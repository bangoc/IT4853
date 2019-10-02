#include "parser.h"

#include <fstream>
#include <iostream>

bool ParseCollection(Collection& col, const std::string& fname) {
	std::ifstream inp{fname};
	std::string doc;
	while (std::getline(inp, doc)) {
		col.push_back(doc);
	}
	std::cout << "Number of documents " << col.size() << std::endl;
	for (int i = 0; i < col.size(); ++i) {
		std::cout << "VB " << i << ": " << col[i] << std::endl;
	}
	return true;
}