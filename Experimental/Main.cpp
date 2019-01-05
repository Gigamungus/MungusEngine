#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>


void reverseString(std::string* string) {
	size_t size = string->size();
	for (size_t i = 0, j = size - 1; i < size / 2; i++, j--) {
		char tmp = (*string)[i];
		(*string)[i] = (*string)[j];
		(*string)[j] = tmp;
	}
}

int main(void) {
	std::string str = "1234567890";
	reverseString(&str);

	std::cout << str << "\n";
	std::cin.get();
}
