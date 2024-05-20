#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>

#include "Core/Vector/Vector.h"
#include "Core/Base/Transform2D.h"
#include "Utilities/pool.h"
#include "Utilities/factory.h"

using namespace Core;

using namespace std;

class X:public MUtil::Factory<X>
{
public:
	X() { cout << "cons" << endl; }
	X(const X& rhs) { cout << "copy cons" << endl; }
	X& operator=(const X& rhs) { cout << "copy oper" << endl; return *this; }
	X(const X&& rhs) { cout << "move cons" << endl; }
	X& operator=(const X&& rhs) { cout << "move oper" << endl; return *this;}
	~X() { cout << "des:" << this << endl; }

}; 

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
	// �R���\�[�����J��
	AllocConsole();
	FILE* stream = nullptr;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONIN$", "r", stdin);
#endif // DEBUG
	{
		MUtil::IPool<X> *pool = new Pool<X>(10);

		pool->InitPool(X::GetFactory());

		for (int i = 0; i < 10; ++i)
		{
			X& obj = pool->Allocate();

			pool->Recycle(obj);
		}

		delete pool;
	}
#ifdef DEBUG
	system("pause");
	// �R���\�[�������
	FreeConsole();

#endif // DEBUG
	return 0;
}