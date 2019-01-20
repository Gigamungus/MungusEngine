#include <iostream>
#include <string>
#include <sstream>

#include <filesystem>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <stack>


struct Thing {
	Thing* other = nullptr;
};

void test(void) {
	Thing thing1 = *new Thing();
	Thing thing2 = *new Thing();

	thing1.other = &thing2;
	thing2.other = &thing1;
}

int main(void) {
	while (true)
		test();


	std::cin.get();
}
