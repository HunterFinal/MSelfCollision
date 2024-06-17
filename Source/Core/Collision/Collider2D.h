#pragma once

#include "../Vector/Vector.h"

enum class ECollisionShape;

namespace Core
{
	class Collider2D
	{

	public:
		virtual bool IsHit(Collider2D *other) = 0;	

	// 	コンストラクタ・デストラクタ
	public:
		Collider2D();
		virtual ~Collider2D();

	// コピー・ムーブ
	public:
		// コピー
		Collider2D(const Collider2D& rhs);
		Collider2D& operator =(const Collider2D& rhs);

		// ムーブ
		Collider2D(Collider2D&& rhs) noexcept;
		Collider2D& operator =(Collider2D&& rhs) noexcept;

	public:
		// 

	protected:
		ECollisionShape _shape;
		Vector2 _center;

	};

	class BoxCollider2D final : public Collider2D
	{
	public:
		BoxCollider2D();
		~BoxCollider2D() override;
	private:
		Vector2* _size;

	};

	class CircleCollider2D final: public Collider2D
	{
	public:
		CircleCollider2D();
		~CircleCollider2D() override;
	private:
		float _radius;
	};


}

