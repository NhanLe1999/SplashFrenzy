//
//  FTSEndLayer.hpp
//  HelloWord-mobile
//
//  Created by ThangNguyen on 21/11/2023.
//

#include "cocos2d.h"

class BPEndLayer : public cocos2d::Layer
{
public:

//    CREATE_FUNC(FTSEndLayer);
    static BPEndLayer* create(bool isOver)
    {
        BPEndLayer *pRet = new(std::nothrow) BPEndLayer();
        if (pRet && pRet->init(isOver))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

public:
    void setCallback(std::function<void()> callback){
        _callback = callback;
    }
     virtual bool init(bool isOver);
    void onEnter() override;
protected:
    void initButton();
    void initLabel();
private:
    bool _isOver = true;
    int _lv = 1;
    std::function<void()> _callback;
    cocos2d::Sprite* _background;
};