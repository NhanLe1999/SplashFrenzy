#include "BPAnimationManager.h"

USING_NS_CC;

#define MK_RETURN_IF(x, ...)  if(x){ CCLOG("error: return at %s", __FUNCTION__); return __VA_ARGS__;}
#define MK_RETURN_IF_WITH_CONTENT(x,__TYPE__, ...)  if(x){ CCLOG("error: return at %s", __FUNCTION__); __VA_ARGS__ return __TYPE__ ;}

BPAnimationManager::BPAnimationManager()
{
	init();
}

BPAnimationManager::~BPAnimationManager()
{

}

bool BPAnimationManager::init()
{
	_screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	return true;
}


void BPAnimationManager::zoomInEffect(Node * i_node, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	const float k_currentScaleFactor = i_node->getScale();

	i_node->setVisible(false);

	i_node->setScale(0.0f*k_currentScaleFactor);

	i_node->runAction(Sequence::create(DelayTime::create(0.125f), Show::create(), EaseBackOut::create(ScaleTo::create(0.3f, 1.0f*k_currentScaleFactor)), CallFunc::create([=]() {
	
		if (i_callback) {
			i_callback();
		}

	}), nullptr));
}
void BPAnimationManager::runSacleEffect(Node * i_node, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););
	i_node->runAction(Sequence::create(ScaleTo::create(0.5, 1.1), ScaleTo::create(0.5, 0.9), ScaleTo::create(0.5, 1.1), ScaleTo::create(0.5, 0.9), ScaleTo::create(0.5, 1), CallFunc::create([=]() {
	
		if (i_callback) {
			i_callback();
		}

	}), nullptr));
}

void BPAnimationManager::zoomOutEffect(Node * i_node, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	auto spawn = Spawn::createWithTwoActions(FadeOut::create(0.1f), EaseBackOut::create(ScaleTo::create(0.3f, 0.0f)));

	i_node->runAction(Sequence::create(spawn, CallFunc::create([=]() {

		if (i_callback) {
			i_callback();
		}

	}), nullptr));
}

void BPAnimationManager::fadeInEffect(Node * i_node,std::function<void()> i_callback, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	const auto k_currentOpacity = i_node->getOpacity();

	if (auto widget = dynamic_cast<ui::Widget*>(i_node)) {

		widget->setEnabled(false);
	}

	i_node->setOpacity(0);

	i_node->runAction(Sequence::create(FadeTo::create(duration, k_currentOpacity), CallFunc::create([=]() {

		if (i_callback) {
			i_callback();
		}

		if (auto widget = dynamic_cast<ui::Widget*>(i_node)) {

			widget->setEnabled(true);
		}

	}), nullptr));
}

void BPAnimationManager::fadeInEffect(std::vector<Node*> i_nodes, std::function<void()> i_callback, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_nodes.empty(), , if (i_callback) i_callback(););

	for (int i = 0; i < i_nodes.size(); i++) {

		if (auto item = i_nodes.at(i)) {

			fadeInEffect(item, i >= i_nodes.size() - 1 ? i_callback : nullptr, duration);
		}
	}
}

void BPAnimationManager::moveLeftEffect(Node * i_node, std::function<void()> i_callback, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	auto spawn = Spawn::createWithTwoActions(FadeOut::create(duration), Sequence::createWithTwoActions(
		EaseBackOut::create(MoveBy::create(duration*0.5f,Vec2(+_screenSize.width*0.1f,0))),
		EaseBackOut::create(MoveBy::create(duration*0.8f, Vec2(-_screenSize.width*1.0f, 0)))));

	i_node->runAction(Sequence::create(spawn, CallFunc::create([=]() {

		if (i_callback) {
			i_callback();
		}

	}), nullptr));
}

void BPAnimationManager::zoomInZoomOutEffectForever(Node* i_node, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, ,);

	const float k_currentScaleFactor = i_node->getScale();

	const float k_duration = duration / 4.0f;

	i_node->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(k_duration, k_currentScaleFactor + 0.1f), ScaleTo::create(k_duration, k_currentScaleFactor), ScaleTo::create(k_duration, k_currentScaleFactor + 0.1f), ScaleTo::create(k_duration, k_currentScaleFactor), nullptr)));
}

void BPAnimationManager::zoomInZoomOutEffect(Node * i_node, std::function<void()> i_callback, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	const float k_currentScaleFactor = i_node->getScale();

	const float k_duration = duration / 4.0f;

	i_node->runAction(Sequence::create(ScaleTo::create(k_duration, k_currentScaleFactor + 0.1f), ScaleTo::create(k_duration, k_currentScaleFactor), ScaleTo::create(k_duration, k_currentScaleFactor + 0.1f), ScaleTo::create(k_duration, k_currentScaleFactor), CallFunc::create([i_callback]() {
		if (i_callback) {
			i_callback();
		}
	}), nullptr));
}

