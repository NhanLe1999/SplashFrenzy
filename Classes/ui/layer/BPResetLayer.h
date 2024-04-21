#pragma once

#include "cocos2d.h"

class BPResetLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(BPResetLayer);

    static cocos2d::Scene* createScene();

    virtual bool init() override;
    void onEnter() override;
    void setCallback(std::function<void(bool)> callback) {
        _callback = callback;
    }
    std::function<void(bool)> _callback;
};


