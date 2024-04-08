#include "CaculateQuickLeaderboardLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickMainMenuScene.h"

USING_NS_CC;

INITIALIZE_READER(CaculateQuickLeaderboardLayer);

std::once_flag _leaderboard_layer_flag;

Scene*  CaculateQuickLeaderboardLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickLeaderboardLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickLeaderboardLayer * CaculateQuickLeaderboardLayer::createView() 
{

    std::call_once(_leaderboard_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickLeaderboardLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickLeaderboardLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickLeaderboardLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickLeaderboardLayer::updateHighScore(int type, float time, std::pair<int, int> newScore)
{
    if (auto txt = utils::findChild<ui::Text*>(this, "txt_score_game_over")) {
        txt->setVisible(true);
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

        return a.first < b.first;

        });

    for (int i = 1, j = 0; i <= 10; i++, j++) {

        if (j >= leaderboards.size()) {
            return;
        }

        auto b = leaderboards.at(j);

        const std::string k_scoreKey = StringUtils::format("txt_score_%d", i);
        const std::string k_timeKey = StringUtils::format("txt_level_%d", i);

        UserDefault::getInstance()->setIntegerForKey(k_scoreKey.c_str(), (int)time);
        UserDefault::getInstance()->setIntegerForKey(k_timeKey.c_str(), b.second);
    }
}
void CaculateQuickLeaderboardLayer::setButtonsVisible(bool value)
{
    auto replay = utils::findChild(this, "replay_button");
    replay->setVisible(value);

    auto home = utils::findChild(this, "home_button");
    home->setVisible(value);
}

void CaculateQuickLeaderboardLayer::setCloseButtonVisible(bool value)
{
    auto home = utils::findChild(this, "back_button");
    home->setVisible(value);
}

void CaculateQuickLeaderboardLayer::didLoadFromCSB()
{
    if (auto txt = utils::findChild<ui::Text*>(this, "score_text")) {
        txt->setString(std::to_string(HELPER_MANAGER->GetTotalNumberCoin()));
    }

    auto item = utils::findChild<ui::ImageView*>(this, "icon_level");

    auto node1 = utils::findChild<ListView*>(this, "list_1");
    node1->setScrollBarEnabled(true);
    node1->setScrollBarAutoHideTime(true);

    for (int i = 0; i < 10; i++) {
        auto img = item->clone();

        if (i < 3)
        {
            if (auto icon = img->getChildByName<ImageView*>("img_icon"))
            {
                icon->setVisible(true);
                icon->loadTexture("CaculateQuick/Popup/Top-" + std::to_string(i + 1) + ".png");
            }

            if (auto icon = img->getChildByName("rank"))
            {
                icon->setVisible(false);
            }
        }
        else {
            if (auto icon = img->getChildByName<ImageView*>("img_icon"))
            {
                icon->setVisible(false);
            }
        }

        img->setName(std::to_string(i + 1));
        img->setVisible(true);
        node1->addChild(img);
    }

    int fontSize = 40;

    _btnCurrent = utils::findChild<ui::Button*>(this, "btn_easy");

    ShowLeaderBoadById(1);
}

void CaculateQuickLeaderboardLayer::ShowLeaderBoadById(int id)
{

    std::vector<std::pair<int, int>> leaderboards;

    for (int i = 1; i <= 10; i++) {

        const std::string k_scoreKey = StringUtils::format("txt_score_%d", i);
        const std::string k_timeKey = StringUtils::format("txt_level_%d", i);

        auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);
        auto time = UserDefault::getInstance()->getIntegerForKey(k_timeKey.c_str(), 0);

        leaderboards.push_back({ score,time });
    }

    std::sort(leaderboards.begin(), leaderboards.end(), [](const std::pair<int, int> a, const std::pair<int, int> b) {

        if (a.second == 0 || b.second == 0)
        {
            return false;
        }

        if (a.second > b.second)
        {
            return a.first < b.first;
        }

        return a.first < b.first;

        });

    auto last = std::unique(leaderboards.begin(), leaderboards.end());

    leaderboards.erase(last, leaderboards.end());

    std::sort(leaderboards.begin(), leaderboards.end(), [](const std::pair<int, int> a, const std::pair<int, int> b) {

        if (a.second == 0 || b.second == 0)
        {
            return false;
        }

        /*if (a.second > b.second)
        {
            return a.first < b.first;
        }*/

        return a.first > b.first;

        });

    for (int i = 0; i < leaderboards.size(); i++) {

        auto b = leaderboards.at(i);
        std::string timePlay = HELPER_MANAGER->getTimeToString(b.first);

        if (auto pa = utils::findChild(this, std::to_string(i + 1))) {
            pa->getChildByName<ui::Text*>("txt_score")->setString(cocos2d::StringUtils::format("%d", b.first));
            pa->getChildByName<ui::Text*>("txt_level")->setString(cocos2d::StringUtils::format("%d", b.second));
            pa->getChildByName<ui::Text*>("rank")->setString(std::to_string(i + 1));
            _listNode.push_back(pa);
        }
    }

    if (leaderboards.size() < 10)
    {
        for (int i = leaderboards.size(); i < 10; i++)
        {
            if (auto pa = utils::findChild(this, std::to_string(i + 1)))
            {
                pa->removeFromParent();
            }
        }
    }
}

void CaculateQuickLeaderboardLayer::OnlickBtnLevel(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto btn = dynamic_cast<ui::Button*>(sender);
    ShowLeaderBoadById(btn->getTag());
}

void CaculateQuickLeaderboardLayer::onCloseButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    this->removeFromParent();
}

void CaculateQuickLeaderboardLayer::onHomeButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,CaculateQuickMainMenuScene::createScene()));

}

void CaculateQuickLeaderboardLayer::onReplayButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,CaculateQuickGameScene::createScene()));

}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickLeaderboardLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickLeaderboardLayer, onCloseButtonClicked),
        CLICK_MAP(CaculateQuickLeaderboardLayer, onHomeButtonClicked),
        CLICK_MAP(CaculateQuickLeaderboardLayer, onReplayButtonClicked)
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
