#pragma once

#include <vector>

#include "../Utilities/MDesignPattern/singleton.h"

namespace MSelfCollision
{
    namespace MManagement
    {
        // 前方宣言
        class Collider2D;

        class Collider2DManagement : public MDesignPattern::MSingleton::Singleton<Collider2DManagement>
        {
        private:
            friend class Singleton<Collider2DManagement>;

        private:
            Collider2DManagement();

        public:
            ~Collider2DManagement();

        public:
            void Update();

        private:
            // 全てのコライダーを管理する動的配列
            std::vector<Collider2D*> _colliders;

        };

    }// namespace MManagement

}// namespace MSelfCollision 