void BPAnimationManager::zoomInZoomOutEffect(std::vector<Node*> i_nodes, std::function<void()> i_callback, float duration)
{
	MK_RETURN_IF_WITH_CONTENT(i_nodes.empty(), , if (i_callback) i_callback(););

	for (int i = 0; i < i_nodes.size(); i++) {

		if (auto item = i_nodes.at(i)) {

			zoomInZoomOutEffect(item, i >= i_nodes.size() - 1 ? i_callback : nullptr, duration);
		}
	}
}

void BPAnimationManager::fadeInAndZoomInEffectForNodes(std::vector<Node*> i_nodes , float fadeInZommInDuration , float fadeInDurationBetweenItems , std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_nodes.empty(), , if (i_callback) i_callback(););

	for (int i = 0; i < i_nodes.size(); i++) {

		if (auto item = i_nodes.at(i)) {

			if (auto  langbg = utils::findChild(item, "lang_bg")) {
				langbg->setLocalZOrder(100);
			}

			const auto k_currentScale = item->getScale();
			const auto k_currentOpacity = item->getOpacity();

			item->setOpacity(0);
			item->setScale(0.5f*k_currentScale);

			if (i >= i_nodes.size() - 1) { //end

				item->runAction(Sequence::create
				(
					DelayTime::create((i + 1)*(fadeInDurationBetweenItems / i_nodes.size())),
					EaseIn::create(Spawn::createWithTwoActions(FadeTo::create(fadeInZommInDuration, k_currentOpacity), ScaleTo::create(fadeInZommInDuration, 1.0f*k_currentScale)), 2),
					CallFunc::create([i_callback](){
				
						if (i_callback) {
							i_callback();
						}

					}),
					nullptr
				));

			} else {
				item->runAction(Sequence::createWithTwoActions
				(
					DelayTime::create((i + 1)*(fadeInDurationBetweenItems / i_nodes.size())),
					EaseIn::create(Spawn::createWithTwoActions(FadeTo::create(fadeInZommInDuration, k_currentOpacity), ScaleTo::create(fadeInZommInDuration, 1.0f*k_currentScale)), 2)
				));
			}
	
		}
	}
}

void BPAnimationManager::transitionSlideIn(Direction i_direction, float i_duration, std::vector<Node*> i_nodes, std::function<void()> i_callback)
{
	for (int i = 0; i < i_nodes.size(); i++) {

		transitionSlideIn(i_direction, i_duration, i_nodes.at(i), (i == i_nodes.size() -1) ? i_callback:nullptr);
	}
}

void BPAnimationManager::transitionSlideIn(Direction i_direction, float i_duration, std::vector<std::pair<std::vector<Node*>, float>> i_nodesAndDelaytime, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT( i_nodesAndDelaytime.empty(), ,if (i_callback) i_callback(););

	cocos2d::Vector<FiniteTimeAction*> actions;

    for (int i = 0; i <i_nodesAndDelaytime.size();i++ ) {

        auto info = i_nodesAndDelaytime.at(i);
        
        for (int j = 0; j < info.first.size(); j++) {
            
            if(auto node = info.first.at(j)) {
                
                if(!node) {
                    continue;
                }
                
                const auto k_currentPosition = node->getPosition();

                switch (i_direction)
                {
                case BPAnimationManager::Direction::LEFT:
                        node->setPositionX(k_currentPosition.x + _screenSize.width);
                    break;
                case BPAnimationManager::Direction::RIGHT:
                        node->setPositionX(k_currentPosition.x - _screenSize.width);
                    break;
                case BPAnimationManager::Direction::TOP:
                        node->setPositionY(k_currentPosition.y - _screenSize.height);
                    break;
                case BPAnimationManager::Direction::BOTTOM:
                        node->setPositionY(k_currentPosition.y + _screenSize.height);
                    break;
                default:
                    break;
                }

                auto moveAction = MoveTo::create(i_duration, k_currentPosition);

                if(i == i_nodesAndDelaytime.size()-1 && j == info.first.size() - 1) {
                    
                    auto sequenceAction    = Sequence::create
                    (
                        DelayTime::create(info.second*i),
                        EaseOut::create(moveAction, 2.0f),
                        CallFunc::create([=]() {
                            if (i_callback) {
                                i_callback();
                            }
                        }),
                        nullptr
                    );
                    node->runAction(sequenceAction);

                }  else {
                    auto sequenceAction    = Sequence::create
                    (
                        DelayTime::create(info.second*i),
                        EaseOut::create(moveAction, 2.0f),
                        nullptr
                    );
                    node->runAction(sequenceAction);
                }
            }
        }
	}
}

