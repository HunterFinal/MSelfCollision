#include "Collider2DManagement.h"

#ifndef SAVE_RELEASE
#include "../Utilities/memory_release_def.h"
#endif

namespace MSelfCollision
{
    namespace MManagement
    {
        Collider2DManagement::Collider2DManagement()
        {
            _colliders = std::vector<Collider2D*>(100);
        }
        Collider2DManagement::~Collider2DManagement()
        {
            // HACK とりあえずnewで作って管理する
            // HACK 後でPoolに切り替えて管理する
            for(auto col : _colliders)
            {
                SAVE_DELETE(col);
            }
        }
    }// namespace MManagement

}// namespace MSelfCollision