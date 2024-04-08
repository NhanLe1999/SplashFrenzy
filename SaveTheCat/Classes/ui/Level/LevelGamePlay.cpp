#include "LevelGamePlay.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickSettingLayer.h"
#include "CaculateQuickLeaderboardLayer.h"
#include "CaculateQuickAnimationManager.h"
#include "CaculateQuickPhysicsShapeCache.h"
#include "CaculateQuickGameScene.h"


#define NUM 100
USING_NS_CC;

INITIALIZE_READER(LevelGamePlay);

std::once_flag level_flag;

Scene *LevelGamePlay::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = LevelGamePlay::createView(1);
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

LevelGamePlay *LevelGamePlay::createView(int id)
{
    std::call_once(level_flag, []
                   { REGISTER_CSB_READER(LevelGamePlay); });


    std::string path = cocos2d::StringUtils::format("csb/ui/Level/LevelGame_%d.csb", 0);

    auto view = reinterpret_cast<LevelGamePlay *>(CSLoader::createNodeWithVisibleSize(path.c_str()));

    if (view)
    {
        view->didLoadFromCSB();
        return view;
    }

    CC_SAFE_DELETE(view);

    return nullptr;
}

void LevelGamePlay::didLoadFromCSB()
{
   
    if (auto slider = utils::findChild<Slider*>(this, "Slider_1"))
    {
        slider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                float kk = slider->getPercent();
                CCLOG("nenenne: %f", kk); 
                break;
            }
            case cocos2d::ui::Widget::TouchEventType::MOVED:
            {
                float kk = slider->getPercent();
                CCLOG("nenenne: %f", kk);
                break;
            }
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                float kk = slider->getPercent();
                CCLOG("nenenne: %f", kk);
                break;
            }
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
            {
                float kk = slider->getPercent();
                CCLOG("nenenne: %f", kk);
                break;
            }
            default:
                break;
            }
            });

    }

    
}

void LevelGamePlay::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void LevelGamePlay::SetDataForResult(std::vector<int> listResult)
{
   
}

void LevelGamePlay::SetDataForGame()
{
   
}

void LevelGamePlay::SetRotationForParent(Node* n)
{
   
}

void LevelGamePlay::CheckComlete(bool ischeckEndGamne)
{
}

void LevelGamePlay::OnGameWin()
{
}

void LevelGamePlay::RunActionWin(Node* node, std::function<void()> callback, float time)
{
   
}

int LevelGamePlay::GetResult(int a, int b, std::string allow)
{
    return 0;
}

void LevelGamePlay::SetDataLevelConfig(LevelConfig lv)
{
    _currentLevelConfig = lv;
}

InfoItem LevelGamePlay::GetDataForGame(int numAllow, int min, int max, std::vector<std::string> listAllow)
{
    if (min == 0 || max == 0)
    {
        int kk = 0;
    }

    InfoItem info = InfoItem();
    if (numAllow == 1)
    {
        info.a = cocos2d::random(min, max);
        info.allow1 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.b = cocos2d::random(min, max);

        if (info.a == 0 || info.b == 0)
        {
            int kk = 0;
        }

        return info;
    }

    if (numAllow == 2)
    {
        info.a = cocos2d::random(min, max);
        info.allow1 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.b = cocos2d::random(min, max);
        info.allow2 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.c = cocos2d::random(min, max);

        if (info.a == 0 || info.b == 0 || info.c == 0)
        {
            int kk = 0;
        }

        return info;
    }

    if (numAllow == 3)
    {
        info.a = cocos2d::random(min, max);
        info.allow1 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.b = cocos2d::random(min, max);
        info.allow2 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.c = cocos2d::random(min, max);
        info.allow3 = listAllow[cocos2d::random(min, max) % listAllow.size()];
        info.d = cocos2d::random(min, max);

        if (info.a == 0 || info.b == 0 || info.c == 0 || info.d == 0)
        {
            int kk = 0;
        }

        return info;
    }
    return info;
}


cocos2d::ui::Widget::ccWidgetClickCallback LevelGamePlay::onLocateClickCallback(const std::string& callBackName)
{
    return nullptr;
}

ui::Widget::ccWidgetTouchCallback LevelGamePlay::onLocateTouchCallback(const std::string& callback_name) {

    if (callback_name == "onTouch")
    {
        return CC_CALLBACK_2(LevelGamePlay::onTouch, this);
    }

    return nullptr;
}

void LevelGamePlay::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type) {

    auto obj = static_cast<ui::Slider*>(sender);

    bool isSucess = false;

    obj->getSlidBallDisabledRenderer()->setPosition(Vec2(40, 0));
    obj->setZoomScale(0.0f);
    obj->getSizePercent();

    float kk = obj->getPercent();
    CCLOG("nenenne: %f", kk);


    switch (event_type)
    {
    case ui::Widget::TouchEventType::BEGAN:
    {
       // obj->setScale(1.0f);
        SOUND_MANAGER->PlaySoundBeginDrag();
        

        break;
    }

    case ui::Widget::TouchEventType::MOVED:
    {
        CCPoint location = obj->getTouchMovePosition();

        auto point = this->getTouchMovePosition();
        obj->setPosition(obj->getParent()->convertToNodeSpace(location));
        float kk = obj->getPercent();
        CCLOG("nenenne: %f", kk);

        break;
    }
    case ui::Widget::TouchEventType::ENDED:
        SOUND_MANAGER->PlaySoundEndDrag();
        break;

    case ui::Widget::TouchEventType::CANCELED:
    {
        auto ccc = 0;
        break;
    }
    default:
        break;
    }
}