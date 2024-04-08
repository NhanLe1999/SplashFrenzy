#pragma once

#include "cocos2d.h"

class CaculateQuickLevelLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CaculateQuickLevelLayer);
    static cocos2d::Scene *createScene();
    static CaculateQuickLevelLayer *createView();

    virtual bool init() override;
};
