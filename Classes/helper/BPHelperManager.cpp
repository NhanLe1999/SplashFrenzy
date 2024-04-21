#include "BPHelperManager.h"
#include "WaitingLayer.h"
#include "BPAnimationManager.h"
#include <iomanip>

USING_NS_CC;

void BPHelperManager::disableButton(cocos2d::Ref* sender)
{
	if (auto button = dynamic_cast<ui::Button*>(sender)) {

		button->setTouchEnabled(false);
	}
}

void BPHelperManager::showWaitingLayer()
{
	auto waitView = WaitingLayer::createView();
	waitView->setName("WaitingLayer");
	Director::getInstance()->getRunningScene()->addChild(waitView, INT_MAX - 1);
}

float BPHelperManager::lerp(float a, float b, float x, float y, float i)
{
	if (a == b) {
		CCLOG("something wrong!");
		return -1;
	}

	return (((i - a) / (b - a)) * (y - x)) + x;
}

void BPHelperManager::displayToast(const char* text, float duartionSeconds, Node* parent, Color4B color)
{
    auto label = Label::createWithTTF(text, "fonts/arial.ttf", 20);
    label->setPosition(Director::getInstance()->getVisibleSize()/2.f);
    label->setTextColor(color);
    label->enableOutline(color);
    parent->addChild(label, INT_MAX-1);

    ANIMATION_MANAGER->transitionSlideIn(BPAnimationManager::Direction::LEFT, 0.25f, label);

    label->runAction(Sequence::createWithTwoActions(DelayTime::create(duartionSeconds), RemoveSelf::create()));
}
void BPHelperManager::displayToastBottom(const char* text, float duartionSeconds, std::string pathBg, Color4B color)
{
    auto scene = Director::getInstance()->getRunningScene();
    
    scene->removeChildByName("displayToastBottom",true);
   
    auto toast = Sprite::create(pathBg);
    toast->setName("displayToastBottom");
    scene->addChild(toast, INT_MAX-1);

    auto label = Label::createWithTTF(text, "fonts/arial.ttf", 30);
    
    label->setTextColor(color);
    label->enableOutline(color);
    label->setColor(Color3B(255,255,255));
    toast->addChild(label);
    toast->setContentSize(label->getContentSize()+Size(10,10));
    toast->setOpacity(120);
    label->setPosition(toast->getContentSize()/2.f);
    
    label->runAction(FadeOut::create(duartionSeconds*2));
    toast->runAction(Sequence::createWithTwoActions(DelayTime::create(duartionSeconds), RemoveSelf::create()));
    
    toast->setPosition(scene->getContentSize().width/2,label->getContentSize().height+50);
}
void BPHelperManager::displayToastTop(const char* text, float duartionSeconds, std::string pathBg, Color4B color)
{
    auto scene = Director::getInstance()->getRunningScene();
    
    scene->removeChildByName("displayToastBottom",true);
   
    auto toast = Sprite::create(pathBg);
    toast->setName("displayToastBottom");
    scene->addChild(toast, INT_MAX-1);

	auto label = Label::createWithTTF(text, "fonts/arial.ttf", 30);
	
	label->setTextColor(color);
	label->enableOutline(color);
    label->setColor(Color3B(255,255,255));
    toast->addChild(label);
    toast->setContentSize(label->getContentSize()+Size(10,10));
    toast->setOpacity(120);
    label->setPosition(toast->getContentSize()/2.f);
    
    label->runAction(FadeOut::create(duartionSeconds*2));
    toast->runAction(Sequence::createWithTwoActions(DelayTime::create(duartionSeconds), RemoveSelf::create()));
    
    toast->setPosition(scene->getContentSize().width/2,scene->getContentSize().height - 50);
}

void BPHelperManager::attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	spine->schedule([=](float dt) {

		if (auto slot = spine->findSlot(slotName)) {

			node->setRotation(-slot->bone->rotation);

			node->setScaleX(slot->bone->scaleX);

			node->setScaleY(slot->bone->scaleY);

			node->setPosition({ slot->bone->worldX + offsetPos.x ,slot->bone->worldY + offsetPos.y });
		}

	}, StringUtils::format("update_node_position_%d_%d",random(0,1000),random(0,100)));

	spine->addChild(node);
}

