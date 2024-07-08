#pragma once

#include <vector>

#include "../Utilities/MDesignPattern/singleton.h"


namespace MSelfCollision
{
    // 前方宣言
    class Collider2D;

    namespace MManagement
    {

        class Collider2DManagement : public MDesignPattern::MSingleton::Singleton<Collider2DManagement>
        {
        private:
            friend class Singleton<Collider2DManagement>;

        private:
            Collider2DManagement();

        public:
            ~Collider2DManagement();

        public:
            void UpdateCollision();

        public:
            void RegisterCollider(Collider2D* collider);

        private:
            // 全てのコライダーを管理する動的配列
            std::vector<Collider2D*> _colliders;
        };

    }// namespace MManagement

}// namespace MSelfCollision 