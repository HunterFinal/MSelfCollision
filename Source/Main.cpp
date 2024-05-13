#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>

#include "Core/Vector/Vector.h"
#include "Core/Base/Transform2D.h"
#include "Utilities/pool.h"

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
#ifdef DEBUG
	// コンソールを開く
	AllocConsole();
	FILE* stream = nullptr;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONIN$", "r", stdin);
#endif // DEBUG
	{
		MUtil::IPool<char> *pool = new Pool<char>(10);

		for (int i = 0; i < 10; ++i)
		{
			char obj = pool->Allocate();

			obj = (char)('0' + i);

			pool->Recycle(obj);
		}

		delete pool;
	}
#ifdef DEBUG
	system("pause");
	// コンソールを解放
	FreeConsole();

#endif // DEBUG
	return 0;
}