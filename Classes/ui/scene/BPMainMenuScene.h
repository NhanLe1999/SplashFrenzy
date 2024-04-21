#pragma once

#include "cocos2d.h"
#include "BaseSingleton.h"
#include "cocos-ext.h"
#include "ensRippleNode.h"
class BPMainMenuScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init() override;
    void initHeader();
    void initMainButton();
    void runActionElementIn();
    void runActionElementOut(std::function<void()> callback);
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    bool isCheat = false;
    ens::CrippleSprite*    _background;
    std::map<Node*, std::pair<Vec2,Vec2>> _mapPosElement;
    CREATE_FUNC(BPMainMenuScene);
};


