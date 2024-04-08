#include "CaculateQuickHelperManager.h"
#include "CaculateQuickWaitingLayer.h"
#include <iomanip>
#include <algorithm>
#include "CaculateQuickAnimationManager.h"

USING_NS_CC;

void CaculateQuickHelperManager::disableButton(cocos2d::Ref* sender)
{
	if (auto button = dynamic_cast<ui::Button*>(sender)) {
		button->setTouchEnabled(false);
	}
}

void CaculateQuickHelperManager::showCaculateQuickWaitingLayer()
{
	auto waitView = CaculateQuickWaitingLayer::createView();
	waitView->setName("CaculateQuickWaitingLayer");
	Director::getInstance()->getRunningScene()->addChild(waitView, INT_MAX - 1);
}

float CaculateQuickHelperManager::lerp(float a, float b, float x, float y, float i)
{
	if (a == b) {
		CCLOG("something wrong!");
		return -1;
	}

	return (((i - a) / (b - a)) * (y - x)) + x;
}

void CaculateQuickHelperManager::attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos)
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

		}, StringUtils::format("update_node_position_%d_%d", random(0, 1000), random(0, 100)));

	spine->addChild(node);
}

void CaculateQuickHelperManager::attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
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
	case CaculateQuickHelperManager::PhysicType::BOX:
		phyicBody = PhysicsBody::createBox(node->getContentSize());
		break;
	case CaculateQuickHelperManager::PhysicType::CIRCLE:
		phyicBody = PhysicsBody::createCircle(node->getContentSize().width * 0.5f);
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


void CaculateQuickHelperManager::attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	node->setPosition(offsetPos);

	PhysicsBody* phyicBody = nullptr;

	switch (type)
	{
	case CaculateQuickHelperManager::PhysicType::BOX:
		phyicBody = PhysicsBody::createBox(node->getContentSize());
		break;
	case CaculateQuickHelperManager::PhysicType::CIRCLE:
		phyicBody = PhysicsBody::createCircle(node->getContentSize().width * 0.5f);
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


float CaculateQuickHelperManager::getSpineDuration(spine::SkeletonAnimation* spine, std::string animationName, float defaultDuration)
{
	float delayTime = defaultDuration;

	if (spine)
	{
		if (auto ani = spine->findAnimation(animationName)) {

			delayTime = ani->duration;

		}
	}

	return delayTime;

}

void CaculateQuickHelperManager::addLockLayer(cocos2d::Node* node)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150), visibleSize.width, visibleSize.height);
	node->addChild(layer);

	auto lockButton = cocos2d::ui::Button::create();
	lockButton->ignoreContentAdaptWithSize(false);
	lockButton->setContentSize(visibleSize * 2.0f);
	lockButton->setPressedActionEnabled(true);
	lockButton->setPosition(layer->getContentSize() * 0.5f);
	lockButton->addClickEventListener([=](Ref*) {

		int a = 1;

		a++;

		});

	layer->addChild(lockButton);
}

std::string CaculateQuickHelperManager::getCurrentDate()
{
	std::time_t currentTime = std::time(nullptr);
	std::tm currentDate = *std::localtime(&currentTime);

	std::ostringstream oss;
	oss << std::put_time(&currentDate, "%d-%m-%Y");
	return oss.str();
}

Sprite* CaculateQuickHelperManager::setPhysicsBodyOfAnimByCreateSprite(SkeletonAnimation* animation, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion)
{
	Vec2 pos = Vec2(0, 0);

	Size sizeSprite = Size(0, 0);

	if (animation)
	{
		sizeSprite = animation->getBoundingBox().size;
		pos = sizeSprite / 2;
	}

	auto sprite = Sprite::create();
	sprite->setPosition(pos);

	sprite->setContentSize(sizeSprite);

	auto Enemy1Body = PhysicsBody::createEdgeBox(sizeSprite + size, PHYSICSBODY_MATERIAL_DEFAULT, 2);
	Enemy1Body->setContactTestBitmask(true);
	Enemy1Body->setDynamic(false);
	Enemy1Body->setCollisionBitmask(collisionBitmask);

	if (postion.x != 0 || postion.y != 0)
	{
		sprite->setPosition(postion);
	}

	sprite->setPhysicsBody(Enemy1Body);
	sprite->setName(name);
	Enemy1Body->setName(name);

	animation->addChild(sprite);

	return sprite;
}

