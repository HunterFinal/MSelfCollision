#include<iostream>

#include "Core/Vector/Vector.h"
#include "Core/Base/Transform2D.h"

using namespace Core;

int main()
{
	Transform2D t;
	Vector2 dir(5, 5);
	for (int i = 0; i < 10; ++i)
	{
		t.Translate(dir * (float)(i + 1));

		std::cout << t.GetPosition() << std::endl;
	}

	return 0;
}