#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickGameOverLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickGameOverLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickGameOverLayer * createView();//1.

    void updateHighScore(std::pair<int, int> newScore);

    void OnShowTextLevel(int numLevel);
    void OnShowNumStar(int numstar);
    void OnEnableBtnRevival(bool isEnablae);
        
private:
    
    void didLoadFromCSB();
    
    void onSettingButtonClicked(cocos2d::Ref* sender);

    void onHomeButtonClicked(cocos2d::Ref* sender);

    void onReplayButtonClicked(cocos2d::Ref* sender);

    void onRankButtonClicked(cocos2d::Ref* sender);
    void onClose(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.
    
private:

};

CREATE_READER(CaculateQuickGameOverLayer);

