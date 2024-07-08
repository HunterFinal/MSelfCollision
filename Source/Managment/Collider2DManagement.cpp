#include "Collider2DManagement.h"

#include "../Core/Collision/collider2D.h"

#ifndef SAVE_RELEASE
#include "../Utilities/memory_release_def.h"
#endif

namespace MSelfCollision
{
    namespace MManagement
    {
        Collider2DManagement::Collider2DManagement()
            : _colliders(std::vector<Collider2D*>(100))         
        {
            ;
        }
        Collider2DManagement::~Collider2DManagement()
        {
            // HACK とりあえずnewで作って管理する
            // HACK 後でPoolに切り替えて管理する
            for(auto col : _colliders)
            {
                SAVE_DELETE(col);
            }

            _colliders.clear();
            _colliders.shrink_to_fit();
        }
        void Collider2DManagement::UpdateCollision()
        {
            if(_colliders.size() < 1)
                return;

            //HACK 二重ループ処理は重いので、いい方法を考える
            for(int i = 0; i < _colliders.size();++i)
            {
                if(!_colliders[i]->IsActive())
                    continue;

                for(int j = i + 1; j < _colliders.size(); ++j)
                {
                    if(!_colliders[j]->IsActive())
                        continue;

                    {
                        
                    }
                }
            }
            
        }
        void Collider2DManagement::RegisterCollider(Collider2D *collider)
        {
            _colliders.push_back(collider);
        }
    } // namespace MManagement

}// namespace MSelfCollision