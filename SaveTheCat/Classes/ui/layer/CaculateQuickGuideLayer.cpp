#include "CaculateQuickGuideLayer.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickGameScene.h"
#include "CaculateQuickSoundManager.h"

#define NUMPAG 3

USING_NS_CC;

INITIALIZE_READER(CaculateQuickGuideLayer);

std::once_flag _guide_layer_flag;

Scene*  CaculateQuickGuideLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickGuideLayer::createView();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

CaculateQuickGuideLayer * CaculateQuickGuideLayer::createView() 
{
    std::call_once(_guide_layer_flag, []
	{
        REGISTER_CSB_READER(CaculateQuickGuideLayer);
    });
    
	auto view = reinterpret_cast<CaculateQuickGuideLayer*>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickGuideLayer.csb"));
    
	if (view) 
	{
        view->didLoadFromCSB();
        return view;
    }
    
    CC_SAFE_DELETE(view);
    
    return nullptr;
}

void CaculateQuickGuideLayer::didLoadFromCSB()
{
    
}


void CaculateQuickGuideLayer::onCloseButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();

    this->removeFromParent();
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickGuideLayer::onLocateClickCallback(const std::string & callBackName)
{
	std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(CaculateQuickGuideLayer, onCloseButtonClicked),
    };
    
    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}
