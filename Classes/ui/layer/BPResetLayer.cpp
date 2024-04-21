#include "BPResetLayer.h"
#include "BPHelperManager.h"
#include "BPMainMenuScene.h"
#include "BPSoundManager.h"

USING_NS_CC;

Scene* BPResetLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = BPResetLayer::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

bool BPResetLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 255*0.85f), visibleSize.width, visibleSize.height);
    this->addChild(layer);

  
    Sprite* background = Sprite::create("res/BlackPink/popup/popup_statistics/bis_popup_reset.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,1, "background");
    float posX = background->getContentSize().width/2;
    float posY = -65;
    

    Button *btCance = Button::create("res/BlackPink/button_main/bis_button_main_cancel.png");
    background->addChild(btCance);
    btCance->setPosition(Vec2(posX + 110, posY));
    btCance->addClickEventListener([=](Ref *sender) {
        this->removeFromParent();
        });

    Button *btOK = Button::create("res/BlackPink/button_main/bis_button_main_reset.png");
    background->addChild(btOK);
    btOK->setPosition(Vec2(posX - 110 , posY));
    btOK->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();
        });
    return true;
}

void BPResetLayer::onEnter(){
    auto _background = this->getChildByName("background");
    _background->setScale(0);
    _background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.76)));
    cocos2d::Layer::onEnter();
}
