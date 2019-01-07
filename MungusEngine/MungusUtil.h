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

	std::string getTextFromFile(const std::string& url);

	void reverseString(std::string* string);

	std::string removeAllWhiteSpace(const std::string& str);

	long long inline getStringIteratorIndex(const std::string::iterator& begin, const std::string::iterator& itr);

}
