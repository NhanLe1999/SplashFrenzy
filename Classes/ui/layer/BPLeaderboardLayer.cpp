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
		SOUND_MANAGER->playClickEffect();
		auto layer = BPResetLayer::create();

		layer->setCallback([this](bool isSucess) {
			ResetData();
			});

		this->addChild(layer,1000);
		});

	Button* btHome = Button::create("res/BlackPink/button_main/bis_button_main_home.png");
	_background->addChild(btHome);
	btHome->setPosition(Vec2(10,_background->getContentSize().height - 20));
	btHome->addClickEventListener([=](Ref* sender) {
		SOUND_MANAGER->playClickEffect();
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

void BPLeaderboardLayer::ResetData()
{
	for (int i = 0; i < 5; i++)
	{
		if (auto music = utils::findChild<Label*>(this, "music_" + std::to_string(i)))
		{
			music->setString(std::to_string(0));
		}

		if (auto gem = utils::findChild<Label*>(this, "gem_" + std::to_string(i)))
		{
			gem->setString(std::to_string(0));
		}
	}
	UserDefault::getInstance()->setIntegerForKey("key_hight_music", 0);
	UserDefault::getInstance()->setIntegerForKey("key_hight_gem", 0);
}

void BPLeaderboardLayer::loadHighScore(){
	float posY = 515;
	float disY = 90;

	auto hightMusic = UserDefault::getInstance()->getIntegerForKey("key_hight_music", 0);
	auto hightGem = UserDefault::getInstance()->getIntegerForKey("key_hight_gem", 0);
	
	for (int i = 0; i < 4; i++) {

		auto mmusic = 0, gem = 0;
		if (i == 0)
		{
			mmusic = hightMusic;
			gem = hightGem;
		}

		auto music = Label::createWithTTF(std::to_string(mmusic), "fonts/Baloo2-Bold.ttf",40);
		music->setPosition(Vec2(485, posY));
		music->setName("music_" + std::to_string(i));
		_background->addChild(music);

		auto coin = Label::createWithTTF(std::to_string(gem), "fonts/Baloo2-Bold.ttf",40);
		coin->setPosition(Vec2(690, posY));
		_background->addChild(coin);
		posY -= disY;
		coin->setName("gem_" + std::to_string(i));

	}
	posY = 85;
	auto music = Label::createWithTTF(std::to_string(hightMusic), "fonts/Baloo2-Bold.ttf", 40);
	music->setPosition(Vec2(485, posY));
	music->setName("music_" + std::to_string(4));
	_background->addChild(music);

	auto coin = Label::createWithTTF(std::to_string(hightGem), "fonts/Baloo2-Bold.ttf", 40);
	coin->setPosition(Vec2(690, posY));
	coin->setName("gem_" + std::to_string(4));
	_background->addChild(coin);
}
