#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickLeaderboardLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickLeaderboardLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickLeaderboardLayer * createView();
    

    void setButtonsVisible(bool value);

    void updateHighScore(int type, float time, std::pair<int, int> newScore);

    void setCloseButtonVisible(bool value);

private:
    
    void didLoadFromCSB();
    
    void onCloseButtonClicked(cocos2d::Ref* sender);

    void onHomeButtonClicked(cocos2d::Ref* sender);

    void onReplayButtonClicked(cocos2d::Ref* sender);

    void OnlickBtnLevel(cocos2d::Ref* sender);

    void OnlickBtnModeGame(cocos2d::Ref* sender);

    void EnableButton(Button* button, bool isEnable);

    void ShowLeaderBoadById(int id);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;
    
private:
    std::vector<Node*> _listNode = {};
    Button* _btnCurrent = nullptr;

};

CREATE_READER(CaculateQuickLeaderboardLayer);

