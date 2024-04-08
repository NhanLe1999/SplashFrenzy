#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickGuideLayer.h"
#include "CaculateQuickLeaderboardLayer.h"
#include "CaculateQuickAnimationManager.h"
#include "audio/include/SimpleAudioEngine.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickLevelLayer.h"
#include "CaculateQuickSettingLayer.h"
#include "CaculateQuickShopLayer.h"

using namespace CocosDenshion;

USING_NS_CC;

INITIALIZE_READER(CaculateQuickMainMenuScene);

std::once_flag _main_menu_scene;//4.

Scene*  CaculateQuickMainMenuScene::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickMainMenuScene::createView();
        view->setPosition(Director::getInstance()->getVisibleOrigin());
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

CaculateQuickMainMenuScene* CaculateQuickMainMenuScene::createView()
{
    std::call_once(_main_menu_scene, []
        {
            REGISTER_CSB_READER(CaculateQuickMainMenuScene);
        });

    auto view = reinterpret_cast<CaculateQuickMainMenuScene*>(CSLoader::createNodeWithVisibleSize("csb/ui/scene/CaculateQuickMainMenuScene.csb"));

    if (view)
    {
        view->didLoadFromCSB();
        return view;
    }

    CC_SAFE_DELETE(view);

    return nullptr;
}


bool CaculateQuickMainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    return true;
}

void CaculateQuickMainMenuScene::OnLoadingSucess()
{
    if (auto menu = utils::findChild(this, "menu"))
    {
        menu->setVisible(true);
    }

    if (auto listView = utils::findChild<ui::ListView*>(this, "view")) {
        listView->setVisible(true);
        auto screenSize = Director::getInstance()->getVisibleSize();
        /*listView->setScale((screenSize.width - 60) / 1420);*/

        auto x = listView->getBoundingBox().size.width;
        auto size = listView->getContentSize();
        size.width = std::fminf((size.width - 20) * (1/0.85f), 1425.0);
        listView->setTouchEnabled(1425.0f * 0.85f > screenSize.width);
        listView->setContentSize(size);
    }

    if (auto btn_back = utils::findChild(this, "btn_back"))
    {
        btn_back->setVisible(false);
    }
}

float calculateFitScaleFactor(Size child, Size parent, int strategy) {
    float scale;
    if (strategy == 0) {
        scale = std::min(parent.width / child.width, parent.height / child.height);
    }
    else {
        scale = std::max(parent.width / child.width, parent.height / child.height);
    }
    return scale;
}

void CaculateQuickMainMenuScene::didLoadFromCSB()
{
    auto screenSize = Director::getInstance()->getVisibleSize();
    auto sc = screenSize.height / 1080;

    if (auto bg = utils::findChild(this, "bg"))
    {
        bg->setScale(sc);

        crippleSprite = new CrippleSprite();// ("bg_menu.png")
        crippleSprite->autorelease();
        crippleSprite->scheduleUpdate();
        crippleSprite->initWithX(INIT_WITH_FILE, "CaculateQuick/bgr_home.jpg", 8);
        crippleSprite->setPosition(bg->getContentSize() * 0.5f);
        crippleSprite->setScale(calculateFitScaleFactor(crippleSprite->getContentSize(), bg->getContentSize(), 1));
        bg->addChild(crippleSprite);
    }

    if (auto bg = utils::findChild(this, "bg1_loading"))
    {
        bg->setScale(sc);
    }

    auto animRoom_1 = spine::SkeletonAnimation::createWithJsonFile("CaculateQuick/Export_logo/Logo.json", "CaculateQuick/Export_logo/Logo.atlas", 1.0);
    animRoom_1->setAnimation(0, "animation", true);
    animRoom_1->setPosition(Vec2(screenSize / 2) + Vec2(0, 100));
    animRoom_1->setOpacity(255 * 0.8f);
    this->addChild(animRoom_1);

  
    //HELPER_MANAGER->AddNumberCoin(3000);
    
    SOUND_MANAGER->playMainMenuMusic(false);
    if(auto img_music = utils::findChild(this, "img_music")){
        auto action2 = RepeatForever::create(RotateBy::create(0.25f, 1));
        img_music->runAction(action2);
    }

    auto tag = 0.5f;

    OnLoadingSucess();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (auto bg = utils::findChild(this, "bg")) {
        auto sx = visibleSize.width / 2280;
        auto sy = visibleSize.height / 1080;
        bg->setScale(std::max(sx, sy));
    }

    //logo->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(3.0f, 1.02f * currentScaleFactor, 0.9f * currentScaleFactor)), EaseBackOut::create(ScaleTo::create(3.0f, 1.0f * currentScaleFactor)))));
    auto playButton = utils::findChild(this, "play_button");
    float k_currentScaleFactor = playButton->getScale();
    playButton->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(3.0f, 1.02f * k_currentScaleFactor, 0.9f * k_currentScaleFactor)), EaseBackOut::create(ScaleTo::create(3.0f, 1.0f * k_currentScaleFactor)))));
    
    auto vertFilename = std::string("shader1.vsh");
    auto fragFilename = std::string("shader1.fsh");
}

