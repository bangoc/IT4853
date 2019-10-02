#include <sstream>

#include "base.h"

bool Tokenize(TermsList& out, const std::string& doc) {
	std::stringstream ss{doc};
	std::string term;
	while (ss >> term) {
		out.push_back(term);
	}
	return true;
}