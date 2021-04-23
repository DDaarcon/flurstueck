#include <iostream>
#include <stdexcept>
#include <fstream>
#include "includes/finders.hpp"
#include "external_includes/units.hpp"

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Please pass file format and file name as arguments\n";
		std::cout << "./executable file_format file_name\n";
		return 0;
	}

	std::string fileFormat = argv[1];
	std::string fileName = argv[2];


	std::ifstream inFile(fileName);
	if (inFile.is_open()) {
		Units::Unit rootUnit;
		std::string fileProlog;
		rootUnit.ReadXML(inFile, true, &fileProlog);

		std::vector<std::string> values;

		if (fileFormat == "aaa" || fileFormat == "AAA") {
			FinderAAA finder;
			values = finder.FindValues(&rootUnit);
		} else if (fileFormat == "nas" || fileFormat == "NAS") {
			FinderNAS finder;
			values = finder.FindValues(&rootUnit);
		} else {
			std::cout << "Invalid format\n";
			return 0;
		}

		for (auto val : values) {
			std::cout << val << '\n';
		}

		
	} else {
		std::cout << "Couldn't open file with name: " << fileName << '\n';
	}

    return 0;
}
