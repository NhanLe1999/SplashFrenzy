#include "CaculateQuickSettingLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickMainMenuScene.h"
#include "CaculateQuickSoundManager.h"

USING_NS_CC;


INITIALIZE_READER(CaculateQuickSettingLayer);

std::once_flag _setting_layer_flag;

Scene*  CaculateQuickSettingLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickSettingLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickSettingLayer * CaculateQuickSettingLayer::createView() 
{
    std::call_once(_setting_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickSettingLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickSettingLayer *>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickSettingLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickSettingLayer::didLoadFromCSB()
{
    auto isMusicOn = UserDefault::getInstance()->getBoolForKey("key_is_music_on", true);

    if (auto button = utils::findChild<ui::ImageView*>(this, "music_button")) {
        std::string path = StringUtils::format("CaculateQuick/Popup/music_%s.png", !isMusicOn ? "off" : "on");
        button->loadTexture(path);
    }

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey("key_is_sound_on", true);

    if (auto button = utils::findChild<ui::ImageView*>(this, "sound_button")) {
        std::string pathMusic = StringUtils::format("CaculateQuick/Popup/sound_%s.png", !isSoundOn ? "off" : "on");
        button->loadTexture(pathMusic);
    }
}

void CaculateQuickSettingLayer::onClose(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    if (auto sum = dynamic_cast<CaculateQuickGameScene*>(this->getParent())) {
        sum->onGameResume();
    }
    this->removeFromParent();
}

void CaculateQuickSettingLayer::onMusicButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto button = dynamic_cast<cocos2d::ui::ImageView*>(sender);
    auto isSound = SOUND_MANAGER->isMusicEffectEnable();
    UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, !isSound);
    std::string path = StringUtils::format("CaculateQuick/Popup/music_%s.png", isSound ? "off" : "on");
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

void CaculateQuickSettingLayer::onSoundButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();
    auto button = dynamic_cast<cocos2d::ui::ImageView*>(sender);
    auto isSound = SOUND_MANAGER->isSoundEffectEnable();
    UserDefault::getInstance()->setBoolForKey(IS_SOUND_KEY_ON, !isSound);

    std::string path = StringUtils::format("CaculateQuick/Popup/sound_%s.png", isSound ? "off" : "on");
    button->loadTexture(path, TextureResType::LOCAL);
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickSettingLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickSettingLayer, onClose),
        CLICK_MAP(CaculateQuickSettingLayer, onMusicButtonClicked),
        CLICK_MAP(CaculateQuickSettingLayer, onSoundButtonClicked),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
