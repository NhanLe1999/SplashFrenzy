#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickSettingLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickSettingLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickSettingLayer * createView();//1.
        
private:
    
    void didLoadFromCSB();

    void onClose(cocos2d::Ref* sender);
    
    void onMusicButtonClicked(cocos2d::Ref* sender);

    void onSoundButtonClicked(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.
    
private:

};

CREATE_READER(CaculateQuickSettingLayer);