void BPHelperManager::attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	node->setPosition(spine->getPosition());

	spine->schedule([=](float dt) {

		if (auto slot = spine->findSlot(slotName)) {

			node->setRotation(-slot->bone->rotation);

			node->setScaleX(slot->bone->scaleX);

			node->setScaleY(slot->bone->scaleY);

			node->setPosition({ slot->bone->worldX + offsetPos.x ,slot->bone->worldY + offsetPos.y });
		}

	}, StringUtils::format("update_node_position_%d_%d", random(0, 1000), random(0, 100)));

	PhysicsBody* phyicBody = nullptr;
	
	switch (type)
	{
	case BPHelperManager::PhysicType::BOX:
		phyicBody =  PhysicsBody::createBox(node->getContentSize());
		break;
	case BPHelperManager::PhysicType::CIRCLE:
		phyicBody =  PhysicsBody::createCircle(node->getContentSize().width*0.5f);
		break;
	default:
		phyicBody = PhysicsBody::createBox(node->getContentSize());
		break;
	}

	phyicBody->setContactTestBitmask(true);
	phyicBody->setCollisionBitmask(physicMask);
	phyicBody->setDynamic(false);

	node->setPhysicsBody(phyicBody);

	spine->addChild(node);
}

void BPHelperManager::createPhysicBody(cocos2d::Node* node, cocos2d::Size nodeSize, int physicMask, PhysicType type, bool isDynamic, float mass, bool isGravity) {
    PhysicsBody* phyicBody = nullptr;

    switch (type)
    {
    case BPHelperManager::PhysicType::BOX:
        phyicBody = PhysicsBody::createBox(node->getContentSize());
        break;
    case BPHelperManager::PhysicType::CIRCLE:
        phyicBody = PhysicsBody::createCircle(node->getContentSize().width * 0.5f);
        break;
    default:
        phyicBody = PhysicsBody::createBox(node->getContentSize());
        break;
    }
    phyicBody->setMass(mass);
    phyicBody->setContactTestBitmask(true);
    phyicBody->setCollisionBitmask(physicMask);
    phyicBody->setDynamic(isDynamic);
    phyicBody->setGravityEnable(isGravity);

    node->setPhysicsBody(phyicBody);
}
void BPHelperManager::attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
    if (!spine || !node) {
        return;
    }

    node->setContentSize(nodeSize);

    node->setPosition(offsetPos);
   
    PhysicsBody* phyicBody = nullptr;
    
    switch (type)
    {
    case BPHelperManager::PhysicType::BOX:
        phyicBody =  PhysicsBody::createBox(node->getContentSize());
        break;
    case BPHelperManager::PhysicType::CIRCLE:
        phyicBody =  PhysicsBody::createCircle(node->getContentSize().width*0.5f);
        break;
    default:
        phyicBody = PhysicsBody::createBox(node->getContentSize());
        break;
    }

    phyicBody->setContactTestBitmask(true);
    phyicBody->setCollisionBitmask(physicMask);
    phyicBody->setDynamic(false);

    node->setPhysicsBody(phyicBody);

    spine->addChild(node);
}
void BPHelperManager::attachNodeToSpineAndSetPhysicWithoutRotation(Sprite* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	node->setPosition(offsetPos);

	PhysicsBody* phyicBody = nullptr;

	switch (type)
	{
		case BPHelperManager::PhysicType::BOX:
			phyicBody =  PhysicsBody::createBox(node->getContentSize());
			break;
		case BPHelperManager::PhysicType::CIRCLE:
			phyicBody =  PhysicsBody::createCircle(node->getContentSize().width*0.5f);
			break;
		default:
			phyicBody = PhysicsBody::createBox(node->getContentSize());
			break;
	}

	phyicBody->setContactTestBitmask(true);
	phyicBody->setCollisionBitmask(physicMask);
	phyicBody->setDynamic(false);

	node->setPhysicsBody(phyicBody);

	spine->addChild(node);
}

float BPHelperManager::getSpineDuration(spine::SkeletonAnimation *spine, std::string animationName, float defaultDuration)
{
    float delayTime = defaultDuration;

    if(spine)
    {
        if (auto ani = spine->findAnimation(animationName)) {

            delayTime = ani->duration;
            
        }
    }
    
    return delayTime;

}

