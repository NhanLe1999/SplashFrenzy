#include "CaculateQuickGameScene.h"
#include "CaculateQuickHelperManager.h"
#include "spine/Animation.h"
#include "CaculateQuickPauseLayer.h"
#include "CaculateQuickGameOverLayer.h"
#include "CaculateQuickAnimationManager.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickWinLayer.h"
#include "CaculateQuickShopLayer.h"
#include "CaculateQuickPhysicsShapeCache.h"
#include "CaculateQuickSettingLayer.h"
#include "MySlider.h"

USING_NS_CC;

#define TAG_COIN 321

#define TAG_BOX_CLICK 3
#define TAG_BOX_NO_CLICK 4


#define key_save_number_allow "key_save_number_allow_%d"
#define key_save_number_answer "key_save_number_answer_%d"

#define TIME_SKILL 10

#define TYPE_NUM_1 1
#define TYPE_NUM_2 2
#define TYPE_Allow 3
#define TYPE_NUM_EQUAL 4
#define TYPE_NUM_RESULT 5

#define TYPE_NUM_ANSWER 6

#define COLOR_ERROR cocos2d::Color3B::RED
#define COLOR_NORMAL cocos2d::Color3B(96, 96, 96)
#define COLOR_CORRECT cocos2d::Color3B::WHITE

#define TAG_DEFAULT 99999

INITIALIZE_READER(CaculateQuickGameScene);

std::once_flag _game_scene;

