#pragma once

#include "CaculateQuickCocostudioMacro.h"

class CaculateQuickShopLayer : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:

    CREATE_FUNC(CaculateQuickShopLayer);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickShopLayer * createView();//1.
        
private:
    
    void didLoadFromCSB();

    void onClose(cocos2d::Ref* sender);
    void onBuyFixer(cocos2d::Ref* sender);
    void onBuySheild(cocos2d::Ref* sender);
    void onBuyRuler(cocos2d::Ref* sender);
    void onAddButtonClicked(cocos2d::Ref* sender);

    void OnupdateNumSkill();

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.
    
private:
    Text* _txtRuler = nullptr;
    Text* _txtSheild = nullptr;
    Text* _txtFixer = nullptr;

    Button* _BtnSkillRuler = nullptr;
    Button* _BtnSkillSheild = nullptr;
    Button* _BtnSkillFixer = nullptr;

};

CREATE_READER(CaculateQuickShopLayer);