void BPHelperManager::addLockLayer(cocos2d::Node* node)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 255*0.85f), visibleSize.width, visibleSize.height);
    node->addChild(layer);

    auto lockButton = cocos2d::ui::Button::create();
    lockButton->ignoreContentAdaptWithSize(false);
    lockButton->setContentSize(visibleSize*2.0f);
    lockButton->setPressedActionEnabled(true);
    lockButton->setPosition(layer->getContentSize()*0.5f);
    lockButton->addClickEventListener([=](Ref*){
        
        int a=1;
        
        a++;
        
    });
    
    layer->addChild(lockButton);
}

std::string BPHelperManager::getCurrentDate()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm currentDate = *std::localtime(&currentTime);
    
    std::ostringstream oss;
    oss << std::put_time(&currentDate, "%d-%m-%Y");
    return oss.str();
}
long long BPHelperManager::getCurrentTimeSeconds() {
	auto currentTime = std::chrono::system_clock::now();
	auto duration = currentTime.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}
void BPHelperManager::attachPhysicToNode(cocos2d::Node* node, int physicMask,Vec2 size, PhysicType type, bool isDynamic)
{
    if (!node) {
        return;
    }

    PhysicsBody* phyicBody = nullptr;

    switch (type)
    {
        case BPHelperManager::PhysicType::BOX:
            phyicBody =  PhysicsBody::createBox((Size)size);
            break;
        case BPHelperManager::PhysicType::CIRCLE:
            phyicBody =  PhysicsBody::createCircle(size.x*0.5f);
            break;
        default:
            phyicBody = PhysicsBody::createBox((Size)size);
            break;
    }

    phyicBody->setContactTestBitmask(true);
    phyicBody->setCollisionBitmask(physicMask);
    phyicBody->setDynamic(isDynamic);

    node->setPhysicsBody(phyicBody);
}
void BPHelperManager::removeAllChildByTag(Node* parent, int tag) {
    while (parent->getChildByTag(tag))
    {
        auto node = parent->getChildByTag(tag);
        parent->removeChild(node, true);
    }
}

Animate* BPHelperManager::getAnimate(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)\
{
    auto animation = AnimationCache::getInstance()->getAnimation(nameAnim);
    if (animation == nullptr) {
        animation = BPHelperManager::GetInstance()->createAnimation(prefixName, start, end, delay, loop);
        AnimationCache::getInstance()->addAnimation(animation, nameAnim);
    }
    Animate* animate = Animate::create(animation);
    return animate;
}

Sprite* BPHelperManager::getAnimateSprite(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)
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

Animation* BPHelperManager::createAnimation(const char* prefixName, int start, int end, float delay, int loop)
{
    Vector<SpriteFrame*> animFrames;

    for (int i = start; i <= end; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(prefixName, i)->getCString());

        if (frame != nullptr) {
            animFrames.pushBack(frame);
        }
        else {
            auto sprite = Sprite::create(String::createWithFormat(prefixName, i)->getCString());
            if (sprite == nullptr) {
                sprite = Sprite::createWithSpriteFrameName(String::createWithFormat(prefixName, i)->getCString());
            }
            animFrames.pushBack(sprite->getSpriteFrame());
        }
    }

    auto resultAni = Animation::createWithSpriteFrames(animFrames, delay);

    resultAni->setLoops(loop);

    return resultAni;
}

int BPHelperManager::GetTotalNumberCoin(bool isDiamond)
{
    auto coin = UserDefault::getInstance()->getIntegerForKey(isDiamond ? KEY_SAVE_DIAMOND : KEY_SAVE_COINT, 0);
    return coin >= 0 ? coin : 0;
}

void BPHelperManager::AddNumberCoin(int numberCoinAdd, bool isDiamond)
{
    auto coinSave = UserDefault::getInstance()->getIntegerForKey(isDiamond ? KEY_SAVE_DIAMOND : KEY_SAVE_COINT, 0) + numberCoinAdd;
    SaveNumberCoin(coinSave, isDiamond);
}

void BPHelperManager::SaveNumberCoin(int numberCoin, bool isDiamond)
{
    UserDefault::getInstance()->setIntegerForKey(isDiamond ? KEY_SAVE_DIAMOND : KEY_SAVE_COINT, numberCoin);
}