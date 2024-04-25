/*						     Vector	cpp  						    */
// -------------------------------------------------------------------
// File name			:Vector.cpp
// Summary				:Vector implement
// List					:1.Vector2
//						 2.Vector3
// Writer				:MAI ZHICONG(バク チソウ)
// Update Message		:2024/04/25		Create
// 
// -------------------------------------------------------------------


#include <cmath>

#include "Vector.h"

#ifndef _FLOAT_TOLERANCE

#define FLOAT_TOLERANCE (float) 0.000001

#endif // !_FLOAT_TOLERANCE

namespace Core
{
// Vector2 
#pragma region Vector2
	// Static properties initialize 
	#pragma region Static properties initialize

		Vector2 Vector2::Zero(0, 0);
		Vector2 Vector2::Left(-1, 0);
		Vector2 Vector2::Right(1, 0);
		Vector2 Vector2::Up(0, 1);
		Vector2 Vector2::Down(0, -1);
		Vector2 Vector2::One(1, 1);
		Vector2 Vector2::PositiveInfinity(INFINITY, INFINITY);
		Vector2 Vector2::NegativeInfinity(-INFINITY, -INFINITY);

	#pragma endregion

	// Operator overload
	#pragma region Operator overload

		std::ostream& operator<<(std::ostream& o, const Vector2& v2)
		{
			o << '(' << v2.x << ',' << v2.y << ')';
			return o;
		}

		Vector2& Vector2::operator=(const Vector2& other)
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		Vector2& Vector2::operator=(const Vector3& other)
		{
			x = other.x;
			y = other.y;

			return *this;
		}

		Vector2& Vector2::operator=(Vector2&& other) noexcept
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;

