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

class X
{
public:
	X() : data(0){ cout << "cons" << endl; }
	X(int d) : data(d) { cout << "param cons" << endl;}
	X(const X& rhs) { data = rhs.data; cout << "copy cons" << endl; }
	X& operator=(const X& rhs){ cout << "copy oper" << endl; return *this; }
	X(const X&& rhs) noexcept { cout << "move cons" << endl; }
	X& operator=(const X&& rhs) noexcept { cout << "move oper" << endl; return *this;}
	~X() { cout << "des:" << this << endl; cout << data << endl;}

private:
	int data;
}; 

class FactoryX:public PlacementNewFactory<X>
{
	inline X* CreateProduct(void* const targetAddress) override;
};

X* FactoryX::CreateProduct(void* const targetAddress)
{
	return new(reinterpret_cast<X*>(targetAddress)) X(rand() % 10);
}

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
		MUtil::IPool<X> *pool = new Pool<X>(10);

		FactoryX pFactory;

		pool->InitPool(pFactory.GetFactory());

		X obj(100);
		for (int i = 0; i < 10; ++i)
		{
			pool->Allocate(obj);
			pool->Recycle(obj);
		}

		delete pool;
	}

{

}
#ifdef DEBUG
	system("pause");
	// コンソールを閉じる
	FreeConsole();

#endif // DEBUG
	return 0;
}