void CaculateQuickHelperManager::setPhysicsPolygon(Node* sprite, Size size, int collisionBitmask, std::string name, Vec2* points, int count, cocos2d::Vec2 postion)
{
	auto Enemy1Body = PhysicsBody::createEdgePolygon(points, count, PHYSICSBODY_MATERIAL_DEFAULT, 1);
	Enemy1Body->setContactTestBitmask(true);
	Enemy1Body->setDynamic(false);
	Enemy1Body->setCollisionBitmask(collisionBitmask);
	sprite->setPhysicsBody(Enemy1Body);
	sprite->setName(name);
	Enemy1Body->setName(name);
}

void CaculateQuickHelperManager::setPhysicsPolygonByCreateSprite(Node* node, Size size, int collisionBitmask, std::string name, Vec2* points, int count, cocos2d::Vec2 postion) {
	Vec2 pos = Vec2(0, 0);
	Size sizeSprite = Size(0, 0);
	sizeSprite = node->getContentSize();
	pos = sizeSprite / 2;
	auto sprite = Sprite::create();
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(pos);
	sprite->setContentSize(node->getContentSize());
	auto Enemy1Body = PhysicsBody::createEdgePolygon(points, count, PHYSICSBODY_MATERIAL_DEFAULT, 1);
	Enemy1Body->setContactTestBitmask(true);
	Enemy1Body->setDynamic(false);
	Enemy1Body->setCollisionBitmask(collisionBitmask);

	if (postion.x != 0 || postion.y != 0)
	{
		sprite->setPosition(postion);
	}

	sprite->setPhysicsBody(Enemy1Body);
	sprite->setName(name);
	Enemy1Body->setName(name);

	node->addChild(sprite);
}

Sprite* CaculateQuickHelperManager::setPhysicsBodyByCreateSprite(Node* node, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion)
{
	Vec2 pos = Vec2(0, 0);
	Size sizeSprite = Size(0, 0);
	sizeSprite = node->getContentSize();
	pos = sizeSprite / 2;
	auto sprite = Sprite::create();
	sprite->setPosition(pos);

	sprite->setContentSize(sizeSprite);

	auto Enemy1Body = PhysicsBody::createEdgeBox(sizeSprite + size, PHYSICSBODY_MATERIAL_DEFAULT, 1);

	Enemy1Body->setContactTestBitmask(true);
	Enemy1Body->setDynamic(false);
	Enemy1Body->setCollisionBitmask(collisionBitmask);

	sprite->setPosition(sprite->getPosition() + postion);

	sprite->setPhysicsBody(Enemy1Body);
	sprite->setName(name);
	Enemy1Body->setName(name);

	node->addChild(sprite);

	return sprite;
}

Sprite* CaculateQuickHelperManager::setPhysicsBody(Sprite* node, Size size, int collisionBitmask, std::string name, cocos2d::Vec2 postion, bool isEnableDynamic, int categirBitmask)
{
	Vec2 pos = Vec2(0, 0);
	Size sizeSprite = Size(0, 0);
	sizeSprite = node->getContentSize();
	pos = sizeSprite / 2;

	auto Enemy1Body = PhysicsBody::createEdgeBox(sizeSprite + size, PhysicsMaterial(100, 0, 0), 1);

	Enemy1Body->setDynamic(isEnableDynamic);
	Enemy1Body->setCollisionBitmask(collisionBitmask);
	Enemy1Body->setPositionOffset(Enemy1Body->getPositionOffset() + postion);
	Enemy1Body->setCategoryBitmask(categirBitmask);
	Enemy1Body->setGroup(0);

	node->addComponent(Enemy1Body);
	node->setName(name);
	Enemy1Body->setName(name);

	return node;
}


float CaculateQuickHelperManager::getTimeDelayOfAimation(float delay, SkeletonAnimation* animation, std::string nameAction)
{
	float delayTime = delay;

	if (auto aimation = animation->findAnimation(nameAction))
	{
		delayTime = aimation->duration;
	}
	else if (auto aimation = animation->findAnimation("action"))
	{
		delayTime = aimation->duration;
	}

	return delayTime;
}

std::vector<std::string> CaculateQuickHelperManager::split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

