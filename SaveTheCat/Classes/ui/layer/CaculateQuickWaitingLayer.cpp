#include "CaculateQuickWaitingLayer.h"

USING_NS_CC;

INITIALIZE_READER(CaculateQuickWaitingLayer);

std::once_flag _waiting_layer_flag;

CaculateQuickWaitingLayer * CaculateQuickWaitingLayer::createView() {
	
	std::call_once(_waiting_layer_flag, [] {
		REGISTER_CSB_READER(CaculateQuickWaitingLayer);
	});

	auto p = dynamic_cast<CaculateQuickWaitingLayer*>(CSLoader::createNodeWithVisibleSize("csb/ui/layer/CaculateQuickWaitingLayer.csb"));
	if (p) {
		p->didLoadFromCSB();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

void CaculateQuickWaitingLayer::didLoadFromCSB() {
   
	if (auto indicator = cocos2d::utils::findChild(this, "indicator")) {

		indicator->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
	}
}

void CaculateQuickWaitingLayer::onEnter() {

	ui::Layout::onEnter();

}

void CaculateQuickWaitingLayer::onExit() {

	ui::Layout::onExit();

}

void CaculateQuickWaitingLayer::onSkip(Ref * sender) {

}

void CaculateQuickWaitingLayer::onConfirm(Ref * sender) {
	
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickWaitingLayer::onLocateClickCallback(const std::string & callBackName) {
    std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map = {
        CLICK_MAP(CaculateQuickWaitingLayer, onConfirm),
        CLICK_MAP(CaculateQuickWaitingLayer, onSkip),
    };
    
    if (function_map.find(callBackName) != function_map.end()) {
        return function_map.at(callBackName);
    }
	return nullptr;
}
