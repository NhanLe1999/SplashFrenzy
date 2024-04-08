#include "CaculateQuickGameOverLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickSettingLayer.h"
#include "CaculateQuickLeaderboardLayer.h"
#include "CaculateQuickAnimationManager.h"

USING_NS_CC;

INITIALIZE_READER(CaculateQuickGameOverLayer);
#define LOSE_COIN 100

std::once_flag _gameover_layer_flag;

Scene*  CaculateQuickGameOverLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickGameOverLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickGameOverLayer * CaculateQuickGameOverLayer::createView() 
{
    std::call_once(_gameover_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickGameOverLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickGameOverLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickGameOverLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickGameOverLayer::didLoadFromCSB()
{
    SOUND_MANAGER->playOnGameOver();
//    auto num = UserDefault::getInstance()->getIntegerForKey(KEY_NUM_REVIAL_CONTINUE_GAME, 0);
//    
//    OnEnableBtnRevival(num <= 0);

    auto txt = utils::findChild<ui::Text*>(this, "text_coin");
    txt->setString(StringUtils::format("+%d",LOSE_COIN));
}

void CaculateQuickGameOverLayer::onHomeButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    auto button = dynamic_cast<ui::Button*>(sender);

    button->setTouchEnabled(false);

    SOUND_MANAGER->playClickEffect();

    auto scene = CaculateQuickMainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(scene);
}

void CaculateQuickGameOverLayer::onReplayButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    Director::getInstance()->replaceScene(CaculateQuickGameScene::createScene());
}

void CaculateQuickGameOverLayer::onSettingButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickSettingLayer::createView();
    this->getParent()->addChild(view);
    this->removeFromParent();
}

void CaculateQuickGameOverLayer::OnShowNumStar(int numstar)
{
    if (auto star = utils::findChild<ImageView*>(this, "star")) {

        std::string path = cocos2d::StringUtils::format("CaculateQuick/popup/sb_popup_win_star_%d.png", numstar);
        star->loadTexture(path);
    }
}

void CaculateQuickGameOverLayer::OnShowTextLevel(int numLevel)
{
    if (auto txt = utils::findChild<ui::Text*>(this, "text_level")) {
        txt->setString(std::to_string(numLevel));
    }
}

void CaculateQuickGameOverLayer::OnEnableBtnRevival(bool isEnablae)
{
    if (!isEnablae) {
        if (auto btn = utils::findChild<ui::Button*>(this, "btn_revival")) {
            btn->setTouchEnabled(false);
            btn->loadTextureNormal("Dumpling_Rush/icon/dr_icon_revival_block.png");
        }
    }else{
        
    }
}

void CaculateQuickGameOverLayer::updateHighScore(std::pair<int, int> newScore)
{
    if (auto txt = utils::findChild<ui::Text*>(this, "text_level")) {
        txt->setString(std::to_string(newScore.second));
    }

    if (auto txt = utils::findChild<ui::Text*>(this, "text_coin")) {
        txt->setString(std::to_string(newScore.first));
    }

    std::vector<std::pair<int, int>> leaderboards;

    leaderboards.push_back(newScore);

    for (int i = 1; i <= 10; i++) {

        const std::string k_scoreKey = StringUtils::format("txt_score_%d", i);
        const std::string k_timeKey = StringUtils::format("txt_level_%d", i);

        auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);
        auto time = UserDefault::getInstance()->getIntegerForKey(k_timeKey.c_str(), 0);

        leaderboards.push_back({ score,time });
    }

    std::sort(leaderboards.begin(), leaderboards.end(), [](const std::pair<int, int> a, const std::pair<int, int> b) {

        if (a.first == b.first) return a.second < b.second;

        return a.first > b.first;

        });

    for (int i = 1, j = 0; i <= 10; i++, j++) {

        if (j >= leaderboards.size()) {
            return;
        }

        auto b = leaderboards.at(j);

        const std::string k_scoreKey = StringUtils::format("txt_score_%d", i);
        const std::string k_timeKey = StringUtils::format("txt_level_%d", i);

        UserDefault::getInstance()->setIntegerForKey(k_scoreKey.c_str(), b.first);
        UserDefault::getInstance()->setIntegerForKey(k_timeKey.c_str(), b.second);
    }
}

void CaculateQuickGameOverLayer::onRankButtonClicked(cocos2d::Ref* sender)
{
    auto view = CaculateQuickLeaderboardLayer::createView();
    view->setButtonsVisible(false);
    this->addChild(view);
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void CaculateQuickGameOverLayer::onClose(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    onHomeButtonClicked(sender);
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickGameOverLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickGameOverLayer, onReplayButtonClicked),
        CLICK_MAP(CaculateQuickGameOverLayer, onHomeButtonClicked),
        CLICK_MAP(CaculateQuickGameOverLayer, onRankButtonClicked),
        CLICK_MAP(CaculateQuickGameOverLayer, onClose),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