long long CaculateQuickHelperManager::getTimeStampNow() {
	auto now = std::chrono::system_clock::now();
	std::chrono::seconds timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	return timestamp.count();
}

std::string CaculateQuickHelperManager::timestampToDateString(long long timestamp) {
	time_t timestampAsTimeT = static_cast<time_t>(timestamp);
	std::tm* timeinfo = std::localtime(&timestampAsTimeT);
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d:%m/%Y", timeinfo);
	return std::string(buffer);
}

std::string CaculateQuickHelperManager::getTimeToString(int time)
{
	auto mi = (int) (time / 60);
	auto se = time % 60;

	std::string txtMi  = std::to_string(mi);
	std::string txtSe = std::to_string(se);

	if (mi < 10) {
		txtMi = "0" + txtMi;
	}

	if (se < 10) {
		txtSe = "0" + txtSe;
	}

	return txtMi + ":" + txtSe;
}

Vec2 CaculateQuickHelperManager::getPoint(Size sizeCurrent, Vec2 value)
{
	auto x = sizeCurrent.width / 1024;
	value = value * x;
	return value;
}

int CaculateQuickHelperManager::GetTotalNumberCoin()
{
	auto coin = UserDefault::getInstance()->getIntegerForKey(KEY_SAVE_COINT, 0);
	return coin >= 0 ? coin : 0;
}

void CaculateQuickHelperManager::AddNumberCoin(int numberCoinAdd)
{
	auto coinSave = UserDefault::getInstance()->getIntegerForKey(KEY_SAVE_COINT, 0) + numberCoinAdd;
	SaveNumberCoin(coinSave);
}

void CaculateQuickHelperManager::SaveNumberCoin(int numberCoin)
{
	UserDefault::getInstance()->setIntegerForKey(KEY_SAVE_COINT, numberCoin);
}

void CaculateQuickHelperManager::RunAnimNode(Node* txt)
{
	txt->runAction(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(0.25f, 1.5f)), EaseBackOut::create(ScaleTo::create(0.25f, 1.1f))));
}


Animate* CaculateQuickHelperManager::getAnimate(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)\
{
	auto animation = AnimationCache::getInstance()->getAnimation(nameAnim);
	if (animation == nullptr) {
		animation = CaculateQuickAnimationManager::GetInstance()->createAnimation(prefixName, start, end, delay, loop);
		AnimationCache::getInstance()->addAnimation(animation, nameAnim);
	}
	Animate* animate = Animate::create(animation);
	return animate;
}

Sprite* CaculateQuickHelperManager::getAnimateSprite(std::string pathSrpite, std::string nameAnim, const char* prefixName, int start, int end, float delay, int loop)
{
	auto animate = getAnimate(pathSrpite, nameAnim, prefixName, start, end, delay, loop);
	auto sprite = Sprite::create(pathSrpite);
    if(sprite == nullptr)
    {
        sprite =Sprite::createWithSpriteFrameName(pathSrpite);
    }
	sprite->runAction(animate);
	sprite->setName("objectPause_" + nameAnim);
	return sprite;
}


Vec2* CaculateQuickHelperManager::getPointCollider(std::vector<Vec2> vec)
{
	int size = vec.size();
	Vec2* points = new Vec2[size];
	for (int i = 0; i < vec.size(); i++) {
		points[i] = vec[i];
	}
	return points;
}

std::vector<Vec2> CaculateQuickHelperManager::resetPointFishCollider(std::vector<Vec2>& listValue, Vec2 pointAddd)
{
	for (int i = 0; i < listValue.size(); i++)
	{
		listValue[i] += pointAddd;
	}
	return listValue;
}

Vec2 CaculateQuickHelperManager::getThirdPointByX(Vec2 first, Vec2 second, double x) {
	Vec2 third;
	double m = (second.y - first.y) / (second.x - first.x); 
	double b = first.y - m * first.x; 
	third.x = x;
	third.y = m * x + b; 

	return third;
}

Vec2 CaculateQuickHelperManager::getThirdPointByY(Vec2 first, Vec2 second, double y) {
	Vec2 third;
	double m = (second.y - first.y) / (second.x - first.x); 
	double b = first.y - m * first.x; 
	double x = (y - b) / m;
	third.x = x;
	third.y = y;

	return third;
}
