#include "BPChooseCharacter.h"
#include "cocos2d.h"
#include "BPHelperManager.h"
#include "BPSoundManager.h"
#include "BPGameManager.h"
#include "SFGameScene.h"
#include "BPMainMenuScene.h"
#define NUMBER_ITEM  7
#define NUMBER_LAYER 10
bool BPChooseCharacter::init() {
	if (!Layer::init())
	{
		return false;
	}
	initData();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BPHelperManager::GetInstance()->addLockLayer(this);

	_background = Sprite::create("res/BlackPink/popup/popup_character/bis_popup_character.png");
	this->addChild(_background);
	_background->setPosition((Vec2)visibleSize / 2 + origin + Vec2(0, 20));

	Button* btHome = Button::create("res/BlackPink/button_main/bis_button_main_home.png");
	_background->addChild(btHome);
	btHome->setPosition(Vec2(10, _background->getContentSize().height - 20));
	btHome->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
		((BPMainMenuScene*)this->getParent())->runActionElementIn();
		this->removeFromParent();
		});

	Button* btPlay = Button::create("res/BlackPink/button_main/bis_button_main_play-54.png");
	_background->addChild(btPlay);
	btPlay->setPosition(Vec2(_background->getContentSize().width + 20, _background->getContentSize().height - 20));
	btPlay->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
		Director::getInstance()->replaceScene(TransitionFade::create(0.3f, SFGameScene::createScene()));
		this->removeFromParent();

		});
	initButtonLv();
	initLabel();
	loadStatusItem();
	return true; 
}
void BPChooseCharacter::initData() {
	_mapItemCoin[2] = 1000;
	_mapItemCoin[3] = 1000;
	_mapItemCoin[4] = 2000;
	_mapItemCoin[5] = 3000;
	_mapItemCoin[6] = 3000;
	_mapItemCoin[7] = 3000;
	_mapItemCoin[8] = 4000;
	_mapItemCoin[9] = 4000;
	_mapItemCoin[10] = 15000;

	UserDefault::getInstance()->setIntegerForKey("CharacterStatus1", 1);
	UserDefault::getInstance()->setIntegerForKey("CharacterActive", 1);
}
void BPChooseCharacter::initButtonLv() {
	std::string pathSelect = "res/BlackPink/popup/popup_character/bis_popup_character_selected_";
	std::string pathLock = "res/BlackPink/popup/popup_character/bis_popup_character_lock_5";
	std::string pathDisable = "res/BlackPink/popup/popup_character/bis_popup_character_non_";
	auto bgSize = _background->getContentSize();
	float posX = 28;
	float posY = 250;
	for (int i = 1; i <= 10; i++) {
		std::string path = pathDisable + std::to_string(i) + ".png";
		if (i == 10) {
			path = "res/BlackPink/popup/popup_character/bis_popup_character_commingsoon.png";
		}
		Button* bt = Button::create(path);
		_background->addChild(bt);
		bt->setAnchorPoint(Vec2(0, 0));
		bt->setPosition(Vec2(posX,posY));
		bt->setTag(i);
		bt->addClickEventListener(CC_CALLBACK_1(BPChooseCharacter::clickButtonLvEvent,this));
		_listItem.push_back(bt);
		posX += 180 +10;
		if (i == 5) {
			posX = 28;
			posY -= 210;
		}
	}

}
void BPChooseCharacter::initLabel() {
	Sprite* bgMusic = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_main.png");
	_background->addChild(bgMusic);
	bgMusic->setAnchorPoint(Vec2(0, 1));
	bgMusic->setPosition(Vec2(0, -10));
	Sprite* headMusic = Sprite::create("res/BlackPink/ui/bis_ui_icon_notes_world_main.png");
	bgMusic->addChild(headMusic);
	headMusic->setAnchorPoint(Vec2(0, 0.5));
	headMusic->setPosition(Vec2(0, bgMusic->getContentSize().height / 2));
	int coin = UserDefault::getInstance()->getIntegerForKey("UserMusic", 0);
	_numberMusic = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
	_numberMusic->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));
	
	bgMusic->addChild(_numberMusic);

	Sprite* bgCoin = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_main.png");
	_background->addChild(bgCoin);
	bgCoin->setAnchorPoint(Vec2(1, 1));
	bgCoin->setPosition(Vec2(_background->getContentSize().width, -10));

	Sprite* headCoin = Sprite::create("res/BlackPink/ui/bis_ui_icon_gem_world_lock.png");
	bgCoin->addChild(headCoin);
	headCoin->setAnchorPoint(Vec2(0, 0.5));
	headCoin->setPosition(Vec2(0, bgCoin->getContentSize().height / 2));
	coin = UserDefault::getInstance()->getIntegerForKey("UserCoin", 0);
	_numberCoin = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
	_numberCoin->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));
	bgCoin->addChild(_numberCoin);
}
void BPChooseCharacter::clickButtonLvEvent(Ref* sender) {
	SOUND_MANAGER->playClickEffect();
	auto bt = (Button*)sender;
	int type = bt->getTag();
	if (type == 10) return;
	std::string data = "CharacterStatus" + std::to_string(type);
	int status = UserDefault::getInstance()->getIntegerForKey(data.c_str(), -1);
	if (status != -1) {
		UserDefault::getInstance()->setIntegerForKey("CharacterActive", type);
	}
	else {
		int coin = UserDefault::getInstance()->getIntegerForKey("UserMusic", 0);
		if (_mapItemCoin[type] > coin) {
			return;
		}
		UserDefault::getInstance()->setIntegerForKey("UserMusic", coin - _mapItemCoin[type]);
		UserDefault::getInstance()->setIntegerForKey(data.c_str(), 1);
		UserDefault::getInstance()->setIntegerForKey("CharacterActive", type);
		_numberMusic->setString(std::to_string(coin - _mapItemCoin[type]));
	}
	loadStatusItem();
	
}
void BPChooseCharacter::loadStatusItem() {
	std::string pathSelect = "res/BlackPink/popup/popup_character/bis_popup_character_selected_";
	std::string pathLock = "res/BlackPink/popup/popup_character/bis_popup_character_lock_";
	std::string pathDisable = "res/BlackPink/popup/popup_character/bis_popup_character_non_";

	for (auto item : _listItem) {
		std::string name;
		int type = item->getTag();
		if (type == 10) continue;
		name = std::to_string(type) + ".png";
		std::string data = "CharacterStatus" + std::to_string(type);
		int status = UserDefault::getInstance()->getIntegerForKey(data.c_str(), -1);
		if (status != -1) {
			item->loadTextureNormal(pathDisable + name);
			continue;
		}
		else {
			item->loadTextureNormal(pathLock + name);
			continue;
		}
	}
	int active = UserDefault::getInstance()->getIntegerForKey("CharacterActive", 1);
	_listItem[active-1]->loadTextureNormal(pathSelect + std::to_string(active) + ".png");

}
void BPChooseCharacter::onEnter() {
	_background->setScale(0);
	_background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.8)));
	_background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.8)));
	cocos2d::Layer::onEnter();
}
