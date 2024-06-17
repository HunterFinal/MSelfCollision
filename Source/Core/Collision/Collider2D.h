#pragma once

struct Vector2;
enum class ECollisionShape;

namespace Core
{
		class Collider2D
	{

	public:
		virtual bool IsHit() = 0;	

	public:
		Collider2D();
		virtual ~Collider2D();

	protected:
		ECollisionShape _shape;
		Vector2* _center;

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

