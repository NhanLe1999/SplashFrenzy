#pragma once

#include "cocos2d.h"

class WaitingLayer : public cocos2d::Layer {

public:

	CREATE_FUNC(WaitingLayer);

	static WaitingLayer* createView();
    
private:

	void onEnter() override;
	
	void onExit() override;
    
    void onConfirm(cocos2d::Ref * sender);

    void onSkip(cocos2d::Ref * sender);
    
	void didLoadFromCSB();

};