void BPAnimationManager::transitionSlideIn(Direction i_direction, float i_duration, Node * i_node, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	const auto k_currentPosition = i_node->getPosition();

	switch (i_direction)
	{
	case BPAnimationManager::Direction::LEFT:
		i_node->setPositionX(k_currentPosition.x + _screenSize.width);
		break;
	case BPAnimationManager::Direction::RIGHT:
		i_node->setPositionX(k_currentPosition.x - _screenSize.width);
		break;
	case BPAnimationManager::Direction::TOP:
		i_node->setPositionY(k_currentPosition.y - _screenSize.height);
		break;
	case BPAnimationManager::Direction::BOTTOM:
		i_node->setPositionY(k_currentPosition.y + _screenSize.height);
		break;
	default:
		break;
	}

	auto moveAction = MoveTo::create(i_duration, k_currentPosition);

	auto sequenceAction	= Sequence::create
	(
		EaseBackInOut::create(moveAction),
		CallFunc::create([=]() {
			if (i_callback) {
				i_callback();
			}
		}),
		nullptr
	);
	i_node->runAction(sequenceAction);
}

void BPAnimationManager::transitionSlideOut(Direction i_direction, float i_duration, std::vector<Node*> i_nodes, std::function<void()> i_callback)
{
	for (int i = 0; i < i_nodes.size(); i++) {

			transitionSlideOut(i_direction, i_duration, i_nodes.at(i), (i == i_nodes.size() - 1) ? i_callback : nullptr);
	}
}

void BPAnimationManager::transitionSlideOut(Direction i_direction, float i_duration, std::vector<std::pair<std::vector<Node*>, float>> i_nodesAndDelaytime, std::function<void()> i_callback)
{
    MK_RETURN_IF_WITH_CONTENT( i_nodesAndDelaytime.empty(), ,if (i_callback) i_callback(););

    cocos2d::Vector<FiniteTimeAction*> actions;

    for (int i = 0; i <i_nodesAndDelaytime.size();i++ ) {

        auto info = i_nodesAndDelaytime.at(i);
        
        for (int j = 0; j < info.first.size(); j++) {
            
            if(auto node = info.first.at(j)) {
                
                if(!node) {
                    continue;
                }
                
                ActionInterval* moveAction = nullptr;

                switch (i_direction)
                {
                case BPAnimationManager::Direction::LEFT:
                    moveAction = MoveTo::create(i_duration, Vec2(-_screenSize.width,0));
                    break;
                case BPAnimationManager::Direction::RIGHT:
                    moveAction = MoveBy::create(i_duration,  Vec2(+_screenSize.width, 0));
                    break;
                case BPAnimationManager::Direction::TOP:
                    moveAction = MoveBy::create(i_duration, Vec2(0, +_screenSize.height));
                    break;
                case BPAnimationManager::Direction::BOTTOM:
                    moveAction = MoveBy::create(i_duration, Vec2(0, -_screenSize.height));
                    break;
                default:
                    break;
                }

                if(i == i_nodesAndDelaytime.size()-1 && j == info.first.size() - 1) {
                    
                    auto sequenceAction = Sequence::create
                    (
                        DelayTime::create(info.second*i),
                        EaseOut::create(moveAction, 2.0f),
                        CallFunc::create([=]() {
                            if (i_callback) {
                                i_callback();
                            }
                        }),
                        nullptr
                    );
                    node->runAction(sequenceAction);

                } else {
                    auto sequenceAction    = Sequence::create
                    (
                        DelayTime::create(info.second*i),
                        EaseOut::create(moveAction, 2.0f),
                        nullptr
                    );
                    node->runAction(sequenceAction);
                }
            }
        }
    }
}

void BPAnimationManager::transitionSlideOut(Direction i_direction, float i_duration, Node * i_node, std::function<void()> i_callback)
{
	MK_RETURN_IF_WITH_CONTENT(i_node == nullptr, , if (i_callback) i_callback(););

	ActionInterval* moveAction = nullptr;

	switch (i_direction)
	{
	case BPAnimationManager::Direction::LEFT:
		moveAction = MoveBy::create(i_duration, Vec2(-_screenSize.width,0));
		break;
	case BPAnimationManager::Direction::RIGHT:
		moveAction = MoveBy::create(i_duration,  Vec2(+_screenSize.width, 0));
		break;
	case BPAnimationManager::Direction::TOP:
		moveAction = MoveBy::create(i_duration, Vec2(0, +_screenSize.height));
		break;
	case BPAnimationManager::Direction::BOTTOM:
		moveAction = MoveBy::create(i_duration, Vec2(0, -_screenSize.height));
		break;
	default:
		break;
	}

	if (moveAction) {

		auto sequenceAction = Sequence::create
		(
			EaseOut::create(moveAction, 2.0f),
			CallFunc::create([=]() {
			if (i_callback) {
				i_callback();
			}
		}),
			nullptr
			);
		i_node->runAction(sequenceAction);

	} else {
		if (i_callback) {
			i_callback();
		}
	}
}

