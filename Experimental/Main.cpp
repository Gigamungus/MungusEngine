#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>

#include "../Resources/Vendor/JSON/json.hpp"
#include "../Resources/MungusLibs/MungusUtil.h"
using json = nlohmann::json;




class Test {
	int num;
public:
	Test(int num) : num(num) {}

	void sameAsThis(std::shared_ptr<Test> ptr) {
		std::cout << (this == &*ptr) << "\n";
	}
};

std::shared_ptr<Test> testFunc(std::shared_ptr<Test> ptr1, std::shared_ptr<Test> ptr2) {
	std::shared_ptr<Test> ptr3 = ptr1;
	std::shared_ptr<Test> ptr4 = ptr2;

	std::cout << (ptr3 == ptr4) << "\n" << (&*ptr1 == &*ptr4) << "\n";

	return ptr2;
}


int main(void) {

	std::shared_ptr<Test> ptr1 = std::make_shared<Test>(5);
	std::shared_ptr<Test> ptr2 = std::make_shared<Test>(10);

	ptr1->sameAsThis(ptr1);
	ptr1->sameAsThis(ptr2);

	std::cin.get();
}
