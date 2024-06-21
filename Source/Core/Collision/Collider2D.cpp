#include "Collider2D.h"

#include "../Vector/vector.h"
#include "MCollisionFunction.h"

namespace MSelfCollision
{
 
    Collider2D::Collider2D()
            : _shape(ECollisionShape::None)
            , _center(Core::Vector2::Zero)
    {
        ;
    }

    Collider2D::~Collider2D()
    {
        // –³Œø‚Ì’l‚É‚·‚é
        _shape = ECollisionShape::None;
        _center = Core::Vector2::PositiveInfinity;
    }

    Collider2D::Collider2D(const Collider2D &rhs)
            : _shape(rhs._shape)
            , _center(rhs._center)
    {
        ;
    }

    Collider2D& Collider2D::operator=(const Collider2D &rhs)
    {
        // TODO: insert return statement here
        _shape = rhs._shape;
        _center = rhs._center;

        return *this;
    }

    Collider2D::Collider2D(Collider2D &&rhs) noexcept
    {
        _shape = rhs._shape;
        _center = std::move(rhs._center);

        rhs._shape = ECollisionShape::None;
        rhs._center = Core::Vector2::PositiveInfinity;
    }

    Collider2D& Collider2D::operator=(Collider2D &&rhs) noexcept
    {
        // TODO: insert return statement here
        _shape = rhs._shape;
        _center = std::move(rhs._center);

        rhs._shape = ECollisionShape::None;
        rhs._center = Core::Vector2::PositiveInfinity;

        return *this;        
    }

}
