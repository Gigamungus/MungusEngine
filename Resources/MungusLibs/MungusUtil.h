#pragma once

#ifndef MUNGUS_UTIL
#define MUNGUS_UTIL

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

	inline std::string getTextFromFile(const std::string& url) {
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

	inline void reverseString(std::string* string) {
		size_t size = string->size();
		for (size_t i = 0, j = size - 1; i < size / 2; i++, j--) {
			char tmp = (*string)[i];
			(*string)[i] = (*string)[j];
			(*string)[j] = tmp;
		}
	}

	inline std::string removeAllWhiteSpace(const std::string& str) {
		std::stringstream stream;

		for (char letter : str) {
			if (letter != ' ' && letter != '\t' && letter != '\n') {
				stream << letter;
			}
		}

		return stream.str();
	}

	inline std::vector<std::string> splitString(std::string str, const std::string& delimiter) {
		std::vector<std::string> values;

		unsigned long long pos = 0;

		while ((pos = str.find(delimiter)) != std::string::npos) {
			values.push_back(str.substr(0, pos));
			str.erase(0, pos + delimiter.length());
		}
		std::cout << str << std::endl;

		return values;
	}

	inline long long getStringIteratorIndex(const std::string::iterator& begin, const std::string::iterator& itr) {
		return std::distance(begin, itr);
	}

	inline float min(float one, float two) {
		return one < two ? one : two;
	}

	inline float max(float one, float two) {
		return one > two ? one : two;
	}

	inline float min3(float one, float two, float three) {
		return (one < two) ? ((one < three) ? one : three) : ((two < three) ? two : three);
	}

	inline float max3(float one, float two, float three) {
		return (one > two) ? ((one > three) ? one : three) : ((two > three) ? two : three);
	}

}

#endif // MUNGUS_UTIL