Scene *CaculateQuickGameScene::createScene()
{
    auto scene = Scene::createWithPhysics();

    if (scene)
    {
       scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        auto view = CaculateQuickGameScene::createView();
        view->setPhysicsWorld(scene->getPhysicsWorld());
        view->setPosition(Director::getInstance()->getVisibleOrigin());
        view->didLoadFromCSB();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

CaculateQuickGameScene *CaculateQuickGameScene::createView()
{
    std::call_once(_game_scene, []
                   { REGISTER_CSB_READER(CaculateQuickGameScene); });

    auto view = reinterpret_cast<CaculateQuickGameScene *>(CSLoader::createNodeWithVisibleSize("csb/ui/scene/CaculateQuickGameScene.csb"));

    if (view)
    {
        return view;
    }

    CC_SAFE_DELETE(view);

    return nullptr;
}

void CaculateQuickGameScene::didLoadFromCSB()
{
    _screenSize = Director::getInstance()->getVisibleSize();
    this->setName("CaculateQuickGameScene");
    std::vector<int> ListMap = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,19,13,2,9,22,23,27,4,21,3,1,10,26,24,8,0,16,15,14,7,5,11,20,18,17,25,6,12,0,23,11,17,1,16,12,21,27,6,13,2,25,8,7,18,15,9,14,20,24,22,19,4,10,3,26,5,1,10,21,24,19,17,7,27,13,4,25,18,14,0,5,6,12,9,2,11,26,16,8,20,15,3,22,23,4,5,24,14,20,6,16,12,27,23,1,3,9,2,26,7,17,19,0,15,11,13,22,8,21,10,18,25,27,1,7,21,13,24,6,19,22,26,0,2,9,4,11,16,10,23,3,15,18,25,8,17,14,12,20,5,1,2,16,7,26,9,6,24,13,4,10,23,15,20,22,19,0,21,25,27,18,8,17,12,11,5,3,14,17,20,1,12,18,15,19,23,26,21,2,6,5,27,14,7,13,10,25,9,22,11,3,0,24,4,8,16,5,1,13,23,20,3,18,26,8,15,4,12,25,6,27,17,19,16,21,24,14,2,22,9,11,0,10,7,14,1,10,21,6,8,19,12,22,23,25,13,2,3,0,16,17,5,15,9,7,27,24,26,4,11,20,18,7,12,27,26,20,17,9,0,11,6,2,22,10,3,14,25,23,8,4,21,1,24,13,18,19,5,15,16,26,25,12,22,21,23,14,0,9,2,10,6,5,27,18,19,15,3,20,1,8,7,17,24,11,16,13,4,5,22,10,3,20,24,23,12,17,21,15,11,0,13,14,9,7,27,1,26,19,18,16,6,2,8,25,4,13,0,22,25,12,8,14,6,20,3,5,23,7,16,18,27,11,10,4,21,15,26,9,1,2,19,17,24,21,22,7,27,18,4,20,8,13,19,3,15,26,16,23,1,6,0,12,11,25,14,2,17,24,5,10,9,5,23,12,10,20,26,8,21,17,7,19,11,16,22,0,15,2,24,13,14,6,9,27,1,25,18,4,3,0,16,3,9,12,21,24,11,15,22,5,20,1,14,13,7,6,17,2,19,8,23,10,27,26,25,4,18,11,22,9,12,24,10,8,27,16,18,26,13,15,2,17,4,5,19,21,20,6,0,7,25,3,1,23,14,4,18,8,13,11,14,25,7,19,21,0,24,26,6,22,9,23,16,1,27,12,3,17,2,5,20,15,10,12,21,0,19,25,20,23,2,27,17,14,11,9,26,8,16,5,15,4,3,22,6,18,24,1,7,13,10,10,17,0,3,9,8,21,1,2,22,26,24,19,16,27,6,18,23,5,25,11,13,12,20,7,15,4,14,20,0,10,15,4,14,16,1,3,2,18,17,5,23,21,11,22,26,7,25,12,6,19,9,24,27,13,8,18,23,16,9,6,13,14,5,26,7,19,0,27,21,4,10,20,11,15,24,22,2,17,1,25,3,8,12,0,5,14,19,3,10,27,12,6,4,25,17,8,20,13,16,26,18,23,1,15,22,11,24,21,7,9,2,6,22,16,3,26,1,8,4,18,24,27,13,2,17,9,20,21,25,23,12,14,11,0,7,15,10,5,19,23,24,14,13,22,8,20,25,1,2,27,11,21,19,15,12,18,7,0,10,9,3,16,26,4,6,5,17,3,8,17,19,21,2,16,6,14,20,4,27,26,11,15,12,22,18,13,10,25,9,24,5,1,0,7,23,24,20,18,13,23,2,7,22,16,15,8,0,10,1,19,5,11,27,12,9,6,3,25,17,4,21,26,14,26,4,11,2,14,27,24,15,12,6,22,25,8,10,17,21,13,18,23,20,1,16,9,7,5,3,19,0,27,20,4,1,11,2,17,0,24,12,10,7,6,22,9,16,8,26,15,13,23,14,18,19,5,3,25,21,25,12,18,6,22,15,9,24,23,14,7,11,1,10,16,5,2,20,17,0,19,26,13,3,27,8,21,4,20,16,9,7,19,11,17,4,8,21,3,12,24,0,26,23,15,13,6,18,25,27,5,10,14,2,1,22,18,3,10,21,9,27,11,24,26,4,6,12,19,16,17,22,0,7,5,8,23,20,2,13,1,14,15,25,27,10,2,9,4,12,13,16,0,11,1,18,14,20,23,22,19,8,24,6,15,17,21,3,25,26,7,5,20,16,6,23,8,11,10,0,27,15,19,14,13,2,26,21,5,22,25,3,24,12,17,18,9,7,4,1,5,17,1,11,13,2,22,21,0,7,19,3,27,24,10,12,16,9,8,4,23,14,6,18,26,20,15,25,23,6,14,24,1,4,27,2,8,21,0,25,18,16,11,10,7,5,17,26,22,19,13,12,9,20,3,15,21,12,10,25,24,23,4,2,26,17,7,9,20,19,14,11,3,22,8,13,6,27,5,0,18,1,15,16,25,6,1,3,4,9,23,16,5,12,11,8,14,0,7,26,24,21,17,13,10,27,15,19,18,2,20,22,10,20,1,23,6,7,9,2,8,12,24,16,5,21,0,18,27,11,19,17,3,14,15,26,13,22,4,25,6,24,19,8,20,11,17,0,5,25,14,15,27,22,9,1,3,10,18,16,2,23,21,4,13,12,7,26,27,15,24,14,22,11,12,6,18,0,20,3,4,26,7,5,25,23,2,17,10,21,16,9,19,1,13,8,25,11,2,1,5,10,9,3,0,7,15,20,22,4,12,6,21,14,27,23,17,26,24,18,16,13,8,19,2,10,25,16,8,20,26,0,6,1,12,23,11,4,5,27,14,22,17,3,18,24,19,7,9,15,21,13,27,10,17,15,7,21,4,26,6,1,0,16,18,19,11,2,9,3,14,20,22,25,5,12,24,13,8,23,13,25,20,7,15,14,6,4,24,10,21,27,19,1,17,26,22,8,12,3,23,2,11,18,5,9,0,16,27,7,16,2,6,24,0,9,3,26,4,18,1,12,8,25,13,10,23,17,19,14,5,20,21,15,22,11,12,13,27,4,11,24,9,1,3,15,20,14,26,21,10,18,6,16,2,22,23,17,7,0,19,5,8,25,13,14,12,5,7,26,8,21,27,4,10,2,15,6,20,9,18,24,25,19,23,17,1,11,0,16,3,22,9,19,11,26,5,23,22,13,21,1,15,17,0,25,8,7,24,4,18,10,2,20,12,14,16,3,6,27,24,3,21,7,27,17,9,23,4,0,18,1,20,26,16,2,25,22,19,13,11,6,8,12,10,15,5,14 };
    SOUND_MANAGER->playMainMenuMusic(true);
    _screenSize = Director::getInstance()->getVisibleSize();
    UserDefault::getInstance()->setBoolForKey("key_is_play_anim_swip", false);

    _currentLevelID = UserDefault::getInstance()->getIntegerForKey(KEY_CURENT_LEVEL, 1);

    SetUpdataLevel();
    SetDataCurrentLevel(_currentLevelID - 1);

    if (auto txtLv = utils::findChild<ui::Text*>(this, "txt_level"))
    {
        txtLv->setString(std::to_string(_currentLevelID));
    }

    auto root_layout = utils::findChild(this, "root_layout");

    auto path = cocos2d::StringUtils::format("map/title_map/map_%d.tmx", 2);
    _tileMap = TMXTiledMap::create(path);
    _tileMap->setAnchorPoint(Vec2(0, 0));
    _tileMap->setName("objectPause__tileMap");
    auto sizeMap = _tileMap->getContentSize();
    _tileMap->setPosition(Vec2(sizeMap.width / 2, sizeMap.height / 2));
    this->addChild(_tileMap, 10000);
   

    _character = Sprite::create("BlackpinkIsland/character/PTModelSprite_ID58592.png");
    _character->setPosition(Vec2(_screenSize / 2));
    _tileMap->addChild(_character);
    RunActionCharator(Anim::COIN);

    PhysicsShapeCache::getInstance()->setBodyOnSprite("nv_1", _character, COLLISION_NV);

    getGroupNameByPoint("tuong", 88);

    cocos2d::Follow* followAction = cocos2d::Follow::create(_character, Rect(0, 0, sizeMap.width / 2, _screenSize.height));
    followAction->setTag(9090);
    _tileMap->stopActionByTag(9090);
    _tileMap->runAction(followAction);
    _physicSceneWorld->setGravity(Vec2(0, -980));

    cocos2d::Follow* followAction1 = cocos2d::Follow::create(this);
    auto root_layout1 = utils::findChild(this, "root_layout");
    root_layout1->runAction(followAction1);
    
    cocos2d::Follow* followAction2 = cocos2d::Follow::create(this);
    auto root_game_play = utils::findChild(this, "root_game_play");
    root_game_play->runAction(followAction2);


    //_character->getPhysicsBody()->setContactTestBitmask(true);
}

void CaculateQuickGameScene::getGroupNameByPoint(std::string name, int collison)
{
    auto group = _tileMap->objectGroupNamed(name);

    if (!group)
    {
        return;
    }

    auto listValuOfGroup = group->getObjects();

    for (int i = 0; i < listValuOfGroup.size(); i++)
    {
        auto value = listValuOfGroup[i];
        auto k1 = value.asValueMap();

        auto x = k1["x"].asFloat();
        auto y = k1["y"].asFloat();

        auto width = k1["width"].asFloat();

        auto height = k1["height"].asFloat();

        Sprite* sprite = nullptr;

        if (name == "tuong") {
            sprite = Sprite::create("BlackpinkIsland/ground/ground_world_1/bis_object_ground_world_1_8.png");
            sprite->setAnchorPoint(Point(0.5, 0));
            sprite->setPosition(cocos2d::Vec2(x, y) + Vec2(width / 2, height));
            sprite->stopAllActions();
            sprite->setTag(9);
            sprite->setScale(0.5f);
            PhysicsShapeCache::getInstance()->setBodyOnSprite("tuong", sprite, 22);
        }

        if (sprite == nullptr) {
            continue;
        }


        _tileMap->addChild(sprite);

        CCLOG("%f, %f", x, y);

        auto listener = EventListenerKeyboard::create();
        listener->onKeyPressed = CC_CALLBACK_2(CaculateQuickGameScene::onKeyPressed, this);
        listener->onKeyReleased = CC_CALLBACK_2(CaculateQuickGameScene::onKeyReleased, this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    }
}

void CaculateQuickGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    float x = 200, y = 550;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        CCLOG("Up arrow key is pressed.");
        _character->getPhysicsBody()->setVelocity(Vec2(_character->getPhysicsBody()->getVelocity().x, y));
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        CCLOG("Down arrow key is pressed.");
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _character->getPhysicsBody()->setVelocity(Vec2(-x, _character->getPhysicsBody()->getVelocity().y));
        CCLOG("Left arrow key is pressed.");
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        CCLOG("Right arrow key is pressed.");
        _character->getPhysicsBody()->setVelocity(Vec2(x, _character->getPhysicsBody()->getVelocity().y));
        break;
    default:
        break;
    }
}

void CaculateQuickGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        CCLOG("Up arrow key is released.");
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        CCLOG("Down arrow key is released.");
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        CCLOG("Left arrow key is released.");
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        CCLOG("Right arrow key is released.");
        break;
    default:
        break;
    }
}

void CaculateQuickGameScene::RunActionCharator(Anim anim)
{
    auto anim1 = HELPER_MANAGER->getAnimate("BlackpinkIsland/character/PTModelSprite_ID58592.png",
        "FROG_RELAX", "BlackpinkIsland/character/PTModelSprite_ID%d.png", 58592, 58602, 0.1f, -1);
    _character->setTag(999);
    _character->stopAllActions();
    _character->runAction(anim1);
}

void CaculateQuickGameScene::SetUpdataLevel()
{

}

void CaculateQuickGameScene::SetDataCurrentLevel(int level_id)
{
    /*if (level_id > _levels.size())
    {
        int levelId = cocos2d::random(0, (int)_levels.size() - 1);
        _currentLevelConfig = _levels[levelId];
    }
    else {
        _currentLevelConfig = _levels[level_id];
    }*/
}

void CaculateQuickGameScene::OnUpdateNumSkillGame()
{
    _numSkillHammer = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_HAMMER, 3);
    _numSkillKhien = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_KHIEN, 3);
    _numSkillFrog = UserDefault::getInstance()->getIntegerForKey(KEY_SKILL_FROG, 3);
    _score = HELPER_MANAGER->GetTotalNumberCoin();

    if (_numSkillHammer <=0)
    {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_1"))
        {
            btn->setTouchEnabled(false);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_fixer_none.png");
        }
    }
    else if (!_isUseSkillHammer) {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_1"))
        {
            btn->setTouchEnabled(true);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_fixer.png");
        }
    }

    if (_numSkillKhien <= 0)
    {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_2"))
        {
            btn->setTouchEnabled(false);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_sheild_none.png");
        }
    }
    else if (!_isUseSkillKhien) {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_2"))
        {
            btn->setTouchEnabled(true);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_sheild.png");
        }
    }

    if (_numSkillFrog <= 0)
    {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_3"))
        {
            btn->setTouchEnabled(false);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_ruler_none.png");
        }
    }
    else if(!_isUseSkillFrog) {
        if (auto btn = utils::findChild<ui::Button*>(this, "skin_3"))
        {
            btn->setTouchEnabled(true);
            btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_ruler.png");
        }
    }

    updateScore(0);

    UpdateTextSkillHammer();
    UpdateTextSkillFrog();
    UpdateTextSkillKhien();
}

