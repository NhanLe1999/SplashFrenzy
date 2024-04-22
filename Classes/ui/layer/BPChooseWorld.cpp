#include "BPChooseWorld.h"
#include "cocos2d.h"
#include "BPHelperManager.h"
#include "BPSoundManager.h"
#include "BPGameManager.h"
#include "SFGameScene.h"
#include "BPMainMenuScene.h"
#include "BPChooseCharacter.h"
#define NUMBER_ITEM  7
#define NUMBER_LAYER 10
bool BPChooseWorld::init() {
	if (!Layer::init())
	{
		return false;
	}
	initData();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BPHelperManager::GetInstance()->addLockLayer(this);

	_background = Sprite::create("res/BlackPink/popup/popup_world/bis_popup_world.png");
	this->addChild(_background);
	_background->setPosition((Vec2)visibleSize / 2 + origin + Vec2(0,20));

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
		auto layer = BPChooseCharacter::create();
		this->getParent()->addChild(layer);
		this->removeFromParent();
		});
	initButtonLv();
	initLabel();
	return true;
}
void BPChooseWorld::initData() {
	_mapItemCoin[1] = 1000;
	_mapItemCoin[2] = 1500;
	_mapItemCoin[3] = 5000;
	ItemData data;
	data.pathEnable = "res/BlackPink/popup/popup_world/bis_popup_world_selected_1.png";
	data.pathDisable = "res/BlackPink/popup/popup_world/bis_popup_world_non_1.png";
	data.pathLock = "res/BlackPink/popup/popup_world/bis_popup_world_non_1.png";
	_listItemData.push_back(data);

	ItemData data1;
	data1.pathEnable = "res/BlackPink/popup/popup_world/bis_popup_world_selected_2.png";
	data1.pathDisable = "res/BlackPink/popup/popup_world/bis_popup_world_non_2.png";
	data1.pathLock = "res/BlackPink/popup/popup_world/bis_popup_world_lock_2.png";
	_listItemData.push_back(data1);

	ItemData data2;
	data2.pathEnable = "res/BlackPink/popup/popup_world/bis_popup_world_selected_3.png";
	data2.pathDisable = "res/BlackPink/popup/popup_world/bis_popup_world_non_3.png";
	data2.pathLock = "res/BlackPink/popup/popup_world/bis_popup_world_lock_3.png";
	_listItemData.push_back(data2);

	ItemData data3;
	data3.pathEnable = "res/BlackPink/popup/popup_world/bis_popup_world_selected_4.png";
	data3.pathDisable = "res/BlackPink/popup/popup_world/bis_popup_world_non_4.png";
	data3.pathLock = "res/BlackPink/popup/popup_world/bis_popup_world_lock_4.png";
	_listItemData.push_back(data3);


}
void BPChooseWorld::initButtonLv() {
	auto bgSize = _background->getContentSize();
	float posY = 420;
	float posX = 28;
	auto item1 = Button::create("res/BlackPink/popup/popup_world/bis_popup_world_selected_1.png");
	_background->addChild(item1);
	item1->setAnchorPoint(Vec2(0,0.5));
	item1->setPosition(Vec2(posX,posY));
	item1->setTag(0);
	_listItem.push_back(item1);
	item1->addClickEventListener(CC_CALLBACK_1(BPChooseWorld::clickButtonLvEvent,this));

	auto item2 = Button::create(_listItemData[1].pathLock);
	_background->addChild(item2);
	item2->setAnchorPoint(Vec2(0, 0.5));
	item2->setTag(1);
	_listItem.push_back(item2);
	item2->setPosition(Vec2(posX + item2->getContentSize().width + 10, posY));
	item2->addClickEventListener(CC_CALLBACK_1(BPChooseWorld::clickButtonLvEvent, this));

	posY -= (item2->getContentSize().height + 10);
	auto item3 = Button::create(_listItemData[2].pathLock);
	_background->addChild(item3);
	item3->setAnchorPoint(Vec2(0, 0.5));
	item3->setPosition(Vec2(posX, posY));
	item3->setTag(2);
	_listItem.push_back(item3);
	item3->addClickEventListener(CC_CALLBACK_1(BPChooseWorld::clickButtonLvEvent, this));

	auto item4 = Button::create(_listItemData[3].pathLock);
	_background->addChild(item4);
	item4->setAnchorPoint(Vec2(0, 0.5));
	item4->setTag(3);
	_listItem.push_back(item4);
	item4->setPosition(Vec2(posX + item2->getContentSize().width + 10, posY));
	item4->addClickEventListener(CC_CALLBACK_1(BPChooseWorld::clickButtonLvEvent, this));

}
void BPChooseWorld::initLabel() {
	Sprite* bgMusic = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_main.png");
	_background->addChild(bgMusic);
	bgMusic->setAnchorPoint(Vec2(0, 1));
	bgMusic->setPosition(Vec2(0, -10));
	Sprite* headMusic = Sprite::create("res/BlackPink/ui/bis_ui_icon_notes_world_lock.png");
	bgMusic->addChild(headMusic);
	headMusic->setAnchorPoint(Vec2(0, 0.5));
	headMusic->setPosition(Vec2(0, bgMusic->getContentSize().height / 2));
	int coin = HELPER_MANAGER->GetTotalNumberCoin(false);
	auto _numberMusic = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
	_numberMusic->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));

	bgMusic->addChild(_numberMusic);

	Sprite* bgCoin = Sprite::create("res/BlackPink/ui/bis_ui_bar_world_main.png");
	_background->addChild(bgCoin);
	bgCoin->setAnchorPoint(Vec2(1, 1));
	bgCoin->setPosition(Vec2(_background->getContentSize().width, -10));

	Sprite* headCoin = Sprite::create("res/BlackPink/ui/bis_ui_icon_gem_world_main.png");
	bgCoin->addChild(headCoin);
	headCoin->setAnchorPoint(Vec2(0, 0.5));
	headCoin->setPosition(Vec2(0, bgCoin->getContentSize().height / 2));
	coin = coin = HELPER_MANAGER->GetTotalNumberCoin(true);
	auto _numberCoin = Label::createWithTTF(std::to_string(coin), "fonts/Baloo2-Bold.ttf", 50);
	_numberCoin->setPosition(Vec2(197, bgMusic->getContentSize().height / 2));
	bgCoin->addChild(_numberCoin);
}
void BPChooseWorld::clickButtonLvEvent(Ref* sender) {
    SOUND_MANAGER->playClickEffect();
	auto bt = (Button*)sender;
	int type = bt->getTag();
	//if (type != 0)return;
	//std::string data = "StatusMap_" + std::to_string(type);
	//int status = UserDefault::getInstance()->getIntegerForKey(data.c_str(), -1);
	//disableItem();
	
}
void BPChooseWorld::disableItem() {
	for (auto item : _listItem) {
		int type = item->getTag();
		if (type == 0) {
			item->loadTextureNormal(_listItemData[type].pathDisable);
			continue;
		}
		std::string data = "StatusMap_" + std::to_string(type);
		int status = UserDefault::getInstance()->getIntegerForKey(data.c_str(), -1);
		data = "";
		if (status == -1) {
			item->loadTextureNormal(_listItemData[type].pathLock);
		}
		item->loadTextureNormal(_listItemData[type].pathDisable);
	}
}
void BPChooseWorld::onEnter(){
    _background->setScale(0);
    _background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.8)));
    _background->runAction(EaseBackOut::create(ScaleTo::create(0.35, 0.8)));
    cocos2d::Layer::onEnter();
}
