#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>


struct Test {
	std::vector<float> floats;
	int i;
};

int main(void) {
	Test test;

	std::cout << offsetof(Test, i) << "\n";

	test.floats.push_back(1.0);
	test.floats.push_back(1.0);
	test.floats.push_back(1.0);
	test.floats.push_back(1.0);


	std::cout << offsetof(Test, i) << "\n";


	std::cin.get();
}
