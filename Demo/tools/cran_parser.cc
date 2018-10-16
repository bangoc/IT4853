#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::string line;
	bool first_line;
	while (std::getline(std::cin, line)) {
		if (line[0] == '.' && line[1] == 'I') {
			if (!first_line) {
				std::cout << std::endl;
			} else {
				first_line = false;
			}
		}
		std::cout << line << " ";
	}
}