void BPAnimationManager::popupCustomAnimation(cocos2d::Node* popupBackground,  ActionType actionType, float actionTime, std::function<void()> callback ) {

	MK_RETURN_IF(!popupBackground);

	if (actionType == ActionType::SHOW) {

		popupBackground->setRotation(70.0f);
		popupBackground->setOpacity(0.0f);

		auto spawnAction = Spawn::createWithTwoActions(FadeIn::create(actionTime), EaseBackInOut::create(RotateTo::create(actionTime, 0.0f)));

		popupBackground->runAction(Sequence::createWithTwoActions(spawnAction, CallFunc::create([=]() {

			if (callback) {
				callback();
			}

		})));
	}
	else
	{

		auto spawnAction = Spawn::create(FadeOut::create(actionTime), EaseBackInOut::create(RotateTo::create(actionTime, -180.0f)), ScaleTo::create(actionTime, 0.0f), nullptr);

		popupBackground->runAction(Sequence::createWithTwoActions(spawnAction, CallFunc::create([=]() {

			if (callback) {
				callback();
			}

		})));
	}
}

Animation* BPAnimationManager::createAnimation(const char* prefixName, int start, int end, float delay, std::string lastFrame)
{
	Vector<SpriteFrame*> animFrames;
	
	for (int i = start; i <= end; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());

		if (frame != nullptr)
		{
			animFrames.pushBack(frame);
		}
	}
	
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(lastFrame));

	return Animation::createWithSpriteFrames(animFrames, delay);
}

cocos2d::Animation * BPAnimationManager::createAnimationWithLoop(const char * prefixName, int start, int end, float delay)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = start; i <= end; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());
		
		if (frame != nullptr)
		{
			animFrames.pushBack(frame);
		}
	}

	auto resultAni = Animation::createWithSpriteFrames(animFrames, delay);
	
	resultAni->setLoops(-1);

	return resultAni;
}

Animation* BPAnimationManager::createAnimation(const char* prefixName, int start, int end, float delay, int loop )
{
	Vector<SpriteFrame*> animFrames;

	for (int i = start; i <= end; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());
		
		if (frame != nullptr) {
			animFrames.pushBack(frame);
		} else {
			auto sprite = Sprite::create(String::createWithFormat(prefixName, i)->getCString());
			animFrames.pushBack(sprite->getSpriteFrame());
		}
	}

	auto resultAni = Animation::createWithSpriteFrames(animFrames, delay);

	resultAni->setLoops(loop);

	return resultAni;
}

Animate* BPAnimationManager::getAnimate(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)\
{
	auto animation = AnimationCache::getInstance()->getAnimation(nameAnim);
	if (animation == nullptr) {
		animation = BPAnimationManager::GetInstance()->createAnimation(prefixName, start, end, delay, loop);
		AnimationCache::getInstance()->addAnimation(animation, nameAnim);
	}
	Animate* animate = Animate::create(animation);
	return animate;
}

Sprite* BPAnimationManager::getAnimateSprite(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)
{
	auto animate = getAnimate(pathSrpite, nameAnim, prefixName, start, end, delay, loop);
	auto sprite = Sprite::create(pathSrpite);
	if (sprite == nullptr)
	{
		sprite = Sprite::createWithSpriteFrameName(pathSrpite);
	}
	sprite->runAction(animate);
	sprite->setName("objectPause_" + nameAnim);
	return sprite;
}

void BPAnimationManager::runShakingAction(cocos2d::Node* node, int actionTag, std::function<void()> i_callback)
{
	if (!node) {
		return;
	}

	auto shaking = node->getActionByTag(actionTag);

	if (!shaking) {

		//SOUND_MANAGER->playWallEffect();

		auto shakingAction = Sequence::create(
			MoveBy::create(0.0428571429, { 10,10 }),
			MoveBy::create(0.0428571429, { -10,-10 }),
			MoveBy::create(0.0428571429, { -10,-10 }),
			MoveBy::create(0.0428571429, { +10,+10 }),
			MoveBy::create(0.0428571429, { -10,0 }),
			MoveBy::create(0.0428571429, { +20,0 }),
			MoveBy::create(0.0428571429, { -10,0 }),
			CallFunc::create([=]() {
				if (i_callback) i_callback();
				}),
			nullptr);

		shakingAction->setTag(actionTag);

		node->runAction(shakingAction);
	}
}
