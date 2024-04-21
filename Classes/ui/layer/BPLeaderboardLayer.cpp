#include "BPLeaderboardLayer.h"
#include "BPHelperManager.h"
#include "BPSoundManager.h"
#include "BPGameManager.h"
#include "BPResetLayer.h"
#include "BPMainMenuScene.h"
USING_NS_CC;

Scene* BPLeaderboardLayer::createScene()
{
	auto scene = Scene::create();

	if (scene)
	{
		auto view = BPLeaderboardLayer::create();
		scene->addChild(view);
	}
	else
	{
		CC_SAFE_DELETE(scene);
	}

	return scene;
}

bool BPLeaderboardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_indexLayer = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BPHelperManager::GetInstance()->addLockLayer(this);
	auto a  = BPGameManager::GetInstance()->getListDataScore();
	_background = Sprite::create("res/BlackPink/popup/popup_statistics/bis_popup_statistics.png");
	_background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+ 40));
	this->addChild(_background,1, "background");
	loadHighScore();

	Button* btReset = Button::create("res/BlackPink/button_main/bis_button_main_reset.png");
	_background->addChild(btReset);
	btReset->setPosition(Vec2(_background->getContentSize().width / 2, -60));
	btReset->addClickEventListener([=](Ref* sender) {
		auto layer = BPResetLayer::create();
		this->addChild(layer,1000);
		});

	Button* btHome = Button::create("res/BlackPink/button_main/bis_button_main_home.png");
	_background->addChild(btHome);
	btHome->setPosition(Vec2(10,_background->getContentSize().height - 20));
	btHome->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
		((BPMainMenuScene*)this->getParent())->runActionElementIn();
		this->removeFromParent();
		});

	return true;
}

void BPLeaderboardLayer::onEnter(){
    
	auto a = this->getChildByName("background");
	a->setScale(0);
    a->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.75)));
    cocos2d::Layer::onEnter();
}
void BPLeaderboardLayer::onExit(){
    cocos2d::Layer::onExit();
}
void BPLeaderboardLayer::loadHighScore(){
	float posY = 515;
	float disY = 90;
	
	for (int i = 0; i < 4; i++) {
		auto music = Label::createWithTTF("1000", "fonts/Baloo2-Bold.ttf",40);
		music->setPosition(Vec2(485, posY));
		_background->addChild(music);

		auto coin = Label::createWithTTF("1000", "fonts/Baloo2-Bold.ttf",40);
		coin->setPosition(Vec2(690, posY));
		_background->addChild(coin);
		posY -= disY;
	}
	posY = 85;
	auto music = Label::createWithTTF("1000", "fonts/Baloo2-Bold.ttf", 40);
	music->setPosition(Vec2(485, posY));
	_background->addChild(music);

	auto coin = Label::createWithTTF("1000", "fonts/Baloo2-Bold.ttf", 40);
	coin->setPosition(Vec2(690, posY));
	_background->addChild(coin);
}
