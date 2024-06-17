#pragma once

enum class ECollisionShape
{
	None = 0,
	Circle,
	Rect,	
};

namespace MCollision
{
    // 前方宣言
    class Collider2D;

	bool IsOverlap2D(Collider2D* col1,Collider2D* col2);
	bool IsCircleOverlapped2D(Collider2D* circle1,Collider2D* circle2);
	bool IsRectOverlapped2D(Collider2D* rect1,Collider2D* rect2);
	bool IsCircleAndRectOverlapped2D(Collider2D* circle,Collider2D* rect);
}