#include "Transform2D.h"

namespace Core
{
	bool Transform2D::operator==(const Transform2D& other)
	{
		return (*this) == other;
	}

	bool Transform2D::operator!=(const Transform2D& other)
	{
		return !((*this) == other);
	}
	
	void Transform2D::Translate(const Vector2& direction)
	{
		if (_pPosition2D != nullptr)
		{
			(*_pPosition2D) += direction;
		}
	}

	void Transform2D::Translate(const Vector2& normalizedDirection, const float axisValue)
	{
		if (_pPosition2D != nullptr)
		{
			(*_pPosition2D) += (normalizedDirection * axisValue);
		}
	}

	Vector2 Transform2D::GetPosition() const
	{
		if (_pPosition2D != nullptr)
		{
			Vector2 pos(*_pPosition2D);
			return pos;
		}
		return Vector2::Zero;
	}

}