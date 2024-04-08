#pragma once

#include "CaculateQuickCocostudioMacro.h"
#include "cocos2d.h"
#include "CaculateQuickCCSpriteRipper.h"

class CaculateQuickMainMenuScene : public cocos2d::Scene, public cocostudio::WidgetCallBackHandlerProtocol
{
public:

    CREATE_FUNC(CaculateQuickMainMenuScene);

    static cocos2d::Scene* createScene();

    static CaculateQuickMainMenuScene* createView();//1.

    static void onMusic(cocos2d::Ref* sender);

    static void onSound(cocos2d::Ref* sender);

    virtual bool init() override;

private:
    
    void didLoadFromCSB();//2.
    
    void onPlayButtonClicked(cocos2d::Ref* sender);


    void onLeaderBoardButtonClicked(cocos2d::Ref* sender);

    void OnLoadingSucess();

    void onShopButtonClicked(cocos2d::Ref* sender);

    void onTutorialButtonClicked(cocos2d::Ref* sender);

    void onSettingButtonClicked(cocos2d::Ref * sender);

    void OnContinueGame(cocos2d::Ref* sender);

    void OnPlayGame(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string& callback_name) override;

    ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string& callback_name) override;

    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type);

private:
    
    CrippleSprite* crippleSprite;

    std::function<void()> _callback;

};

CREATE_READER(CaculateQuickMainMenuScene);

