#include "CaculateQuickPauseLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickSettingLayer.h"

USING_NS_CC;

INITIALIZE_READER(CaculateQuickPauseLayer);

std::once_flag _pause_layer_flag;

Scene*  CaculateQuickPauseLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickPauseLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickPauseLayer * CaculateQuickPauseLayer::createView() 
{
    std::call_once(_pause_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickPauseLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickPauseLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickPauseLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickPauseLayer::didLoadFromCSB()
{
    auto isMusicOn = UserDefault::getInstance()->getBoolForKey("key_is_music_on", true);

    if (auto button = utils::findChild<ui::ImageView*>(this, "music_button")) {
        std::string path = StringUtils::format("CaculateQuick/Popup/sound_%s.png", !isMusicOn ? "off" : "on");
        button->loadTexture(path);
    }

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey("key_is_sound_on", true);

    if (auto button = utils::findChild<ui::ImageView*>(this, "sound_button")) {
        std::string pathMusic = StringUtils::format("CaculateQuick/Popup/music_%s.png", !isSoundOn ? "off" : "on");
        button->loadTexture(pathMusic);
    }
}

void CaculateQuickPauseLayer::onMusicButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto button = dynamic_cast<cocos2d::ui::ImageView*>(sender);
    auto isSound = SOUND_MANAGER->isMusicEffectEnable();
    UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, !isSound);
    std::string path = StringUtils::format("CaculateQuick/Popup/sound_%s.png", isSound ? "off" : "on");
    button->loadTexture(path, TextureResType::LOCAL);
    if (!isSound)
    {
        SOUND_MANAGER->resumeAllBackgroundMusics();
    }
    else
    {
        SOUND_MANAGER->pauseAllBackgroundMusics();
    }
}

void CaculateQuickPauseLayer::onSoundButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto button = dynamic_cast<cocos2d::ui::ImageView*>(sender);
    auto isSound = SOUND_MANAGER->isSoundEffectEnable();
    UserDefault::getInstance()->setBoolForKey(IS_SOUND_KEY_ON, !isSound);

    std::string path = StringUtils::format("CaculateQuick/Popup/music_%s.png", isSound ? "off" : "on");
    button->loadTexture(path, TextureResType::LOCAL);
}

void CaculateQuickPauseLayer::onHomeButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    auto button = dynamic_cast<ui::Button*>(sender);

    button->setTouchEnabled(false);

    SOUND_MANAGER->playClickEffect();

    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,CaculateQuickMainMenuScene::createScene()));
}

void CaculateQuickPauseLayer::onReplayButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();


    Director::getInstance()->replaceScene(TransitionFade::create(0.3f,CaculateQuickGameScene::createScene()));
}

void CaculateQuickPauseLayer::onPlayButtonClicked(cocos2d::Ref* sender)
{
    HELPER_MANAGER->disableButton(sender);

    SOUND_MANAGER->playClickEffect();

    if (auto na = dynamic_cast<CaculateQuickGameScene*>(this->getParent())) {

        na->onGameResume();
    }

    this->removeFromParent();
}

void CaculateQuickPauseLayer::onClose(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    if (auto na = dynamic_cast<CaculateQuickGameScene*>(this->getParent())) {
        na->onGameResume();
    }
    this->removeFromParent();
}

void CaculateQuickPauseLayer::onSettingButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickSettingLayer::createView();
    this->getParent()->addChild(view);
    this->removeFromParent();
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickPauseLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickPauseLayer, onPlayButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onReplayButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onHomeButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onSoundButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onMusicButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onSettingButtonClicked),
        CLICK_MAP(CaculateQuickPauseLayer, onClose),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
