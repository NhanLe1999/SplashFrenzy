#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickGuideLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickGuideLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickGuideLayer * createView();
        
private:
    
    void didLoadFromCSB();
    
    void onCloseButtonClicked(cocos2d::Ref* sender);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;
    
private:

    int _numCurrentPage = 1;
    cocos2d::Size                   _screenSize;
    cocos2d::Vec2                   _origin;

    bool _isOnBack = true;
    bool _isOnNext = true;
    bool _isRun = true;

    Button* _buttonNext = nullptr;
    Button* _buttonBack = nullptr;

    cocos2d::Vec2 pointMax = Vec2(0, 0);

};

CREATE_READER(CaculateQuickGuideLayer);

