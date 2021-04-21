#include <iostream>
#include <stdexcept>
#include "includes/finders.hpp"
#include "external_includes/rapidxml.hpp"
#include "external_includes/rapidxml_utils.hpp"

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Please pass file format and file name as arguments\n";
		std::cout << "./executable file_format file_name\n";
		return 0;
	}

	std::string fileFormat = argv[1];
	std::string fileName = argv[2];

	try {
		rapidxml::file<> xmlFile{fileName.c_str()};
		rapidxml::xml_document<> document;
		document.parse<0>(xmlFile.data());

		std::vector<std::string> values;

		if (fileFormat == "aaa" || fileFormat == "AAA") {
			FinderAAA finder;
			values = finder.FindValues(&document);
		} else if (fileFormat == "nas" || fileFormat == "NAS") {
			FinderNAS finder;
			values = finder.FindValues(&document);
		} else {
			std::cout << "Invalid format\n";
			return 0;
		}

		for (auto val : values) {
			std::cout << val << '\n';
		}

		
	} catch (std::runtime_error re) {
		std::cout << "Couldn't open file with name: " << fileName << '\n';
	}

    return 0;
}
