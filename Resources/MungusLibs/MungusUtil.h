#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>

#include <memory>

namespace MungusUtil {

	std::string getTextFromFile(const std::string& url) {
		std::stringstream stream;
		std::string line;
		std::fstream file(url);
		if (!file.is_open())
			std::cout << "couldn't open file: " << url;
		else
			while (std::getline(file, line))
				stream << line << "\n";

		return stream.str();
	}

	void reverseString(std::string* string) {
		size_t size = string->size();
		for (size_t i = 0, j = size - 1; i < size / 2; i++, j--) {
			char tmp = (*string)[i];
			(*string)[i] = (*string)[j];
			(*string)[j] = tmp;
		}
	}

	std::string removeAllWhiteSpace(const std::string* str) {
		std::stringstream stream;

		for (char letter : *str) {
			if (letter != ' ' && letter != '\t' && letter != '\n') {
				stream << letter;
			}
		}

		return stream.str();
	}

}