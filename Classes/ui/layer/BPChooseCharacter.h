#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class BPChooseCharacter : public cocos2d::Layer
{
public:

	CREATE_FUNC(BPChooseCharacter);
	bool init() override;
	void initButtonLv();
	void initLabel();
	void initData();
	void clickButtonLvEvent(Ref* sender);
	std::vector<Button*> _listButtonLV;
	Sprite* _background;
	Label* _numberMusic;
	Label* _numberCoin;
	void loadStatusItem();
	void onEnter() override;
	std::vector<Button*> _listItem;
	std::map<int, int> _mapItemCoin;
};

