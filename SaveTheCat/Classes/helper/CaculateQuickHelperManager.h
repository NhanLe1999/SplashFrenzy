#pragma once
#include "CaculateQuickBaseSingleton.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "spine/SkeletonAnimation.h"
#include "CaculateQuickCocostudioMacro.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace spine;

#define HELPER_MANAGER CaculateQuickHelperManager::GetInstance()

#define KEY_SAVE_UNLOCK_ITEM  "key_save_unlock_item"
#define KEY_SAVE_CURRENT_BOAT  "key_save_current_boat"
#define KEY_SAVE_COINT  "key_save_coin"

class CaculateQuickHelperManager :public BaseSingleton<CaculateQuickHelperManager>
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

    void showCaculateQuickWaitingLayer();

    float lerp(float a, float b, float x, float y, float i);

    static void displayToast(const char* text, float duartionSeconds, Node* parent, Color4B color = Color4B::WHITE);

    void attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO);

    void attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO, int physicMask = 0, PhysicType type = PhysicType::BOX, bool isDynamic = false);

    void attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO, int physicMask = 0, PhysicType type = PhysicType::BOX, bool isDynamic = false);

    Sprite* setPhysicsBodyOfAnimByCreateSprite(SkeletonAnimation* animation, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion = cocos2d::Vec2(0, 0));

    Sprite* setPhysicsBodyByCreateSprite(Node* node, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion = cocos2d::Vec2(0, 0));

    Sprite* setPhysicsBody(Sprite* node, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion = cocos2d::Vec2(0, 0), bool isEnableDynamic = false, int categirBitmask = 0x001);

    void setPhysicsPolygonByCreateSprite(Node* node, Size size, int collisionBitmask, std::string name, Vec2* points, int count, cocos2d::Vec2 postion = cocos2d::Vec2(0, 0));

    void setPhysicsPolygon(Node* node, Size size, int collisionBitmask, std::string name, Vec2* points, int count, cocos2d::Vec2 postion = cocos2d::Vec2(0, 0));

    float getSpineDuration(spine::SkeletonAnimation* spine, std::string animationName, float defaultDuration = 0.0);

    Sprite* getAnimateSprite(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop);

    Animate* getAnimate(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop);

    Vec2* getPointCollider(std::vector<Vec2> vec);

    void addLockLayer(cocos2d::Node* node);

    std::string getCurrentDate();

    float getTimeDelayOfAimation(float delay, SkeletonAnimation* animation, std::string nameAction);
    std::vector<std::string> split(const std::string& s, char delim);

    template<typename Out>
    void split(const std::string& s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    long long getTimeStampNow();
    std::string timestampToDateString(long long timestamp);
    std::string getTimeToString(int time);

    Vec2 getPoint(Size sizeCurrent, Vec2 value);
    std::vector<Vec2> resetPointFishCollider(std::vector<Vec2>& listValue, Vec2 pointAddd);

    int GetTotalNumberCoin();
    void AddNumberCoin(int numberCoinAdd);
    void SaveNumberCoin(int numberCoin);

    template <typename T>
    void SuffleVector(std::vector<T>& vector)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(vector.begin(), vector.end(), generator);
    }

    void RunAnimNode(Node* txt);

    Vec2 getThirdPointByX(Point first, Vec2 second, double x);
    Vec2 getThirdPointByY(Point first, Vec2 second, double y);


private:

};


