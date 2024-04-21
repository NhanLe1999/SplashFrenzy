#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class BPChooseWorld : public cocos2d::Layer
{
public:
	struct ItemData
	{
		std::string pathEnable;
		std::string pathLock;
		std::string pathDisable;
	};
	CREATE_FUNC(BPChooseWorld);
	bool init() override;
	void initButtonLv();
	void initLabel();
	void initData();
	void initButtonDirection();
	void loadLvConfig();
	void clickButtonLvEvent(Ref* sender);
	std::vector<Button*> _listButtonLV;
	Sprite* _background;
	int _indexLayer;
	Button* _btBack;
	Button* _btNext;
	void disableItem();
    void onEnter() override;
	std::vector<Button*> _listItem;
	std::vector<ItemData> _listItemData;
	std::map<int, int> _mapItemCoin;
};

