#pragma once

#include "CaculateQuickCocostudioMacro.h"

enum TypeMove
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    DEFAULT
};


class MySlider :public cocos2d::ui::Layout, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
    CREATE_FUNC(MySlider);
    static MySlider* createView();//1.
    void SetSizeForSlideBar(Size mapSize);


public:

    ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string& callback_name) override;
    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type);

private:

    void didLoadFromCSB();//2.
    void OnSetPersentSlider(Slider* sl, float distance);

private:
    Slider* _sliderRight = nullptr;
    Slider* _sliderLeft = nullptr;
    Slider* _sliderDown = nullptr;
    Slider* _sliderUp = nullptr;

    Slider* _sliderCurret = 0;

    float DisRight = 0;
    float DisLeft = 0;
    float DisDown = 0;
    float DisUp = 0;


    Vec2 _startTouchPos;
    TypeMove _currentTypeMove;
};

CREATE_READER(MySlider);
