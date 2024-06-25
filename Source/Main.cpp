#include <iostream>		// std::cout std::endl
#include <windows.h>	// 
#include <tchar.h>
#include <string>
#include <vector>		// std::vector<T>

#include "Core/Vector/vector.h"
#include "Core/Base/Transform2D.h"
#include "Utilities/pool.h"
#include "Utilities/factory.h"

using namespace Core;

using namespace std;

using namespace MDesignPattern;

class X
{
public:
	X() : data(0){ cout << "cons" << endl; }
	X(int d) : data(d) { cout << "param cons :" << data << endl;}
	X(const X& rhs) { data = rhs.data; cout << "copy cons" << endl; }
	X& operator=(const X& rhs){ cout << "copy oper" << endl; return *this; }
	X(const X&& rhs) noexcept { data = rhs.data; cout << "move cons" << endl; }
	X& operator=(const X&& rhs) noexcept { data = rhs.data; return *this;}
	~X() { cout << "des:" << this << endl; cout << data << endl;}

public:
	int data;
}; 

class FactoryX:public MFactory::PlacementNewFactory<X>
{
	inline X* CreateProduct(void* const targetAddress) override;
};

X* FactoryX::CreateProduct(void* const targetAddress)
{
	return new(reinterpret_cast<X*>(targetAddress)) X(rand() % 100);
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

	// pool test
	{
		MUtil::IPool<X> *pool = new MUtil::Pool<X>(10);

		srand(static_cast<unsigned>(time(nullptr)));
		FactoryX pFactory;

		pool->InitPool(pFactory.GetFactory());

		X* obj;

		for (int i = 0; i < pool->GetCapacity(); ++i)
		{
			obj = pool->Allocate();
			if(obj != nullptr)
			{
				pool->Recycle(obj);
			}
		}

		obj = pool->Allocate();

		delete pool;

	}

	// singleton test

{

}
#ifdef DEBUG
	system("pause");
	// コンソールを閉じる
	FreeConsole();

#endif // DEBUG
	return 0;
}