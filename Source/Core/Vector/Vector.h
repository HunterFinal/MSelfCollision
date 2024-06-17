/*									Vector header									*/
// ------------------------------------------------------------------------------------
// File name			:Vector.h
// Summary				:Vector struct
// List					:1.Vector2
//						 2.Vector3
// Writer				:MAI ZHICONG(バク チソウ)
// Update Message		:2024/04/25		Create
//						:2024/04/27		Rewrite rules of operator overload
// ------------------------------------------------------------------------------------

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
		static const Vector2 Zero;
		/// <summary>
		/// Vector2(-1,0) (x = -1,y = 0)
		/// </summary>
		static const Vector2 Left;
		/// <summary>
		/// Vector2(1,0) (x = 1,y = 0)
		/// </summary>
		static const Vector2 Right;
		/// <summary>
		/// Vector2(0,1) (x = 0,y = 1)
		/// </summary>
		static const Vector2 Up;
		/// <summary>
		/// Vector2(0,-1) (x = 0,y = -1)
		/// </summary>
		static const Vector2 Down;
		/// <summary>
		/// Vector2(1,1) (x = 1,y = 1)
		/// </summary>
		static const Vector2 One;
		/// <summary>
		/// Vector2(INFINITY,INFINITY) (x = inf, y = inf)
		/// </summary>
		static const Vector2 PositiveInfinity;
		/// <summary>
		/// Vector2(-INFINITY,-INFINITY) (x = -inf, y = -inf)
		/// </summary>
		static const Vector2 NegativeInfinity;

	// Constructor
	//		: x(value)		
	//		, y(value)
	public:
		Vector2()											
			: x(0.f)	
			, y(0.f)
		{}

		explicit Vector2(const float _x)					
			: x(_x)			
			, y(0.f)	
		{}

		explicit Vector2(const float _x, 
						 const float _y)	noexcept
			: x(_x)			
			, y(_y)			
		{}

		// Copy
		Vector2(const Vector2& other)						
			: x(other.x)	
			, y(other.y)	
		{}
		// Move
		Vector2(Vector2&& other) noexcept					
			: x(other.x)	
			, y(other.y)	
		{	
			other.x = 0.f;
			other.y = 0.f; 
		}

		// Operator overload

		// Arithmetic(need to be global)
		friend Vector2	operator +	(const Vector2& self, const Vector2& other);
		friend Vector2	operator +	(const Vector2& self, const Vector3& other);
		friend Vector2	operator -	(const Vector2& self, const Vector2& other);
		friend Vector2	operator -	(const Vector2& self, const Vector3& other);
		friend Vector2	operator *	(const Vector2& self, const float num);
		friend Vector2	operator *	(const float num, const Vector2& self);
		friend Vector2	operator *	(const Vector2& self, const Vector2& other);
		friend Vector2	operator /	(const Vector2& self, const float num);

		// Equality Compare(need to be global)
		friend bool	operator ==	(const Vector2& self, const Vector2& other);
		friend bool	operator !=	(const Vector2& self, const Vector2& other);

		// Assignment
		Vector2& operator =	(const Vector2& other)&;
		Vector2& operator =	(const Vector3& other)&;
		Vector2& operator =	(Vector2&& other) & noexcept;

		// Unary Negation/Plus
		Vector2 operator+() const;
		Vector2 operator-() const;

		// Cast
		explicit operator Vector2() const noexcept;
		explicit operator Vector3() const noexcept;

		// Compound Assignment
		Vector2&	operator +=	(const Vector2& other);
		Vector2&	operator +=	(const Vector3& other);
		Vector2&	operator -=	(const Vector2& other);
		Vector2&	operator -=	(const Vector3& other);
		Vector2&	operator *=	(const float num);
		Vector2&	operator *=	(const Vector2& other);
		Vector2&	operator /=	(const float num);


	// Public method
	public:
		auto GetMagnitude()  const	-> float;
		auto GetNormalized() const	-> Vector2;
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
		static const Vector3 Zero;
		/// <summary>
		/// Vector3(-1,0,0) (x = -1, y = 0, z = 0)
		/// </summary>
		static const Vector3 Left;
		/// <summary>
		/// Vector3(1,0,0) (x = 1, y = 0, z = 0)
		/// </summary>
		static const Vector3 Right;
		/// <summary>
		/// Vector3(0,1,0) (x = 0, y = 1, z = 0)
		/// </summary>
		static const Vector3 Up;
		/// <summary>
		/// Vector3(0,-1,0) (x = 0, y = -1, z = 0)
		/// </summary>
		static const Vector3 Down;
		/// <summary>
		/// Vector3(0,0,1) (x = 0, y = 0, z = 1)
		/// </summary>
		static const Vector3 Forward;
		/// <summary>
		/// Vector3(0,0,-1) (x = 0, y = 0, z = -1)
		/// </summary>
		static const Vector3 Back;
		/// <summary>
		/// Vector3(1,1,1) (x = 1, y = 1, z = 1)
		/// </summary>
		static const Vector3 One;
		/// <summary>
		/// Vector3(INFINITY,INFINITY) (x = inf, y = inf, z = inf)
		/// </summary>
		static const Vector3 PositiveInfinity;
		/// <summary>
		/// Vector3(-INFINITY,-INFINITY) (x = -inf, y = -inf, z = -inf)
		/// </summary>
		static const Vector3 NegativeInfinity;

	// ---------------------------------------------------------
	// Constructor and Operator overload
	//		: x(value)			
	// 		, y(value)			
	// 		, z(value)
	// ---------------------------------------------------------
	public:
		Vector3()															
			: x(0.f)		
			, y(0.f)		
			, z(0.f)
		{}

		explicit Vector3(const float _x)									
			: x(_x)				
			, y(0.f)		
			, z(0.f)
		{}

		explicit Vector3(const float _x, 
						 const float _y)					
			: x(_x)				
			, y(_y)				
			, z(0.f)
		{}

		explicit Vector3(const float _x, 
						 const float _y,
						 const float _z)	noexcept
			: x(_x)				
			, y(_y)				
			, z(_z)					
		{}
		explicit Vector3(const Vector2 _v2, const float _z)					
			: x(_v2.x)			, y(_v2.y)			, z(_z)				
		{}

		// Copy
		Vector3(const Vector2& other)										
			: x(other.x)		
			, y(other.y)		
			, z(0.f)
		{}
		Vector3(const Vector3& other)										
			: x(other.x)		
			, y(other.y)		
			, z(other.z)	
		{}

		// Move
		Vector3(Vector3&& other) noexcept									
			: x(other.x)		
			, y(other.y)		
			, z(other.z)	
		{ 
			other.x = 0.f;
			other.y = 0.f;
			other.z = 0.f;
		}

		// Operator overload

		// Arithmetic(need to be global)
		friend Vector3	operator+(const Vector3& self, const Vector2& other);
		friend Vector3	operator+(const Vector3& self, const Vector3& other);
		friend Vector3	operator-(const Vector3& self, const Vector2& other);
		friend Vector3	operator-(const Vector3& self, const Vector3& other);
		friend Vector3	operator*(const Vector3& self, const float num);
		friend Vector3	operator*(const float num, const Vector3& self);
		friend Vector3	operator*(const Vector3& self, const Vector3& other);
		friend Vector3	operator/(const Vector3& self, const float num);

		// Equality Compare
		friend bool		operator==(const Vector3& self, const Vector3& other);
		friend bool		operator!=(const Vector3& self, const Vector3& other);

		// Assignment
		Vector3& operator=(const Vector2& other) &;
		Vector3& operator=(const Vector3& other) &;
		Vector3& operator=(Vector3&& other) & noexcept;

		// Unary Negation/Plus
		Vector3 operator+() const;
		Vector3 operator-() const;

		// Cast
		explicit operator Vector2() const noexcept;
		explicit operator Vector3() const noexcept;

		// Compound Assignment
		Vector3&	operator +=	(const Vector2& other);
		Vector3&	operator +=	(const Vector3& other);
		Vector3&	operator -=	(const Vector2& other);
		Vector3&	operator -=	(const Vector3& other);
		Vector3&	operator *=	(const float num);
		Vector3&	operator *=	(const Vector3& other);
		Vector3&	operator /=	(const float num);
		
	// Public method
	public:
		auto GetMagnitude()  const	-> float;
		auto GetNormalized() const	-> Vector3;
		void Normalize();

	};

}