				other.x = (float)0;
				other.y = (float)0;
			}
			return *this;
		}

		Vector2 Vector2::operator+(const Vector2& other)
		{
			Vector2 addVec;
			addVec.x = x + other.x;
			addVec.y = y + other.y;
			return addVec;
		}

		Vector2& Vector2::operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector2 Vector2::operator-(const Vector2& other)
		{
			Vector2 subVec;
			subVec.x = x - other.x;
			subVec.y = y - other.y;
			return subVec;
		}

		Vector2& Vector2::operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector2 Vector2::operator*(const float num)
		{
			Vector2 mulVec;
			mulVec.x = x * num;
			mulVec.y = y * num;

			return mulVec;
		}

		Vector2 Vector2::operator*(const Vector2& other)
		{
			Vector2 mulVec;
			mulVec.x = x * other.x;
			mulVec.y = y * other.y;

			return mulVec;
		}

		Vector2& Vector2::operator*=(const float num)
		{
			x *= num;
			y *= num;

			return *this;
		}

		Vector2& Vector2::operator*=(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		Vector2 Vector2::operator/(const float num)
		{
			try
			{
				if (num == (float)0)
				{
					throw std::invalid_argument("Can't divide by 0");
				}
				Vector2 divVec;
				divVec.x = x / num;
				divVec.y = y / num;
				return divVec;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				std::exit(-1);
			}
		}

		Vector2& Vector2::operator/=(const float num)
		{
			try
			{
				if (num == (float)0)
				{
					throw std::invalid_argument("Can't divide by 0");
				}
				x /= num;
				y /= num;
				return *this;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				std::exit(-1);
			}
		}

		bool Vector2::operator==(const Vector2& other)
		{
			// Check x
			if ((x - other.x) > -FLOAT_TOLERANCE && (x - other.x) < FLOAT_TOLERANCE)
			{
				// Check y
				if ((y - other.y) > -FLOAT_TOLERANCE && (y - other.y) < FLOAT_TOLERANCE)
					return true;
			}
			return false;

		}

		bool Vector2::operator!=(const Vector2 & other)
		{
			return !(*this == other);
		}

	#pragma endregion

	// Public method
	#pragma region Public method
		float Vector2::GetMagnitude() const
		{
			return sqrtf((powf(x, (float)2) + powf(y, (float)2)));
		}

		Vector2 Vector2::GetNormalized() const
		{
			Vector2 normalize(*this);

			float tempManitude = GetMagnitude();

			if (tempManitude < FLOAT_TOLERANCE)
			{
				return Zero;
			}

			return normalize / GetMagnitude();
		}

		void Vector2::Normalize()
		{
			float tempMagnitude = GetMagnitude();

			if (tempMagnitude < FLOAT_TOLERANCE)
			{
				return;
			}

			x /= tempMagnitude;
			y /= tempMagnitude;

		}

	#pragma endregion

#pragma endregion

// Vector3
#pragma region Vector3
	// Static properties initialize 
	#pragma region Static properties initialize 
		Vector3 Vector3::Zero(0, 0, 0);
		Vector3 Vector3::Left(-1, 0, 0);
		Vector3 Vector3::Right(1, 0, 0);
		Vector3 Vector3::Up(0, 1, 0);
		Vector3 Vector3::Down(0, -1, 0);
		Vector3 Vector3::Forward(0, 0, 1);
		Vector3 Vector3::Back(0, 0, -1);
		Vector3 Vector3::One(1, 1, 1);
		Vector3 Vector3::PositiveInfinity(INFINITY, INFINITY, INFINITY);
		Vector3 Vector3::NegativeInfinity(-INFINITY, -INFINITY, -INFINITY);
	#pragma endregion

	// Operator overload
	#pragma region Operator overload

		std::ostream& operator<<(std::ostream& o, const Vector3& v3)
		{
			o << '(' << v3.x << ',' << v3.y << ',' << v3.z << ')';
			return o;
		}

		Vector3& Vector3::operator=(const Vector2& other)
		{
			x = other.x;
			y = other.y;
			z = (float)0;

			return *this;
		}

		Vector3& Vector3::operator=(const Vector3& other)
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;
				z = other.z;
			}

			return *this;
		}

		Vector3& Vector3::operator=(Vector3&& other) noexcept
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;
				z = other.z;

				other.x = (float)0;
				other.y = (float)0;
				other.z = (float)0;
			}

			return *this;
		}

		Vector3 Vector3::operator+(const Vector2& other)
		{
			Vector3 addVec;
			addVec.x = x + other.x;
			addVec.y = y + other.y;
			addVec.z = z;

			return addVec;
		}

		Vector3 Vector3::operator+(const Vector3& other)
		{
			Vector3 addVec;
			addVec.x = x + other.x;
			addVec.y = y + other.y;
			addVec.z = z + other.z;

			return addVec;
		}

		Vector3& Vector3::operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector3& Vector3::operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}
		Vector3 Vector3::operator-(const Vector2& other)
		{
			Vector3 subVec;
			subVec.x = x - other.x;
			subVec.y = y - other.y;
			subVec.z = z;

			return subVec;
		}

		Vector3 Vector3::operator-(const Vector3& other)
		{
			Vector3 subVec;
			subVec.x = x - other.x;
			subVec.y = y - other.y;
			subVec.z = z;

			return subVec;
		}

		Vector3& Vector3::operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector3& Vector3::operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		Vector3 Vector3::operator*(const float num)
		{
			Vector3 mulVec;
			mulVec.x = x * num;
			mulVec.y = y * num;
			mulVec.z = z * num;

			return mulVec;
		}

		Vector3 Vector3::operator*(const Vector3& other)
		{
			Vector3 mulVec;
			mulVec.x = x * other.x;
			mulVec.y = y * other.y;
			mulVec.z = z * other.z;

			return mulVec;
		}

		Vector3& Vector3::operator*=(const float num)
		{
			x *= num;
			y *= num;
			z *= num;

			return *this;
		}

		Vector3& Vector3::operator*=(const Vector3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		Vector3 Vector3::operator/(const float num)
		{
			try
			{
				if (num == (float)0)
				{
					throw std::invalid_argument("Can't divide by 0");
				}
				Vector3 divVec;
				divVec.x = x / num;
				divVec.y = y / num;
				divVec.z = z / num;

				return divVec;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				std::exit(-1);
			}
		}

		Vector3& Vector3::operator/=(const float num)
		{
			try
			{
				if (num == (float)0)
				{
					throw std::invalid_argument("Can't divide by 0");
				}
				x /= num;
				y /= num;
				z /= num;

				return *this;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				std::exit(-1);
			}
		}

		bool Vector3::operator==(const Vector3& other)
		{
			// Check x
			if ((x - other.x) > -FLOAT_TOLERANCE && (x - other.x) < FLOAT_TOLERANCE)
			{
				// Check y
				if ((y - other.y) > -FLOAT_TOLERANCE && (y - other.y) < FLOAT_TOLERANCE)
				{
					// Check z
					if ((z - other.z) > -FLOAT_TOLERANCE && (z - other.z) < FLOAT_TOLERANCE)
						return true;
				}
			}
			return false;
		}

		bool Vector3::operator!=(const Vector3& other)
		{
			return !((*this) == other);
		}

#pragma endregion

	// Public method
	float Vector3::GetMagnitude() const
	{
		return sqrtf((powf(x, (float)2) + powf(y, (float)2)) + powf(z, (float)2));
	}

	Vector3 Vector3::GetNormalized() const
	{
		Vector3 normalized(*this);

		float tempMagnitude = GetMagnitude();

		if (tempMagnitude < FLOAT_TOLERANCE)
		{
			return Zero;
		}

		return normalized / tempMagnitude;
	}

	void Vector3::Normalize()
	{
		float tempMagnitude = GetMagnitude();

		if (tempMagnitude < FLOAT_TOLERANCE)
		{
			return;
		}

		x /= tempMagnitude;
		y /= tempMagnitude;
		z /= tempMagnitude;
	}

#pragma endregion

}


