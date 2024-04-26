/*						Transform2D header						*/
// ---------------------------------------------------------------
// File name			:Transform2D.h
// Summary				:Transform of 2D object
// Writer				:MAI ZHICONG(バク チソウ)
// Update Message		:2024/04/26		Create	
// ---------------------------------------------------------------

#pragma once

#include <iostream>
#include "../Vector/Vector.h"

namespace Core
{
	class Transform2D
	{
		//Constructor
	public:
		Transform2D() 
			: _pPosition2D(nullptr) 
		{
			_pPosition2D = new Vector2();
		}
		Transform2D(const Vector2& other)
			: _pPosition2D(nullptr)
		{
			_pPosition2D = new Vector2(other.x, other.y);
		}
		Transform2D(const float x,
					const float y)
			: _pPosition2D(nullptr)
		{
			_pPosition2D = new Vector2(x, y);
		}
		virtual ~Transform2D()
		{
			if (_pPosition2D != nullptr)
			{
				delete _pPosition2D;
				_pPosition2D = nullptr;
			}
			std::cout << "Transform2D Destructor";
		}

		// Equality Compare
		friend bool	operator == (const Transform2D& self, const Transform2D& other);
		friend bool	operator != (const Transform2D& self, const Transform2D& other);
		// Public Method
	public:
		void Translate(const Vector2& direction);
		void Translate(const Vector2& normalizedDirection, const float axisValue);
		auto GetPosition() const->	Vector2;
		// プロパティ
	private:
		Vector2* _pPosition2D;
	};

}

