#include "CaculateQuickShopLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"

USING_NS_CC;


INITIALIZE_READER(CaculateQuickShopLayer);

std::once_flag _shop_layer_flag;

Scene*  CaculateQuickShopLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickShopLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickShopLayer * CaculateQuickShopLayer::createView() 
{
    std::call_once(_shop_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickShopLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickShopLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickShopLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickShopLayer::didLoadFromCSB()
{
    if (UserDefault::getInstance()->getBoolForKey(KEY_THE_FIRST, true)) {
        UserDefault::getInstance()->setBoolForKey(KEY_THE_FIRST, false);
        UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_FROG, 3);
        UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_KHIEN, 3);
        UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_HAMMER, 3);
    }


    _txtFixer = utils::findChild<ui::Text*>(this, "txt_fixer");
    _txtSheild = utils::findChild<ui::Text*>(this, "txt_sheild");
    _txtRuler = utils::findChild<ui::Text*>(this, "txt_ruler");

    _txtFixer->setString(std::to_string(UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_HAMMER, 3)));
    _txtSheild->setString(std::to_string(UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_KHIEN, 3)));
    _txtRuler->setString(std::to_string(UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_FROG, 3)));

    _BtnSkillRuler = utils::findChild<ui::Button*>(this, "skin_1");
    _BtnSkillSheild = utils::findChild<ui::Button*>(this, "skin_2");
    _BtnSkillFixer = utils::findChild<ui::Button*>(this, "skin_3");
   

    
    if (auto txt = utils::findChild<ui::Text*>(this, "score_text")) {
        txt->schedule([txt](float dt) {
            txt->setString(std::to_string(HELPER_MANAGER->GetTotalNumberCoin()));
            }, "delay_reset_numcoi");
    }

    std::vector<std::string> listName = {"btn_buy_fixer", "btn_buy_sheild", "btn_buy_ruler"};
    std::vector<int> listCoin = { 300, 200, 100 };

    for (int i = 0; i < listName.size(); i++) {
        if (auto node = utils::findChild(this, listName[i])) {

            node->setTag(listCoin[i]);

            auto btnBuy = node->getChildByName<ui::Button*>("btn_buy");
            auto child = node->getChildren();
            node->schedule([=](float dt) {
                if (node->getTag() <= HELPER_MANAGER->GetTotalNumberCoin()) {
                    node->setColor(Color3B(255, 255, 255));
                    btnBuy->loadTextureNormal("CaculateQuick/popup/sb_popup_shop_buy_a.png");
                }
                else {
                    node->setColor(Color3B(174, 174, 174));
                    btnBuy->loadTextureNormal("CaculateQuick/popup/sb_popup_shop_buy_b.png");
                }
                }, listName[i]);
        }
    }
}

//bua
void CaculateQuickShopLayer::onBuyFixer(cocos2d::Ref* sender)
{
    auto node1 = dynamic_cast<Node*>(sender);

    auto node = node1->getParent();

    if (node->getTag() > HELPER_MANAGER->GetTotalNumberCoin()) {
        return;
    }

    auto coinAdd = UserDefault::getInstance()->getIntegerForKey(node->getName().c_str(), 0);
    HELPER_MANAGER->AddNumberCoin(-node->getTag());

    std::string currentNumText = _txtRuler->getString();
    int number = std::stoi(currentNumText);
    _txtRuler->setString(std::to_string(number + 1));
    _BtnSkillRuler->loadTextureNormal(cocos2d::StringUtils::format("CaculateQuick/ui/%s.png", "sb_ui_item_fixer"));

    auto num = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_HAMMER, 3);
    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_HAMMER, num + 1);

    SOUND_MANAGER->playClickEffect();
    OnupdateNumSkill();
}

//khien
void CaculateQuickShopLayer::onBuySheild(cocos2d::Ref* sender)
{
    auto node1 = dynamic_cast<Node*>(sender);
    auto node = node1->getParent();
    if (node->getTag() > HELPER_MANAGER->GetTotalNumberCoin()) {
        return;
    }

    auto coinAdd = UserDefault::getInstance()->getIntegerForKey(node->getName().c_str(), 0);

    HELPER_MANAGER->AddNumberCoin(-node->getTag());
    SOUND_MANAGER->playClickEffect();

    std::string currentNumText = _txtSheild->getString();
    int number = std::stoi(currentNumText);
    _txtSheild->setString(std::to_string(number + 1));
    _BtnSkillSheild->loadTextureNormal(cocos2d::StringUtils::format("CaculateQuick/ui/%s.png", "sb_ui_item_sheild"));

    auto num = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_KHIEN, 3);
    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_KHIEN, num + 1);

    OnupdateNumSkill();
}

//frog
void CaculateQuickShopLayer::onBuyRuler(cocos2d::Ref* sender)
{
    auto node1 = dynamic_cast<Node*>(sender);
    auto node = node1->getParent();;
    if (node->getTag() > HELPER_MANAGER->GetTotalNumberCoin()) {
        return;
    }

    auto coinAdd = UserDefault::getInstance()->getIntegerForKey(node->getName().c_str(), 0);
    UserDefault::getInstance()->setIntegerForKey(node->getName().c_str(), coinAdd + 1);

    HELPER_MANAGER->AddNumberCoin(-node->getTag());

    std::string currentNumText = _txtFixer->getString();
    int number = std::stoi(currentNumText);
    _txtFixer->setString(std::to_string(number + 1));
    _BtnSkillFixer->loadTextureNormal(cocos2d::StringUtils::format("CaculateQuick/ui/%s.png", "sb_ui_item_ruler"));

    auto num = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_FROG, 3);
    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_FROG, num + 1);

    SOUND_MANAGER->playClickEffect();

    OnupdateNumSkill();
}

void CaculateQuickShopLayer::OnupdateNumSkill()
{
    if (auto game = dynamic_cast<CaculateQuickGameScene*>(this->getParent()))
    {
        game->OnUpdateNumSkillGame();
    }
}

void CaculateQuickShopLayer::onClose(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();

    if (auto game = dynamic_cast<CaculateQuickGameScene*>(this->getParent()))
    {
        game->onGameResume();
    }

    this->removeFromParent();
}

void CaculateQuickShopLayer::onAddButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->AddNumberCoin(10000);
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickShopLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickShopLayer, onClose),
        CLICK_MAP(CaculateQuickShopLayer, onBuyFixer),
        CLICK_MAP(CaculateQuickShopLayer, onBuySheild),
        CLICK_MAP(CaculateQuickShopLayer, onBuyRuler),
        CLICK_MAP(CaculateQuickShopLayer, onAddButtonClicked),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
