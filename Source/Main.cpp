#include<iostream>
#include<windows.h>
#include<tchar.h>
#include<string>

#include "Core/Vector/Vector.h"
#include "Core/Base/Transform2D.h"

using namespace Core;

#ifdef _UNICODE
	typedef std::wstring STRING;
	#define ToString(x)		std::to_wstring(x)
#else
	typedef std::string STRING;
	#define ToString(x) std::to_string(x)
#endif //  _UNICODE

#define ToCString(x)	ToString(x).c_str()

#ifdef _UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
#endif
{
	Vector2 x1(5.f,10.f);

	MessageBox(nullptr, ToCString(x1.x), ToCString(x1.y), MB_OK);
	return 0;
}