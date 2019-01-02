#pragma once

#define MUNGUS __declspec(dllexport)

class MUNGUS Test {
public:
	void print(const char* str);
};