void CaculateQuickGameScene::updateScore(int scoreAdd)
{
    HELPER_MANAGER->AddNumberCoin(scoreAdd);
    _score += scoreAdd;
    updateLabel("txt_score", std::to_string(_score));
}

void CaculateQuickGameScene::onSkillHammer(cocos2d::Ref* sender)
{
    if (_numSkillHammer <= 0) {
        return;
    }
    _numSkillHammer--;
    _isUseSkillHammer = true;
    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_HAMMER, _numSkillHammer);
    auto btn = dynamic_cast<Button*>(sender);
    btn->setTouchEnabled(false);
    btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_fixer_none.png");


    SOUND_MANAGER->playClickEffect();
    //_frog->unschedule("delay_OnCollisionFrogAnGoMuc");
    UpdateTextSkillHammer();
}

void CaculateQuickGameScene::onSkillKhien(cocos2d::Ref* sender)
{
    if (_numSkillKhien <= 0) {
        return;
    }
    _numSkillKhien--;
    _isUseSkillKhien = true;

    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_KHIEN, _numSkillKhien);
    auto btn = dynamic_cast<Button*>(sender);
    btn->setTouchEnabled(false);
    btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_sheild_none.png");

    SOUND_MANAGER->playClickEffect();
    UpdateTextSkillKhien();
}

