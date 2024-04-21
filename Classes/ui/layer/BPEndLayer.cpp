//
//  FTSEndLayer.cpp
//  HelloWord-mobile
//
//  Created by ThangNguyen on 21/11/2023.
//

#include "BPEndLayer.hpp"
#include "cocos2d.h"
#include "BPAnimationManager.h"
#include "BPLeaderboardLayer.h"
#include "SFGameScene.h"
#include "BPMainMenuScene.h"
#include "BPSoundManager.h"
#include "BPGameManager.h"

bool BPEndLayer::init(bool isOver){
    if (!Layer::init())
    {
        return false;
    }
    SOUND_MANAGER->playLoseEffect();

    _lv = BPGameManager::GetInstance()->_currentLv;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 255 * 0.85f), visibleSize.width, visibleSize.height);
    this->addChild(layer);
    std::string path ="res/BlackPink/popup/popup_pause/bis_popup_pause.png";
    if (isOver) {
        path = "res/BlackPink/popup/game_over/bis_popup_game_over.png";
    }
    _isOver = isOver;
    _background = Sprite::create(path);
    _background->setPosition((Vec2)visibleSize / 2 + origin + Vec2(0,-45));
    this->addChild(_background,1);
    
    initLabel();
    initButton();
    return true;
}

void BPEndLayer::initLabel() {
    Sprite* bgMusic = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_1.png");
    _background->addChild(bgMusic);
    bgMusic->setPosition(Vec2(_background->getContentSize().width / 2, 335));
    Sprite* headMusic = Sprite::create("res/BlackPink/ui/bis_ui_icon_notes_world_1.png");
    bgMusic->addChild(headMusic);
    headMusic->setAnchorPoint(Vec2(0, 0.5));
    headMusic->setPosition(Vec2(0, bgMusic->getContentSize().height / 2));
    int coin = UserDefault::getInstance()->getIntegerForKey("UserMusic", 0);
    auto _numberMusic = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
    _numberMusic->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));

    bgMusic->addChild(_numberMusic);

    Sprite* bgCoin = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_1.png");
    _background->addChild(bgCoin);

    bgCoin->setPosition(Vec2(_background->getContentSize().width / 2, 335 - 105));

    Sprite* headCoin = Sprite::create("res/BlackPink/ui/bis_ui_icon_gem_world_1.png");
    bgCoin->addChild(headCoin);
    headCoin->setAnchorPoint(Vec2(0, 0.5));
    headCoin->setPosition(Vec2(0, bgCoin->getContentSize().height / 2));
    coin = UserDefault::getInstance()->getIntegerForKey("UserCoin", 0);
    auto _numberCoin = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
    _numberCoin->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));
    bgCoin->addChild(_numberCoin);
}
void BPEndLayer::initButton(){
    float posY = 90;
    float posX = _background->getContentSize().width/2;

    Button* btHome = Button::create("res/BlackPink/button_world/button_world_1/bis_button_home_world_1.png");
    btHome->setPosition(Vec2(posX -110, posY));
    _background->addChild(btHome);
    btHome->addClickEventListener([=](Ref* sender){
        SOUND_MANAGER->playClickEffect();
        int score = BPGameManager::GetInstance()->_currentSocre;
        BPGameManager::GetInstance()->addScore(score, "User", _lv);
        auto scene = BPMainMenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionSlideInL::create(0.6, scene));
        this->removeFromParent();;
        
    });
    std::string path = "res/BlackPink/button_world/button_world_1/bis_button_play_world_1.png";
    if (_isOver) {
        path = "res/BlackPink/button_world/button_world_1/bis_button_ok_world_1.png";
    }
    Button* btPlay = Button::create(path);
    btPlay->setPosition(Vec2(posX, posY));
    btPlay->setScale(95 / btPlay->getContentSize().width);
    _background->addChild(btPlay);
    btPlay->addClickEventListener([=](Ref* sender){
        if (_isOver) {
            auto scene = SFGameScene::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        else {
            if(_callback)_callback();
        }
        this->removeFromParent();
    });
    
    Button* btGolink = Button::create("res/BlackPink/button_world/button_world_1/bis_button_golink_world_1.png");
    btGolink->setPosition(Vec2(posX + 110, posY));
    _background->addChild(btGolink);
    btGolink->setScale(95 / btGolink->getContentSize().width);
    btGolink->addClickEventListener([=](Ref* sender){
        
        SOUND_MANAGER->playClickEffect();

    });
}
void BPEndLayer::onEnter(){
    _background->setScale(0);
    _background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 1)));
    cocos2d::Layer::onEnter();
}
