#include "WaitingLayer.h"

USING_NS_CC;


WaitingLayer * WaitingLayer::createView() {
	
	return WaitingLayer::create();
}

void WaitingLayer::didLoadFromCSB() {
   
	if (auto indicator = cocos2d::utils::findChild(this, "indicator")) {

		indicator->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
	}
}

void WaitingLayer::onEnter() {

	cocos2d::Layer::onEnter();

}

void WaitingLayer::onExit() {

	cocos2d::Layer::onExit();

}

void WaitingLayer::onSkip(Ref * sender) {

}

void WaitingLayer::onConfirm(Ref * sender) {
	
}

