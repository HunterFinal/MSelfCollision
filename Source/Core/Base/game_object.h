// ---------------------------------------------------------------------------------------------------------------------------------------
// File name:           game_object.h
// Version:             alpha_1.0
// Description:         game object class
// Namespace:           MSelfCollision
// Note:                ...
//
// Update:              2024/06/18  Create
//
// Author:              MAI ZHICONG
// ---------------------------------------------------------------------------------------------------------------------------------------


#pragma once

#include <string>

namespace MSelfCollision
{
    // 前方宣言
    class Transform2D;

    class MGameObject
    {
        // Getter
        public:
            std::string GetName() const {return _name;}
            std::string GetTag() const {return _tag;}
            int GetID() const {return _id;}
            Transform2D* GetTransform() const {return _pTransform;}

        public:
            bool CompareTag(const char* tag);

        // コンストラクタ・デストラクタ
        public:
            MGameObject();
            ~MGameObject();

        // コピー・ムーブ
        public:
            // コピー
            MGameObject(const MGameObject& other);
            MGameObject& operator=(const MGameObject& other);

            // ムーブ
            MGameObject(MGameObject&& other) noexcept;
            MGameObject& operator=(MGameObject&& other) noexcept;

        // プロパティ
        private:
            std::string _name;
            std::string _tag;
            int _id;
            Transform2D* _pTransform;

    };// class MGameObject

}// namespace MSelfCollision 