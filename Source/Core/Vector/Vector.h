   /*						Vector header							*/
// -------------------------------------------------------------------
// File name			:Vector.h
// Summary				:Vector struct
// List					:1.Vector2
//						 2.Vector3
// Writer				:MAI ZHICONG(バク チソウ)
// Update Message		:2024/04/25		Create
// 
// -------------------------------------------------------------------

#pragma once

#include <iostream>

namespace Core
{
	struct Vector2;
	struct Vector3;

	struct Vector2
	{
		// std::cout overload
		friend std::ostream& operator<<(std::ostream& o, const Vector2& v2);

		// Member
		float x;
		float y;
		
	// Static Properties
	public:
		/// <summary>
		/// Vector2(0,0) (x = 0,y = 0)
		/// </summary>
		static Vector2 Zero;
		/// <summary>
		/// Vector2(-1,0) (x = -1,y = 0)
		/// </summary>
		static Vector2 Left;
		/// <summary>
		/// Vector2(1,0) (x = 1,y = 0)
		/// </summary>
		static Vector2 Right;
		/// <summary>
		/// Vector2(0,1) (x = 0,y = 1)
		/// </summary>
		static Vector2 Up;
		/// <summary>
		/// Vector2(0,-1) (x = 0,y = -1)
		/// </summary>
		static Vector2 Down;
		/// <summary>
		/// Vector2(1,1) (x = 1,y = 1)
		/// </summary>
		static Vector2 One;
		/// <summary>
		/// Vector2(INFINITY,INFINITY) (x = inf, y = inf)
		/// </summary>
		static Vector2 PositiveInfinity;
		/// <summary>
		/// Vector2(-INFINITY,-INFINITY) (x = -inf, y = -inf)
		/// </summary>
		static Vector2 NegativeInfinity;

	// Constructor and Operator overload
	public:
		Vector2() : x((float)0), y((float)0) {}
		explicit Vector2(const float _x) : x(_x), y((float)0) {}
		explicit Vector2(const float _x, const float _y) : x(_x), y(_y) {}

		// Copy
		Vector2(const Vector2& other) : x(other.x), y(other.y) {}
		Vector2& operator=(const Vector2& other);
		Vector2& operator=(const Vector3& other);

		// Move
		Vector2(Vector2&& other) noexcept : x(other.x), y(other.y) { other.x = (float)0; other.y = (float)0; }
		Vector2& operator=(Vector2&& other) noexcept;

		// Operator overload
		Vector2 operator+(const Vector2& other);
		Vector2& operator+=(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2 operator*(const float num);
		Vector2 operator*(const Vector2& other);
		Vector2& operator*=(const float num);
		Vector2& operator*=(const Vector2& other);
		Vector2 operator/(const float num);
		Vector2& operator/=(const float num);
		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

	// Public method
	public:
		auto GetMagnitude() const -> float;
		auto GetNormalized() const-> Vector2;
		void Normalize();

	};

	struct Vector3
	{
		// std::cout overload
		friend std::ostream& operator<<(std::ostream& o, const Vector3& v3);

		// Member
		float x;
		float y;
		float z;

	// Static Properties
	public:
		/// <summary>
		/// Vector3(0,0,0) (x = 0, y = 0, z = 0)
		/// </summary>
		static Vector3 Zero;
		/// <summary>
		/// Vector3(-1,0,0) (x = -1, y = 0, z = 0)
		/// </summary>
		static Vector3 Left;
		/// <summary>
		/// Vector3(1,0,0) (x = 1, y = 0, z = 0)
		/// </summary>
		static Vector3 Right;
		/// <summary>
		/// Vector3(0,1,0) (x = 0, y = 1, z = 0)
		/// </summary>
		static Vector3 Up;
		/// <summary>
		/// Vector3(0,-1,0) (x = 0, y = -1, z = 0)
		/// </summary>
		static Vector3 Down;
		/// <summary>
		/// Vector3(0,0,1) (x = 0, y = 0, z = 1)
		/// </summary>
		static Vector3 Forward;
		/// <summary>
		/// Vector3(0,0,-1) (x = 0, y = 0, z = -1)
		/// </summary>
		static Vector3 Back;
		/// <summary>
		/// Vector3(1,1,1) (x = 1, y = 1, z = 1)
		/// </summary>
		static Vector3 One;
		/// <summary>
		/// Vector3(INFINITY,INFINITY) (x = inf, y = inf, z = inf)
		/// </summary>
		static Vector3 PositiveInfinity;
		/// <summary>
		/// Vector3(-INFINITY,-INFINITY) (x = -inf, y = -inf, z = -inf)
		/// </summary>
		static Vector3 NegativeInfinity;

	// Constructor
	public:
		Vector3() : x((float)0), y((float)0),z((float)0) {}
		explicit Vector3(const float _x) : x(_x), y((float)0), z((float)0) {}
		explicit Vector3(const float _x, const float _y) : x(_x), y(_y), z((float)0) {}
		explicit Vector3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
		explicit Vector3(const Vector2 _v2, const float _z) : x(_v2.x), y(_v2.y), z(_z) {}

		// Copy
		Vector3(const Vector2& other) : x(other.x), y(other.y), z((float)0) {}
		Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
		Vector3& operator=(const Vector2& other);
		Vector3& operator=(const Vector3& other);

		// Move
		Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z) { other.x = (float)0; other.y = (float)0; other.z = (float)0; }
		Vector3& operator=(Vector3&& other) noexcept;

		// Operator overload
		Vector3 operator+(const Vector2& other);
		Vector3 operator+(const Vector3& other);
		Vector3& operator+=(const Vector2& other);
		Vector3& operator+=(const Vector3& other);
		Vector3 operator-(const Vector2& other);
		Vector3 operator-(const Vector3& other);
		Vector3& operator-=(const Vector2& other);
		Vector3& operator-=(const Vector3& other);
		Vector3 operator*(const float num);
		Vector3 operator*(const Vector3& other);
		Vector3& operator*=(const float num);
		Vector3& operator*=(const Vector3& other);
		Vector3 operator/(const float num);
		Vector3& operator/=(const float num);
		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);
		
	// Public method
	public:
		auto GetMagnitude() const -> float;
		auto GetNormalized() const-> Vector3;
		void Normalize();

	};

}
