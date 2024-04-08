#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickPauseLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickPauseLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickPauseLayer * createView();//1.
        
private:
    
    void didLoadFromCSB();
    
    void onMusicButtonClicked(cocos2d::Ref* sender);

    void onSettingButtonClicked(cocos2d::Ref* sender);

    void onSoundButtonClicked(cocos2d::Ref* sender);
    
    void onHomeButtonClicked(cocos2d::Ref* sender);

    void onReplayButtonClicked(cocos2d::Ref* sender);

    void onPlayButtonClicked(cocos2d::Ref* sender);
    void onClose(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.
    
private:

};

CREATE_READER(CaculateQuickPauseLayer);