void CaculateQuickMainMenuScene::onPlayButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto btn = dynamic_cast<ui::Button*>(sender);
    auto tag = btn->getTag();
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickLevelLayer::createView();
    this->addChild(view);
    //Director::getInstance()->replaceScene(TransitionFade::create(0.3f, CaculateQuickLevelLayer::createScene()));
}


void CaculateQuickMainMenuScene::onTutorialButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickGuideLayer::createView();
    this->addChild(view);
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void CaculateQuickMainMenuScene::onShopButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickShopLayer::createView();
    this->addChild(view);
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void CaculateQuickMainMenuScene::onSettingButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickSettingLayer::createView();
    this->addChild(view);
}

void CaculateQuickMainMenuScene::onLeaderBoardButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickLeaderboardLayer::createView();
    this->addChild(view);
}

void CaculateQuickMainMenuScene::OnContinueGame(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto tag = dynamic_cast<ui::Button*>(sender)->getTag();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, CaculateQuickGameScene::createScene()));
}

void CaculateQuickMainMenuScene::OnPlayGame(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto btn = dynamic_cast<ui::Button*>(sender);
    auto tag = btn->getTag();
    SOUND_MANAGER->playClickEffect();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, CaculateQuickGameScene::createScene()));
}



cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickMainMenuScene::onLocateClickCallback(const std::string& callBackName)
{
    std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickMainMenuScene, onPlayButtonClicked),
        CLICK_MAP(CaculateQuickMainMenuScene, onShopButtonClicked),
        CLICK_MAP(CaculateQuickMainMenuScene, onTutorialButtonClicked),
        CLICK_MAP(CaculateQuickMainMenuScene, onSettingButtonClicked),
        CLICK_MAP(CaculateQuickMainMenuScene, onLeaderBoardButtonClicked),
    };

    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}

ui::Widget::ccWidgetTouchCallback CaculateQuickMainMenuScene::onLocateTouchCallback(const std::string& callback_name) {
    
    if (callback_name == "onTouch") 
    {
        return CC_CALLBACK_2(CaculateQuickMainMenuScene::onTouch, this);
    }

    return nullptr;
}

void CaculateQuickMainMenuScene::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type) {

    auto obj = static_cast<ui::Widget*>(sender);
    
    auto bg = utils::findChild(this, "bg");

    switch (event_type) 
    {
        case ui::Widget::TouchEventType::BEGAN:
            //this->setLocalZOrder(100);
           // this->getParent()->setLocalZOrder(100);
            //_original_point = this->getPosition();
            break;

        case ui::Widget::TouchEventType::MOVED:
        {
            CCPoint location = obj->getTouchMovePosition();
            
            location = bg->convertToNodeSpace(location);

            //location = CCDirector::sharedDirector()->convertToGL(location);
            crippleSprite->doTouch(location, 512, 12);
            break;
        }
        case ui::Widget::TouchEventType::ENDED:
           // _delegate->onAnswerMoved(this, obj->getTouchEndPosition());
            break;

        case ui::Widget::TouchEventType::CANCELED:
           // _delegate->onAnswerMoved(this, obj->getTouchEndPosition());
            break;

        default:
            break;
    }
}
