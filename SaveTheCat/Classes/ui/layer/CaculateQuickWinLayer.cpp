#include "CaculateQuickWinLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickSettingLayer.h"
#include "CaculateQuickLeaderboardLayer.h"
#include "CaculateQuickAnimationManager.h"

USING_NS_CC;

INITIALIZE_READER(CaculateQuickWinLayer);

std::once_flag _win_layer_flag;

Scene*  CaculateQuickWinLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickWinLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickWinLayer * CaculateQuickWinLayer::createView() 
{
    std::call_once(_win_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickWinLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickWinLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickWinLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickWinLayer::didLoadFromCSB()
{
    SOUND_MANAGER->playLevlUpEffect();
}

void CaculateQuickWinLayer::onHomeButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    auto button = dynamic_cast<ui::Button*>(sender);

    button->setTouchEnabled(false);

    SOUND_MANAGER->playClickEffect();

    auto scene = CaculateQuickMainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,scene));
}

void CaculateQuickWinLayer::onNextButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,CaculateQuickGameScene::createScene()));
}

void CaculateQuickWinLayer::OnShowTextLevel(int numLevel, int numStar, int typeState)
{
    if (auto txt = utils::findChild<ui::Text*>(this, "text_level")) {
        txt->setString(std::to_string(numLevel));
    }

    if (auto star = utils::findChild<ImageView*>(this, "star")) {

        std::string path = cocos2d::StringUtils::format("CaculateQuick/popup/sb_popup_win_star_%d.png", numStar);
        star->loadTexture(path);
    }

    if (auto txt = utils::findChild<ui::Text*>(this, "text_coin"))
    {
        auto co = typeState;
        txt->setString((co != 0 ? "+" : "") + std::to_string(co));
    }

    UserDefault::getInstance()->setIntegerForKey(cocos2d::StringUtils::format(KEY_CURENT_LEVEL).c_str(), numLevel + 1);

    auto numS = UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(KEY_STAR_LEVEL, numLevel - 1).c_str(), 0);

    if (numStar > numS)
    {
        UserDefault::getInstance()->setIntegerForKey(cocos2d::StringUtils::format(KEY_STAR_LEVEL, numLevel - 1).c_str(), numStar);
    }
    
    if (numLevel >= UserDefault::getInstance()->getIntegerForKey(KEY_SAVE_LEVEL, 0)) {
        UserDefault::getInstance()->setIntegerForKey(KEY_SAVE_LEVEL, numLevel);
    }
   
}

void CaculateQuickWinLayer::onSettingButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickSettingLayer::createView();
    this->getParent()->addChild(view);
    this->removeFromParent();
}

void CaculateQuickWinLayer::updateHighScore(std::pair<int, int> newScore)
{
    if (auto txt = utils::findChild<ui::Text*>(this, "text_level")) {
        txt->setString(std::to_string(newScore.second));
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


void CaculateQuickWinLayer::onRankButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    auto cu = UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(KEY_CURENT_LEVEL).c_str(), 0);;
    UserDefault::getInstance()->setIntegerForKey(cocos2d::StringUtils::format(KEY_CURENT_LEVEL).c_str(), cu - 1);

    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, CaculateQuickGameScene::createScene()));
}

void CaculateQuickWinLayer::onClose(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    onHomeButtonClicked(sender);
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickWinLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickWinLayer, onNextButtonClicked),
        CLICK_MAP(CaculateQuickWinLayer, onHomeButtonClicked),
        CLICK_MAP(CaculateQuickWinLayer, onRankButtonClicked),
        CLICK_MAP(CaculateQuickWinLayer, onClose),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
