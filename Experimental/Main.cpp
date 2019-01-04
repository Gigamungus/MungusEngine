#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>

#define TYPE unsigned long long


int main(void) {
	char bytes[1000];
	TYPE num = 27.482364;
	for (int i = 0; i < sizeof(bytes) / sizeof(TYPE); i++) {
		memcpy(&bytes[i * sizeof(TYPE)], &num, sizeof(TYPE));
		num *= 3.123;
	}
	(TYPE*)bytes;
	TYPE* floats = (TYPE*)bytes;
	for (int i = 0; i < sizeof(bytes) / sizeof(TYPE); i++) {
		std::cout << floats[i] << "\n";
	}
	std::cin.get();

}
