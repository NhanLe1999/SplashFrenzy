#pragma once
#include "BaseSingleton.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "spine/SkeletonAnimation.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace spine;

#define KEY_SAVE_COINT  "key_save_coin"
#define KEY_SAVE_DIAMOND  "key_save_diamond"


#define HELPER_MANAGER BPHelperManager::GetInstance()

class BPHelperManager :public BaseSingleton<BPHelperManager>
{
public:
    enum class PhysicType {
        BOX,
        CIRCLE
    };
    template<typename T>
    void shuffle(std::vector<T>& v) {
        static std::random_device mj_rd;
        static std::mt19937 mj_g(mj_rd());
        std::shuffle(v.begin(), v.end(), mj_g);
    }

	void disableButton(cocos2d::Ref* sender);

	void showWaitingLayer();

    float lerp(float a, float b, float x, float y, float i);

    static void displayToast(const char* text, float duartionSeconds, Node* parent,Color4B color = Color4B::WHITE);
    
    static void displayToastTop(const char* text, float duartionSeconds, std::string pathBg,Color4B color = Color4B::WHITE);
    static void displayToastBottom(const char* text, float duartionSeconds, std::string pathBg,Color4B color = Color4B::WHITE);

    void attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node,cocos2d::Size nodeSize,std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO);

    void attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO,int physicMask = 0, PhysicType type = PhysicType::BOX,bool isDynamic = false);
    void createPhysicBody(cocos2d::Node* node, cocos2d::Size nodeSize, int physicMask, PhysicType type, bool isDynamic, float , bool isGravity = false);
    void attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO,int physicMask = 0, PhysicType type = PhysicType::BOX,bool isDynamic = false);
    void attachNodeToSpineAndSetPhysicWithoutRotation(Sprite* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO,int physicMask = 0, PhysicType type = PhysicType::BOX,bool isDynamic = false);
    void attachPhysicToNode(cocos2d::Node* node, int physicMask,Vec2 size, PhysicType type = PhysicType::BOX, bool isDynamic = false);
    float getSpineDuration(spine::SkeletonAnimation *spine,std::string animationName,float defaultDuration = 0.0);
    
    void addLockLayer(cocos2d::Node* node);

    std::string getCurrentDate();
    long long getCurrentTimeSeconds();
    void removeAllChildByTag(Node* parent, int tag);
    void runSacleEffect(Node* parent);

    Animate* getAnimate(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop);
    cocos2d::Animation* createAnimation(const char* prefixName, int start, int end, float delay, int loop = -1);
    Sprite* getAnimateSprite(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop);

    int GetTotalNumberCoin(bool isDiamond);


    void AddNumberCoin(int numberCoinAdd, bool isDiamond);
    void SaveNumberCoin(int numberCoin, bool isDiamond);


private:
    
};


