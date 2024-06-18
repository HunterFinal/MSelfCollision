#pragma once

#include "../Vector/Vector.h"

enum class ECollisionShape;

struct Collision2D;

namespace Core
{
	class Collider2D
	{

	public:
		virtual bool IsHit() = 0;
		Collision2D GetHitCollision2D();	

	// 	コンストラクタ・デストラクタ
	public:
		Collider2D();
		virtual ~Collider2D();

	// コピー・ムーブ
	public:
		// コピー
		Collider2D(const Collider2D& other);
		Collider2D& operator =(const Collider2D& other);

		// ムーブ
		Collider2D(Collider2D&& other) noexcept;
		Collider2D& operator =(Collider2D&& other) noexcept;

	// Public method
	// Getter
	public:
		ECollisionShape GetShape() const;
		Vector2 GetCenter2D() const;
		bool IsActive() const { return _bActive;}

	// Setter
	public: 
		void SetCenter2D(const Vector2& center);
		void SetActive(bool bValue);

	protected:
		ECollisionShape _shape;
		Vector2 _center;

	private:
		bool _bActive;

	};

	class BoxCollider2D final : public Collider2D
	{
	public:
		BoxCollider2D();
		~BoxCollider2D() override;
	private:
		Vector2 _size;

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

