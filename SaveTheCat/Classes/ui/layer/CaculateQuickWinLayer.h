#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickWinLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickWinLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickWinLayer * createView();//1.

    void updateHighScore(std::pair<int, int> newScore);

    void OnShowTextLevel(int numLevel, int numStar, int typeState);
        
private:
    
    void didLoadFromCSB();
    
    void onSettingButtonClicked(cocos2d::Ref* sender);

    void onHomeButtonClicked(cocos2d::Ref* sender);

    void onNextButtonClicked(cocos2d::Ref* sender);

    void onRankButtonClicked(cocos2d::Ref* sender);
    void onClose(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.
    
private:

};

CREATE_READER(CaculateQuickWinLayer);

