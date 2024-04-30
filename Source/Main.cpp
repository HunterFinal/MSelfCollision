#include<iostream>

#include "Core/Vector/Vector.h"
#include "Core/Base/Transform2D.h"

using namespace Core;

int main()
{
	Transform2D* xx;

	xx = new Transform2D;

	xx->Test = 1;

	int x;

	x = xx->Test;

	std::cout << x << std::endl;

	x = 100;

	std::cout << xx->Test << std::endl;

	std::cout << x << std::endl;

	std::cout << xx->ReadonlyTest << std::endl;

	delete xx;
	xx = nullptr;

	return 0;
}