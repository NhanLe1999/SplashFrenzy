#include "BPMainMenuScene.h"
#include "BPResetLayer.h"
#include "BPLeaderboardLayer.h"
#include "SFGameScene.h"
#include "BPSoundManager.h"
#include "BPGameManager.h"
#include "BPChooseWorld.h"
#include "BPdefinition.h"
#include "BPHelperManager.h"
#include "BPEndLayer.hpp"

#define BT_MARGIN  15
#define BT_WIDTH   286
#define BT_HEIGHT  100
#define SCALE  1
USING_NS_CC;

Scene* BPMainMenuScene::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = BPMainMenuScene::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}


bool BPMainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    SOUND_MANAGER->playMainMenuMusic();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize=Director::getInstance()->getWinSize();
    _background=new CrippleSprite();
    _background->autorelease();
    _background->init("res/BlackPink/background_home.png",8);
    _background->setPosition(Vec2(winSize.width/2,winSize.height/2));
    _background->scheduleUpdate();
    this->addChild(_background);
    float sacelY = visibleSize.height / _background->getContentSize().height;
    float sacelX = visibleSize.width / _background->getContentSize().width;
    float scale = std::max(sacelY, sacelX);
    _background->setScale(scale);
    Sprite* logo = Sprite::create("res/BlackPink/logo/logo.png");
    logo->setPosition(Vec2(_background->getContentSize().width / 2, 700));
    _background->addChild(logo,10);
    
    float k_currentScaleFactor = logo->getScale();

    logo->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(3.0f, 1.02f * k_currentScaleFactor, 0.9f * k_currentScaleFactor)), EaseBackOut::create(ScaleTo::create(3.0f, 1.0f * k_currentScaleFactor)))));
    initHeader();
    initMainButton();
    //auto btCheat = cocos2d::ui::Button::create("res/BlackPink/icon/sf_icon_cancel.png");
    //btCheat->setPosition(Vec2(visibleSize.width/2, visibleSize.height-30));
    //btCheat->setScale(0.8);
    //btCheat->addClickEventListener([=](Ref* sender)
    //    {
    //        SOUND_MANAGER->playClickEffect();
    //        UserDefault::getInstance()->setIntegerForKey("UserCoin", 50000);
    //        UserDefault::getInstance()->setIntegerForKey("UserRandom", 1000);
    //    });
    //this->addChild(btCheat);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BPMainMenuScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BPMainMenuScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BPMainMenuScene::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(BPMainMenuScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void BPMainMenuScene::initHeader(){
    

}

void BPMainMenuScene::initMainButton(){
    float posY = 300;
    float posX = _background->getContentSize().width / 2;
    auto btPlay = cocos2d::ui::Button::create("res/BlackPink/button_main/bis_button_main_play-44.png");
    btPlay->setPressedActionEnabled(true);
    btPlay->setPosition(Vec2(posX, posY));
    _background->addChild(btPlay,10);
    btPlay->setAnchorPoint(Vec2(0.5, 0));
    btPlay->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto scoreLayer = BPChooseWorld::create();
        scoreLayer->setName("SRChooseLvLayer");
        this->addChild(scoreLayer, UI_ZORDER);
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
        Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(scoreLayer, true);
    });
    Sprite* light = Sprite::create("res/BlackPink/bis_light.png");
    light->setPosition(btPlay->getPosition() + Vec2(0, 110));
    _background->addChild(light);
    auto btScore = cocos2d::ui::Button::create("res/BlackPink/button_main/bis_button_main_statistics.png");
    btScore->setPressedActionEnabled(true);
    btScore->setPosition(Vec2(posX-260, posY));
    btScore->setAnchorPoint(Vec2(0.5, 0));
    _background->addChild(btScore);
    btScore->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();
            auto scoreLayer = BPLeaderboardLayer::create();
            scoreLayer->setName("SRLeaderboardLayer");
            this->addChild(scoreLayer, UI_ZORDER);
            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
            Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(scoreLayer, true);
        });

    auto btGolink = cocos2d::ui::Button::create("res/BlackPink/button_main/bis_button_main_golink.png");
    btGolink->setPressedActionEnabled(true);
    btGolink->setPosition(Vec2(posX + 260, posY));
    btGolink->setAnchorPoint(Vec2(0.5, 0));
    _background->addChild(btGolink);
    btGolink->addClickEventListener([=](Ref* sender)
        {
            BPEndLayer* layer = BPEndLayer::create(false);
            this->addChild(layer, UI_ZORDER);
            SOUND_MANAGER->playClickEffect();
        });
    
    posY = 120;
    
    auto btSound = cocos2d::ui::Button::create(StringUtils::format("res/BlackPink/button_main/bis_button_main_sound_%s.png", !SOUND_MANAGER->isSoundEffectEnable() ? "off" : "on"));
    btSound->setPosition(Vec2(posX - 120, posY));
    _background->addChild(btSound); 
    btSound->setAnchorPoint(Vec2(0.5, 0));
    btSound->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();

            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);

            auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);

            UserDefault::getInstance()->setBoolForKey(IS_SOUND_KEY_ON, !isSoundOn);


            button->loadTextureNormal(StringUtils::format("res/BlackPink/button_main/bis_button_main_sound_%s.png", !SOUND_MANAGER->isSoundEffectEnable() ? "off" : "on"));
        });

    
    auto btMusic = cocos2d::ui::Button::create(StringUtils::format("res/BlackPink/button_main/bis_button_main_music_%s.png", !SOUND_MANAGER->isMusicEffectEnable() ? "off" : "on"));
    btMusic->setPosition(Vec2(posX + 130, posY));
    _background->addChild(btMusic);
    btMusic->setAnchorPoint(Vec2(0.5, 0));
    btMusic->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();

            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);

            auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);

            UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, !isSoundOn);

            if (SOUND_MANAGER->isMusicEffectEnable()) {

                SOUND_MANAGER->resumeAllBackgroundMusics();
            }
            else
            {
                SOUND_MANAGER->pauseAllBackgroundMusics();
            }


            button->loadTextureNormal(StringUtils::format("res/BlackPink/button_main/bis_button_main_music_%s.png", !SOUND_MANAGER->isMusicEffectEnable() ? "off" : "on"));

        });
}
void BPMainMenuScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    Scene::draw(renderer, transform, flags);
}

void BPMainMenuScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event){
    Touch* touch;
    for(auto  it = touches.begin(); it != touches.end(); it++)
    {
        touch = (Touch*)(*it);
        if(!touch)
            break;
        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);
        _background->doTouch(location, 512, 12);
    }
}
void BPMainMenuScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event){
    Touch* touch;
    for(auto  it = touches.begin(); it != touches.end(); it++)
    {
        touch = (Touch*)(*it);
        
        if(!touch)
            break;
        
        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);
        _background->doTouch(location, 512, 12);
    }
}
void BPMainMenuScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event){

}