void CaculateQuickGameScene::onSkillFrog(cocos2d::Ref* sender)
{
    if (_numSkillFrog <= 0) {
        return;
    }
    _isUseSkillFrog = true;
    _numSkillFrog--;
    UserDefault::getInstance()->setIntegerForKey(KEY_SKILL_FROG, _numSkillFrog);
    auto btn = dynamic_cast<Button*>(sender);
    btn->setTouchEnabled(false);
    btn->loadTextureNormal("CaculateQuick/ui/sb_ui_item_ruler_none.png");

    SOUND_MANAGER->playClickEffect();
    _isUseSkillTime = true;
    UpdateTextSkillFrog();
}   

void CaculateQuickGameScene::onShopButtonClicked(cocos2d::Ref* sender)
{
    this->onGamePause();
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickShopLayer::createView();
    this->addChild(view);
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void CaculateQuickGameScene::UpdateTextSkillHammer()
{
    updateLabel("txt_skin_star", std::to_string(_numSkillHammer));
}

void CaculateQuickGameScene::UpdateTextSkillKhien()
{
    updateLabel("txt_skin_reset", std::to_string(_numSkillKhien));
}

void CaculateQuickGameScene::UpdateTextSkillFrog()
{
    updateLabel("txt_skin_find", std::to_string(_numSkillFrog));
}

cocos2d::ui::Widget::ccWidgetClickCallback CaculateQuickGameScene::onLocateClickCallback(const std::string &callBackName)
{
    std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
        {
            CLICK_MAP(CaculateQuickGameScene, onPauseButtonClicked),
            CLICK_MAP(CaculateQuickGameScene, onSkillHammer),
            CLICK_MAP(CaculateQuickGameScene, onSkillKhien),
            CLICK_MAP(CaculateQuickGameScene, onSkillFrog),
            CLICK_MAP(CaculateQuickGameScene, onShopButtonClicked),
        };

    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}

void CaculateQuickGameScene::updateLabel(std::string labelName, std::string data)
{
    if (auto scoreText = utils::findChild<cocos2d::ui::Text*>(this, labelName)) {
        scoreText->stopAllActions();
        scoreText->setString(data);
        scoreText->runAction(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(0.25f, 1.5f)), EaseBackOut::create(ScaleTo::create(0.25f, 1.1f))));
    }
}

Sprite* CaculateQuickGameScene::GetAnim(Anim anim)
{
    Sprite* sprite = nullptr;

    switch (anim)
    {
    case Anim::COIN:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/coin/animtion_coin0.png",
            "COIN", "CaculateQuick/animation/coin/animtion_coin%d.png", 0, 15, 0.05f, -1);
        break;
    case Anim::FROG_JUMP:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/frog_jump/animation_frog_jump0.png",
            "FROG_JUMP", "CaculateQuick/animation/frog_jump/animation_frog_jump%d.png", 0, 59, 0.05f, -1);
        break;
    case Anim::FROG_RELAX:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/frog_relax/animation_frog_relax0.png",
            "FROG_RELAX", "CaculateQuick/animation/frog_relax/animation_frog_relax%d.png", 0, 19, 0.05f, -1);
        break;
    case Anim::SPARK:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/spark/animation_spark0.png",
            "SPARK", "CaculateQuick/animation/spark/animation_spark%d.png", 0, 17, 0.05f, -1);
        break;
    case Anim::STAR:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/star/animtion_star0.png",
            "STAR", "CaculateQuick/animation/star/animtion_star%d.png", 0, 15, 0.05f, -1);
        break;
    case Anim::WATER:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/water/animation_water0.png",
            "WATER", "CaculateQuick/animation/water/animation_water%d.png", 0, 19, 0.05f, 1);
        break;
    case Anim::WIN:
        sprite = HELPER_MANAGER->getAnimateSprite("CaculateQuick/animation/win/animation_win0.png",
            "WIN", "CaculateQuick/animation/win/animation_win%d.png", 0, 29, 0.05f, -1);
        break;
    default:
        break;
    }

    return sprite;
}

void CaculateQuickGameScene::onPauseButtonClicked(cocos2d::Ref *sender)
{
    this->onGamePause();
    SOUND_MANAGER->playClickEffect();
    auto view = CaculateQuickPauseLayer::createView();
    auto closeButton = utils::findChild(view, "btn_close");
    if (closeButton) {
        if (auto node = utils::findChild(this, "top_game"))
            closeButton->setScale(node->getScale());
    }
    this->addChild(view);
}

