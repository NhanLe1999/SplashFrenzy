#pragma once

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
class BPLeaderboardLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(BPLeaderboardLayer);

    static cocos2d::Scene* createScene();
    virtual bool init() override;
    static void UpdateUserGem(int gem);
    
    static void IncreaseUserGem(int gem);

    static int GetUserGem() {
       return cocos2d::UserDefault::getInstance()->getIntegerForKey("user_gem", 0);
    }

    static void updateMission(int killEnemies, int collectedGem);

    static void updateHighScore(std::tuple<int, int, int, int,std::string> newScore);
    void onEnter() override;
    void onExit() override;
    void initButton();
    void loadHighScore();

    void ResetData();

private:
    cocos2d::ui::Button* _btNext;
    cocos2d::ui::Button* _btBack;
    cocos2d::Sprite* _background;
    int _indexLayer;
};