void CaculateQuickGameScene::gameOver(int score)
{
    if (_isGameOver)
    {
        return;
    }

    _scroreAdd = score;
    updateScore(_scroreAdd);

    SOUND_MANAGER->playOnGameOver();

    this->unschedule("delay_update_level");
    if (auto lvl = utils::findChild(this, "new_level_level"))
    {
        lvl->removeFromParent();
    }

    _isGameOver = true;
    onGamePause();

    auto view = CaculateQuickGameOverLayer::createView();
    view->updateHighScore({ _scroreAdd, _currentLevelID});
    view->OnShowNumStar(0);

    auto closeButton = utils::findChild(view, "btn_close");
    if (closeButton) {
        if (auto node = utils::findChild(this, "top_game"))
            closeButton->setScale(node->getScale());
    }

    this->addChild(view);
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void CaculateQuickGameScene::updateTime(float dt)
{
    auto textTime = utils::findChild<ui::Text*>(this, "txt_time");
    textTime->setVisible(true);

    this->schedule([=](float dt) {
        if (_isGameOver)
        {
            return;
        }
    }, 1.0f, "delay_updateTime");
    
}

void CaculateQuickGameScene::updateLevel(bool isLevelUp)
{
    if (_currentLevelID >= _levels.size())
    {

        CCLOG("something wrong!!!");

        return;
    }

    auto levelId = UserDefault::getInstance()->getIntegerForKey(KEY_SAVE_LEVEL, 1);

    if (_currentLevelID >= levelId)
    {
        UserDefault::getInstance()->setIntegerForKey(KEY_SAVE_LEVEL, _currentLevelID);
    }

    UserDefault::getInstance()->setIntegerForKey(KEY_CURENT_LEVEL, _currentLevelID);

   auto _levelCurrent = _levels.at(_currentLevelID);
   _currentLevelID++;
}

void CaculateQuickGameScene::onGamePause()
{
    this->pause();

    this->pauseSchedulerAndActions();

    this->enumerateChildren(StringUtils::format("//%s.*", "objectPause_"), [](Node *child)
    {
		if (child) {

			child->pauseSchedulerAndActions();
		}

		return false; });

    /*auto children = this->getChildren();

    for (auto child : children)
    {
        child->pauseSchedulerAndActions();
        child->pause();
    }*/

    onPauseOrResumNode(this, true);
}

void CaculateQuickGameScene::onPauseOrResumNode(Node* node, bool isPause)
{
    if (isPause)
    {
        node->pauseSchedulerAndActions();
        node->pause();
    }
    else {
        node->resumeSchedulerAndActions();
        node->resume();
    }


    auto children = node->getChildren();

    if (children.empty() || children.size() == 0)
    {
        return;
    }

    for (auto child : children)
    {
        onPauseOrResumNode(child, isPause);
    }
}

void CaculateQuickGameScene::onGameResume()
{
    _isGameOver = false;
    this->resumeSchedulerAndActions();
    this->resume();

    this->enumerateChildren(StringUtils::format("//%s.*", "objectPause_"), [](Node *child)
                            {

		if (child) {

			child->resumeSchedulerAndActions();
		}

		return false; });

    auto children = this->getChildren();

    onPauseOrResumNode(this, false);
}

void CaculateQuickGameScene::OnGameWin(int score)
{
    auto sco = 50 - (int)_timer;
    if (sco < 0)
    {
        sco = 0;
    }

    _isGameOver = true;
    _scroreAdd = (int)(score * 1.5) + sco;
    _scroreAdd = std::max(_scroreAdd, 20);
     
    this->getEventDispatcher()->removeAllEventListeners();
    this->unscheduleAllCallbacks();
    this->unscheduleAllSelectors();
    this->stopAllActions();
    this->onGamePause();

    auto view = CaculateQuickWinLayer::createView();

    updateScore(_scroreAdd);

    view->OnShowTextLevel(_currentLevelID, 3, _scroreAdd);
    view->updateHighScore({ _scroreAdd, _currentLevelID });
    auto closeButton = utils::findChild(view, "btn_close");
    if (closeButton) {
        if (auto node = utils::findChild(this, "top_game"))
            closeButton->setScale(node->getScale());
    }
    this->addChild(view, INT_MAX);
    // SOUND_MANAGER->playWinEffect();
    ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

