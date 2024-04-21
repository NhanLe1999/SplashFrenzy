#include "SFGameScene.h"
#include "spine/Animation.h"
#include "BPHelperManager.h"
#include "BPSoundManager.h"
#include "BPEndLayer.hpp"
#include "PhysicsShapeCache.h"


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

INITIALIZE_READER(SFGameScene);

std::once_flag _game_scene;

Scene* SFGameScene::createScene()
{
    auto scene = Scene::createWithPhysics();

    if (scene)
    {
        //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        auto view = SFGameScene::createView();
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

SFGameScene* SFGameScene::createView()
{
    std::call_once(_game_scene, []
        { REGISTER_CSB_READER(SFGameScene); });

    auto view = reinterpret_cast<SFGameScene*>(CSLoader::createNodeWithVisibleSize("csb/ui/scene/SFGameScene.csb"));

    if (view)
    {
        return view;
    }

    CC_SAFE_DELETE(view);

    return nullptr;
}

void SFGameScene::didLoadFromCSB()
{
    _screenSize = Director::getInstance()->getVisibleSize();
    this->setName("SFGameScene");
    std::vector<int> ListMap = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,19,13,2,9,22,23,27,4,21,3,1,10,26,24,8,0,16,15,14,7,5,11,20,18,17,25,6,12,0,23,11,17,1,16,12,21,27,6,13,2,25,8,7,18,15,9,14,20,24,22,19,4,10,3,26,5,1,10,21,24,19,17,7,27,13,4,25,18,14,0,5,6,12,9,2,11,26,16,8,20,15,3,22,23,4,5,24,14,20,6,16,12,27,23,1,3,9,2,26,7,17,19,0,15,11,13,22,8,21,10,18,25,27,1,7,21,13,24,6,19,22,26,0,2,9,4,11,16,10,23,3,15,18,25,8,17,14,12,20,5,1,2,16,7,26,9,6,24,13,4,10,23,15,20,22,19,0,21,25,27,18,8,17,12,11,5,3,14,17,20,1,12,18,15,19,23,26,21,2,6,5,27,14,7,13,10,25,9,22,11,3,0,24,4,8,16,5,1,13,23,20,3,18,26,8,15,4,12,25,6,27,17,19,16,21,24,14,2,22,9,11,0,10,7,14,1,10,21,6,8,19,12,22,23,25,13,2,3,0,16,17,5,15,9,7,27,24,26,4,11,20,18,7,12,27,26,20,17,9,0,11,6,2,22,10,3,14,25,23,8,4,21,1,24,13,18,19,5,15,16,26,25,12,22,21,23,14,0,9,2,10,6,5,27,18,19,15,3,20,1,8,7,17,24,11,16,13,4,5,22,10,3,20,24,23,12,17,21,15,11,0,13,14,9,7,27,1,26,19,18,16,6,2,8,25,4,13,0,22,25,12,8,14,6,20,3,5,23,7,16,18,27,11,10,4,21,15,26,9,1,2,19,17,24,21,22,7,27,18,4,20,8,13,19,3,15,26,16,23,1,6,0,12,11,25,14,2,17,24,5,10,9,5,23,12,10,20,26,8,21,17,7,19,11,16,22,0,15,2,24,13,14,6,9,27,1,25,18,4,3,0,16,3,9,12,21,24,11,15,22,5,20,1,14,13,7,6,17,2,19,8,23,10,27,26,25,4,18,11,22,9,12,24,10,8,27,16,18,26,13,15,2,17,4,5,19,21,20,6,0,7,25,3,1,23,14,4,18,8,13,11,14,25,7,19,21,0,24,26,6,22,9,23,16,1,27,12,3,17,2,5,20,15,10,12,21,0,19,25,20,23,2,27,17,14,11,9,26,8,16,5,15,4,3,22,6,18,24,1,7,13,10,10,17,0,3,9,8,21,1,2,22,26,24,19,16,27,6,18,23,5,25,11,13,12,20,7,15,4,14,20,0,10,15,4,14,16,1,3,2,18,17,5,23,21,11,22,26,7,25,12,6,19,9,24,27,13,8,18,23,16,9,6,13,14,5,26,7,19,0,27,21,4,10,20,11,15,24,22,2,17,1,25,3,8,12,0,5,14,19,3,10,27,12,6,4,25,17,8,20,13,16,26,18,23,1,15,22,11,24,21,7,9,2,6,22,16,3,26,1,8,4,18,24,27,13,2,17,9,20,21,25,23,12,14,11,0,7,15,10,5,19,23,24,14,13,22,8,20,25,1,2,27,11,21,19,15,12,18,7,0,10,9,3,16,26,4,6,5,17,3,8,17,19,21,2,16,6,14,20,4,27,26,11,15,12,22,18,13,10,25,9,24,5,1,0,7,23,24,20,18,13,23,2,7,22,16,15,8,0,10,1,19,5,11,27,12,9,6,3,25,17,4,21,26,14,26,4,11,2,14,27,24,15,12,6,22,25,8,10,17,21,13,18,23,20,1,16,9,7,5,3,19,0,27,20,4,1,11,2,17,0,24,12,10,7,6,22,9,16,8,26,15,13,23,14,18,19,5,3,25,21,25,12,18,6,22,15,9,24,23,14,7,11,1,10,16,5,2,20,17,0,19,26,13,3,27,8,21,4,20,16,9,7,19,11,17,4,8,21,3,12,24,0,26,23,15,13,6,18,25,27,5,10,14,2,1,22,18,3,10,21,9,27,11,24,26,4,6,12,19,16,17,22,0,7,5,8,23,20,2,13,1,14,15,25,27,10,2,9,4,12,13,16,0,11,1,18,14,20,23,22,19,8,24,6,15,17,21,3,25,26,7,5,20,16,6,23,8,11,10,0,27,15,19,14,13,2,26,21,5,22,25,3,24,12,17,18,9,7,4,1,5,17,1,11,13,2,22,21,0,7,19,3,27,24,10,12,16,9,8,4,23,14,6,18,26,20,15,25,23,6,14,24,1,4,27,2,8,21,0,25,18,16,11,10,7,5,17,26,22,19,13,12,9,20,3,15,21,12,10,25,24,23,4,2,26,17,7,9,20,19,14,11,3,22,8,13,6,27,5,0,18,1,15,16,25,6,1,3,4,9,23,16,5,12,11,8,14,0,7,26,24,21,17,13,10,27,15,19,18,2,20,22,10,20,1,23,6,7,9,2,8,12,24,16,5,21,0,18,27,11,19,17,3,14,15,26,13,22,4,25,6,24,19,8,20,11,17,0,5,25,14,15,27,22,9,1,3,10,18,16,2,23,21,4,13,12,7,26,27,15,24,14,22,11,12,6,18,0,20,3,4,26,7,5,25,23,2,17,10,21,16,9,19,1,13,8,25,11,2,1,5,10,9,3,0,7,15,20,22,4,12,6,21,14,27,23,17,26,24,18,16,13,8,19,2,10,25,16,8,20,26,0,6,1,12,23,11,4,5,27,14,22,17,3,18,24,19,7,9,15,21,13,27,10,17,15,7,21,4,26,6,1,0,16,18,19,11,2,9,3,14,20,22,25,5,12,24,13,8,23,13,25,20,7,15,14,6,4,24,10,21,27,19,1,17,26,22,8,12,3,23,2,11,18,5,9,0,16,27,7,16,2,6,24,0,9,3,26,4,18,1,12,8,25,13,10,23,17,19,14,5,20,21,15,22,11,12,13,27,4,11,24,9,1,3,15,20,14,26,21,10,18,6,16,2,22,23,17,7,0,19,5,8,25,13,14,12,5,7,26,8,21,27,4,10,2,15,6,20,9,18,24,25,19,23,17,1,11,0,16,3,22,9,19,11,26,5,23,22,13,21,1,15,17,0,25,8,7,24,4,18,10,2,20,12,14,16,3,6,27,24,3,21,7,27,17,9,23,4,0,18,1,20,26,16,2,25,22,19,13,11,6,8,12,10,15,5,14 };
    SOUND_MANAGER->playMainMenuMusic(true);
    _screenSize = Director::getInstance()->getVisibleSize();
    UserDefault::getInstance()->setBoolForKey("key_is_play_anim_swip", false);

    if (auto txtLv = utils::findChild<ui::Text*>(this, "txt_level"))
    {
        txtLv->setString(std::to_string(_currentLevelID));
    }

    _currentIdCharater = UserDefault::getInstance()->getIntegerForKey("CharacterActive", 1);
    SetDataAnimForCharater();

    auto pointX = 0;

    if (auto bg = utils::findChild(this, "bg"))
    {
        bg->setScale(std::max(_screenSize.height / 540.00, _screenSize.width / 960.00));
    }


    root_layout = utils::findChild(this, "root_layout");
    auto root_game_play = utils::findChild(this, "root_game_play");

    auto path = cocos2d::StringUtils::format("res/map/title_map/map_%d.tmx", 3);
    _tileMap = TMXTiledMap::create(path);
    _tileMap->setAnchorPoint(Vec2(0, 0));
    _tileMap->setName("objectPause__tileMap");
    auto sizeMap = _tileMap->getContentSize();
    _tileMap->setPosition(Vec2(sizeMap.width / 2, sizeMap.height / 2));
    this->addChild(_tileMap, 100);
    root_game_play->setLocalZOrder(101);


    _character = Sprite::create(GetCurrentAnimCharater()._pathSpr);
    _character->setPosition(Vec2(_screenSize / 2));
    _tileMap->addChild(_character, INT_MAX);
    RunActionCharator(Anim::NV_1);
    _character->setName("Nv");

    PhysicsShapeCache::getInstance()->setBodyOnSprite("nv_1", _character, COLLISION_NV);

    float sca = 0.8f;

    getGroupNameByPoint("tuong", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_8.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_phai_cao_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_3.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_phai_thap_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_4.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_cao_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_2.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_thap_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_1.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_thap", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_12.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_phai_thap", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_13.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_t_1", "res/BlackPink/ground/ground_world_1/t_1.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_rotation", "res/BlackPink/object/bis_object_rotate.png", COLLISION_TUONG);
    getGroupNameByPoint("mushrom_world_1", "", COLLISION_ENEMY, sca);
    getGroupNameByPoint("kim_cuong", "", COLLISION_DIAMOND, 0.7);
    getGroupNameByPoint("kim_cuong_dynamic", "", COLLISION_DIAMOND, 0.7);
    getGroupNameByPoint("chia_khoa", "", COLLISION_CHIA_KHOA, sca);
    getGroupNameByPoint("xuong_rong_1", "res/BlackPink/object/PTModelSprite_ID55205.png", COLLISION_XUONG_RONG, 0.8f);
    getGroupNameByPoint("xuong_rong_doc", "res/BlackPink/object/PTModelSprite_ID37838.png", COLLISION_XUONG_RONG, sca);
    getGroupNameByPoint("tuong_khoa", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_5.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_tuong_move_up", "res/BlackPink/ground/ground_world_1/t_1.png", COLLISION_TUONG);
    getGroupNameByPoint("go_tuong", "res/BlackPink/object/bis_object_rotate.png", COLLISION_TUONG);
    getGroupNameByPoint("go_rotation", "res/BlackPink/object/bis_object_falling.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_nhac", "", COLLISION_NHAC, sca);



    // getGroupNameByPoint("tuong_trai_thap_tam_giac","res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_1.png", 88);
    this->scheduleUpdate();


    /*for (int i = 0; i  < 100; i++)
    {
        _mapBg = TMXTiledMap::create("res/map/map_bg/2/map_bg.tmx");
        _mapBg->setAnchorPoint(Vec2(0, 0));
        _mapBg->setPosition(Vec2(_pointX, 0));
        this->addChild(_mapBg, 9999);
        _pointX += _mapBg->getContentSize().width;

        float scale = _screenSize.height / _mapBg->getContentSize().height;
        _mapBg->setScale(scale);
        _listMapBg.push_back(_mapBg);
    }*/

    /*_mapBg = TMXTiledMap::create("res/map/map_bg/2/map_bg.tmx");
    _mapBg->setAnchorPoint(Vec2(0, 0));
    _mapBg->setPosition(Vec2(_pointX, 0));
    root_game_play->addChild(_mapBg, 9999);
    _pointX += _mapBg->getContentSize().width;

    float scale = _screenSize.height / _mapBg->getContentSize().height;
    _mapBg->setScale(scale);
    _listMapBg.push_back(_mapBg);

    _mapBg->setTag(_indexMap);

    CreateMap(_mapBg);*/

    /*for (int i = 0; i < _listMapBg.size(); i++)
    {
        cocos2d::Follow* followAction = cocos2d::Follow::create(_character, Rect(0, 0, sizeMap.width * 90000, _screenSize.height));
        _listMapBg[i]->runAction(followAction);
    }

    cocos2d::Follow* followAction3 = cocos2d::Follow::create(_character, Rect(0, 0, _mapBg->getContentSize().width * 90000, _screenSize.height));
    _mapBg->runAction(followAction3);*/

    cocos2d::Follow* followAction = cocos2d::Follow::create(_character, Rect(0, 0, sizeMap.width * 10, _screenSize.height));
    followAction->setTag(9090);
    _tileMap->stopActionByTag(9090);
    _tileMap->runAction(followAction);

    _physicSceneWorld->setGravity(Vec2(0, -980));

   /* cocos2d::Follow* followAction1 = cocos2d::Follow::create(this);
     root_layout->runAction(followAction1);

    cocos2d::Follow* followAction2 = cocos2d::Follow::create(this);
    root_game_play->runAction(followAction2);*/


    if (auto btn_left = utils::findChild<Button*>(this, "btn_left"))
    {
        btn_left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                isMoveLeft = true;
                isMoveRight = false;
                CCLOG("Left arrow key is pressed.");
                _character->setScaleX(-std::abs(_character->getScaleX()));
                _currentStatusNv = StatusNV::RUN;
                break;
            case ui::Widget::TouchEventType::ENDED:
                _character->unschedule("check_run_charater");
                CCLOG("Left arrow key is released.");
                isMoveLeft = false;
                _currentStatusNv = StatusNV::RELEAX;
                _currentStatusNv = isMoveRight ? StatusNV::JUMP : StatusNV::RELEAX;

                break;
            case ui::Widget::TouchEventType::CANCELED:
                _character->unschedule("check_run_charater");
                isMoveLeft = false;
                _currentStatusNv = isMoveRight ? StatusNV::JUMP : StatusNV::RELEAX;

                break;
            default:
                break;
            }
            });
    }

    if (auto btn_right = utils::findChild<Button*>(this, "btn_right"))
    {
        btn_right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                isMoveRight = true;
                isMoveLeft = false;
                CCLOG("Right arrow key is pressed.");
                _character->setScaleX(std::abs(_character->getScaleX()));
                _currentStatusNv = StatusNV::RUN;
                break;
            case ui::Widget::TouchEventType::ENDED:
                isMoveRight = false;
                _character->unschedule("check_run_charater");
                _currentStatusNv = isMoveLeft ? StatusNV::JUMP : StatusNV::RELEAX;

                break;
            case ui::Widget::TouchEventType::CANCELED:
                isMoveRight = false;
                _character->unschedule("check_run_charater");
                _currentStatusNv = isMoveLeft ? StatusNV::JUMP : StatusNV::RELEAX;

                break;
            default:
                break;
            }
            });
    }

    if (auto btn_up = utils::findChild<Button*>(this, "btn_up"))
    {
        float xP = 350, yP = 550;
        btn_up->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                isMoveUp = true;
                CCLOG("Up arrow key is pressed.");
                if (_numJum >= 2)
                {
                    return;
                }
                _currentStatusNv = StatusNV::JUMP;
                _character->scheduleOnce([this](float dt) {
                    _currentStatusNv = (isMoveRight || isMoveLeft) ? StatusNV::RUN : StatusNV::RELEAX;

                    //_currentStatusNv = StatusNV::RELEAX;
                    }, 1.0f, "delay_change_state");
                _numJum++;
                _character->getPhysicsBody()->setVelocity(Vec2(_character->getPhysicsBody()->getVelocity().x, 550));
                break;
            case ui::Widget::TouchEventType::ENDED:
                log("Button Touch Ended");
                break;
            default:
                break;
            }
            });
    }





    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SFGameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SFGameScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SFGameScene::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(SFGameScene::onContactSeparate, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(SFGameScene::onContactPreSolve, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    //_character->getPhysicsBody()->setContactTestBitmask(true);


    _score = HELPER_MANAGER->GetTotalNumberCoin(false);
    _Diamond = HELPER_MANAGER->GetTotalNumberCoin(true);

    updateScore(0);
    updateDiamond(0);
}

void SFGameScene::CreateMap(TMXTiledMap* map)
{
    _character->schedule([=](float dt) {

        auto pointC = root_layout->convertToWorldSpaceAR(_character->getPosition());
        auto pointMap = root_layout->convertToWorldSpaceAR(map->getPosition() + map->getBoundingBox().size);
        CCLOG("point: %f__map___pointC:%f___pointMap:%f__naem:%s", map->getPositionX(), pointC.x, pointMap.x, map->getName().c_str());
        auto kk1 = map->getPosition();
        auto kk2 = _listMapBg[_listMapBg.size() - 1]->getPositionX();

        auto kk = std::abs(pointC.x - pointMap.x);

        if (-_screenSize.width + pointMap.x > 10)
        {
            _character->unschedule("check_create_map");
            auto pointN = map->getPosition() + map->getContentSize();
            _indexMap++;
            auto mapBg = TMXTiledMap::create("res/map/map_bg/2/map_bg.tmx");
            mapBg->setAnchorPoint(Vec2(0, 0));
            mapBg->setPosition(Vec2(pointN.x, 0));
            map->getParent()->addChild(mapBg, 9999);
            _pointX += mapBg->getBoundingBox().size.width;
            mapBg->setName("name_" + std::to_string(_indexMap));

            /*cocos2d::Follow* followAction3 = cocos2d::Follow::create(_character, Rect(0, 0, mapBg->getPositionX() + mapBg->getContentSize().width * 20000, _screenSize.height));
            mapBg->runAction(followAction3);*/

            cocos2d::Follow* followAction2 = cocos2d::Follow::create(_character);
            mapBg->runAction(followAction2);

            _listMapBg.push_back(mapBg);
            mapBg->setScaleY(0.25f);
            CreateMap(mapBg);
        }

        }, "check_create_map");
}

void SFGameScene::getGroupNameByPoint(std::string name, std::string pathSr, int collison, float scale)
{
    auto group = _tileMap->objectGroupNamed(name);

    if (!group)
    {
        return;
    }

    auto listValuOfGroup = group->getObjects();
    int j = 0;

    for (int i = 0; i < listValuOfGroup.size(); i++)
    {
        auto value = listValuOfGroup[i];
        auto k1 = value.asValueMap();

        auto x = k1["x"].asFloat();
        auto y = k1["y"].asFloat();

        auto width = k1["width"].asFloat();

        auto height = k1["height"].asFloat();

        Sprite* sprite = nullptr;

        if (name == "tuong_trai_thap" || name == "tuong_phai_thap" || name == "go_tuong")
        {
            name = "tuong";
        }

        Anim ani = Anim::DEFAULT;
        bool isCollisonBismask = true;

        if (name == "mushrom_world_1")
        {
            ani = Anim::MUSHROM_WORD_1;
        }

        if (name == "kim_cuong" || name == "kim_cuong_dynamic")
        {
            ani = Anim::DIAMOND;
        }

        if (name == "chia_khoa")
        {
            ani = Anim::KEY;
            isCollisonBismask = false;
        }
        if (name == "obj_nhac")
        {
            ani = Anim::GET_NOTE;
        }

        sprite = CreateObject(pathSr, cocos2d::Vec2(x, y) + Vec2(width / 2, height), name, collison, ani);
        if (name == "obj_rotation")
        {
            j++;
        }

        if (name == "mushrom_world_1")
        {
            int s = cocos2d::random(50, 200);
            sprite->setTag(s);
            sprite->setPositionY(sprite->getPositionY() - 10);
            float time = cocos2d::rand_0_1() * (float)cocos2d::random(1, 5);
            sprite->scheduleOnce([=](float dt) {
                sprite->schedule([=](float  dt) {
                    auto tag = sprite->getTag();

                    sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getTag(), 0));
                    sprite->setTag(-sprite->getTag());
                    sprite->setScaleX(-sprite->getScaleX());

                    }, 1.55f, "delay_mushRom_run");
                }, time, "delay_mushRom_run_scheduleOnce");

            sprite->getPhysicsBody()->setContactTestBitmask(true);

        }

        if (name == "obj_tuong_move_up")
        {
            auto point1 = this->convertToWorldSpaceAR(sprite->getPosition());
            sprite->setTag(7);

            sprite->schedule([=](float dt) {

                auto point2 = this->convertToWorldSpaceAR(_character->getPosition());
                if (std::abs(point1.x - point2.x) <= 25.0f)
                {
                    sprite->getPhysicsBody()->setVelocity(Vec2(0, 400));
                    sprite->unschedule("check_point");
                    sprite->scheduleOnce([=](float dt) {
                        sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
                        }, 1.2f, "delay_mushRom_run_scheduleOnce");
                }

                }, "check_point");
        }

        // sprite = CreateObject(pathSr, cocos2d::Vec2(x, y) + Vec2(width / 2, height), name, 23);

        if (name == "tuong_phai_thap_tam_giac" || name == "tuong_trai_thap_tam_giac")
        {
            sprite->setAnchorPoint(Vec2(0.5f, 1));
        }

        if (name == "xuong_rong_1")
        {
            sprite->setPosition(sprite->getPosition() + Vec2(20, 0));
        }

        if (name == "xuong_rong_doc")
        {
            auto point1 = this->convertToWorldSpaceAR(sprite->getPosition());

            sprite->schedule([=](float dt) {

                auto point2 = this->convertToWorldSpaceAR(_character->getPosition());
                if (std::abs(point1.x - point2.x) <= 10.0f)
                {
                    sprite->getPhysicsBody()->setDynamic(true);
                    sprite->scheduleOnce([sprite](float dt) {
                        sprite->removeFromParent();
                        }, 2.5f, "delay_delete");
                }

                }, "check_point");

        }

        if (name == "tuong_khoa")
        {
            _listTuong.push_back(sprite);
        }

        sprite->setScale(scale);


        if (sprite == nullptr) {
            continue;
        }


        _tileMap->addChild(sprite);

        CCLOG("%f, %f", x, y);

    }

}

Sprite* SFGameScene::CreateObject(std::string path, Vec2 point, std::string name, int collison, Anim anim)
{
    Sprite* sprite = nullptr;

    sprite = anim != Anim::DEFAULT ? GetAnim(anim) : Sprite::create(path);

    sprite->setAnchorPoint(Point(0.5, 0));
    sprite->setPosition(point);
    sprite->setScale(0.5f);

    if (name != "")
    {
        PhysicsShapeCache::getInstance()->setBodyOnSprite(name, sprite, collison);
        //sprite->getPhysicsBody()->setCollisionBitmask(isCollisonBismak);
        int kk = sprite->getPhysicsBody()->getCollisionBitmask();
        int k = 0;
    }
    sprite->setName(name);

    return sprite;
}


void SFGameScene::SetDataAnimForCharater()
{
    switch (_currentIdCharater)
    {
    case 1:
    {
        _dataAnimCharater = { 
            {"RUN_1", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58595.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58595,58602, -1},
            {"JUMP_1", StatusNV::JUMP, "res/BlackPink/character/jump/nv_1/PTModelSprite_ID58593.png", "res/BlackPink/character/jump/nv_1/PTModelSprite_ID%d.png", 58593,58594, 0},
            {"RELEAX_1", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58592.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58592,58595, -1},
            {"DIE_1", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58596.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58596,58596, 0}

        };

        break;
    }
    case 2:
    {
        _dataAnimCharater = {
            {"RUN_2", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58668.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58668,58674, -1},
            {"JUMP_2", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID62581.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62581,62582, 0},
            {"RELEAX_2", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58659.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58659,58662, -1},
            {"DIE_2", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58660.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58660,58660, 0}
        
        };

        break;
    }
    case 3:
    {
        _dataAnimCharater = {
            {"RUN_3", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58636.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58636,58641, -1},
            {"JUMP_3", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID62580.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62678,62679, 0},
            {"RELEAX_3", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58627.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58627,58630, -1},
            {"DIE_3", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58644.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58644,58644, 0}

        };

        break;
    }
    case 4:
    {
        _dataAnimCharater = {
            {"RUN_4", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58700.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58700,58705, -1},
            {"JUMP_4", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID62658.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62658,62659, 0},
            {"RELEAX_4", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58691.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58691,58694, -1},
            {"DIE_4", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58692.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58692,58692, 0}
        };
        break;
    }
    case 5:
    {
        _dataAnimCharater = {
            {"RUN_5", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63292.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63292,63297, -1},
            {"JUMP_5", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID63246.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63246,63247, 0},
            {"RELEAX_5", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63238.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63238,63241, -1},
            {"DIE_5", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID63239.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 63239,63239, 0}
        };

        break;
    }
    case 6:
    {
        _dataAnimCharater = {
            {"RUN_6", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58732.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58732,58737, -1},
            {"JUMP_6", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID62663.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62663,62664, 0},
            {"RELEAX_6", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58723.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58723,58726, -1},
            {"DIE_6", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58724.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58724,58724, 0}
        };

        break;
    }
    case 7:
    {
        _dataAnimCharater = {
            {"RUN_7", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63303.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63303,63308, -1},
            {"JUMP_7", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID63266.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63266,63267, 0},
            {"RELEAX_7", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63257.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63257,63260, -1},
            {"RELEAX_7", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63257.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63257,63260, -1},
            {"DIE_7", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID63258.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 63257,63258, 0}
        };

        break;
    }
    case 8:
    {
        _dataAnimCharater = {
            {"RUN_8", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58764.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58764,58769, -1},
            {"JUMP_8", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID62666.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62666,62667, 0},
            {"RELEAX_8", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58755.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58755,58758, -1},
            {"DIE_8", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58756.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58756,58756, 0}
        };

        break;
    }
    case 9:
    {
        _dataAnimCharater = {
            {"RUN_9", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63313.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63313,63318, -1},
            {"JUMP_9", StatusNV::JUMP, "res/BlackPink/character/jump/PTModelSprite_ID63287.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63287,63288, 0},
            {"RELEAX_9", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63278.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63278,63281, -1},
            {"DIE_9", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID63279.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 63279,63279, 0}

        };

        break;
    }
    default:
        break;
    }
}

DataPathAnim SFGameScene::GetCurrentAnimCharater()
{
    for (auto an : _dataAnimCharater)
    {
        if (_currentStatusNv == an._state)
        {
            return an;
        }
    }
    return _dataAnimCharater[0];
}

void SFGameScene::RunActionCharator(Anim anim)
{
    if (_NewStatusNv == _currentStatusNv)
    {
        return;
    }

    auto data = GetCurrentAnimCharater();
    
    CCLOG("DMMMMMMM");

    Animate* anim1 = HELPER_MANAGER->getAnimate(data._pathSpr,
        data._nameAnim, data._pahtAnim.c_str(), data._numStart, data._numnEnd, 0.1f, data._loop, data._state == StatusNV::RUN);;

    _NewStatusNv = _currentStatusNv;
    
    _character->setTag(999);
    _character->stopAllActions();
    _character->runAction(anim1);
}

void SFGameScene::RunAnimNv()
{
    switch (_currentIdCharater)
    {
        case 1:
        {
            break;
        }
        default:
            break;
    }
}

void SFGameScene::SetUpdataLevel()
{

}

void SFGameScene::SetDataCurrentLevel(int level_id)
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

void SFGameScene::updateScore(int scoreAdd)
{
    HELPER_MANAGER->AddNumberCoin(scoreAdd, false);
    _score += scoreAdd;
    _currentCoin += scoreAdd;
    updateLabel("txt_score", std::to_string(_score));
}

void SFGameScene::updateDiamond(int scoreAdd)
{
    HELPER_MANAGER->AddNumberCoin(scoreAdd, true);
    _Diamond += scoreAdd;
    _currentGem += scoreAdd;
    updateLabel("txt_diamond", std::to_string(_Diamond));
}

void SFGameScene::update(float dt)
{
    if (_isGameOver)
    {
        return;
    }
    if (_character->getPositionY() <= 0)
    {
        OnGameOver();
        return;
    }

    Vec2 velocity = _character->getPhysicsBody()->getVelocity();

    float constantSpeed = 10;


    if (isMoveRight) {
        velocity.x = 200;
    }
    else if (isMoveLeft) {
        velocity.x = -200;
    }
    else {
        velocity.x = 0;
    }
    RunActionCharator(Anim::NV_1);

    //velocity = Vec2(200, 0);

    _character->getPhysicsBody()->setVelocity(velocity);

}

void SFGameScene::OnGameOver()
{
    gameOver(_score);
}

void SFGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    float x = 350, y = 550;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        isMoveUp = true;
        CCLOG("Up arrow key is pressed.");
        if (_numJum >= 2)
        {
            return;
        }
        _numJum++;
        _character->getPhysicsBody()->setVelocity(Vec2(_character->getPhysicsBody()->getVelocity().x, y));
        _currentStatusNv = StatusNV::JUMP;
        _character->scheduleOnce([this](float dt) {
                 //   _currentStatusNv = StatusNV::RELEAX;
                    _currentStatusNv = (isMoveRight || isMoveLeft) ? StatusNV::RUN : StatusNV::RELEAX;

                    }, 1.0f, "delay_change_state");
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        CCLOG("Down arrow key is pressed.");
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        isMoveLeft = true;
        isMoveRight = false;
        CCLOG("Left arrow key is pressed.");
        _character->setScaleX(-std::abs(_character->getScaleX()));
        _currentStatusNv = StatusNV::RUN;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        isMoveRight = true;
        isMoveLeft = false;
        CCLOG("Right arrow key is pressed.");
        _character->setScaleX(std::abs(_character->getScaleX()));
        _currentStatusNv = StatusNV::RUN;
        break;
    default:
        break;
    }
}

void SFGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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
        _character->unschedule("check_run_charater");
        CCLOG("Left arrow key is released.");
        isMoveLeft = false;
        _currentStatusNv = isMoveRight ? StatusNV::JUMP : StatusNV::RELEAX;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        isMoveRight = false;
        CCLOG("Right arrow key is released.");
        _character->unschedule("check_run_charater");
        _currentStatusNv = isMoveLeft ? StatusNV::JUMP : StatusNV::RELEAX;
        break;
    default:
        break;
    }
}

bool SFGameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    //if (_isGameOver) { return true; }

    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    int aCollision = a->getCollisionBitmask();
    int bCollision = b->getCollisionBitmask();

    /* if ((COLLISION_FOG == aCollision && COLLISION_GO == bCollision) || (COLLISION_FOG == bCollision && COLLISION_GO == aCollision))
     {

         if (COLLISION_GO == aCollision)
         {
             auto parent = a->getOwner();
             if (parent != nullptr)
             {
                 OnCollisionHeroAndOt();
             }
         }
         else {
             auto parent = b->getOwner();
             if (parent != nullptr)
             {
                 OnCollisionHeroAndOt();
             }
         }
     }*/
    if ((COLLISION_NV == aCollision && COLLISION_TUONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG == aCollision))
    {
        _numJum = 0;
        _isRun = false;
        _character->unschedule("delay_down");
        if (_currentStatusNv == StatusNV::JUMP)
        {
            _currentStatusNv = (isMoveRight || isMoveLeft) ? StatusNV::RUN : StatusNV::RELEAX;
        }
    }
    else if ((COLLISION_NV == aCollision && COLLISION_ENEMY == bCollision) || (COLLISION_NV == bCollision && COLLISION_ENEMY == aCollision))
    {
        if (COLLISION_ENEMY == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndNam(parent);
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndNam(parent);
            }
        }
    }
    else if ((COLLISION_NV == aCollision && COLLISION_DIAMOND == bCollision) || (COLLISION_NV == bCollision && COLLISION_DIAMOND == aCollision))
    {
        if (COLLISION_DIAMOND == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndDiamon(parent);
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndDiamon(parent);
            }
        }
    }
    else if ((COLLISION_NV == aCollision && COLLISION_XUONG_RONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_XUONG_RONG == aCollision))
    {
        if (COLLISION_XUONG_RONG == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndXuongRong();
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndXuongRong();
            }
        }
    }
    else if ((COLLISION_NV == aCollision && COLLISION_CHIA_KHOA == bCollision) || (COLLISION_NV == bCollision && COLLISION_CHIA_KHOA == aCollision))
    {
        if (COLLISION_CHIA_KHOA == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndChiaKhoa(parent);
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndChiaKhoa(parent);
            }
        }
    }
    else if ((COLLISION_NV == aCollision && COLLISION_NHAC == bCollision) || (COLLISION_NV == bCollision && COLLISION_NHAC == aCollision))
    {
        if (COLLISION_NHAC == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndNhac(parent);
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndNhac(parent);
            }
        }
    }
   
    return true;
}

void SFGameScene::onContactSeparate(PhysicsContact& contact)
{
    /* if (!_isGamePlay)
     {
         return;
     }*/
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    int aCollision = a->getCollisionBitmask();
    int bCollision = b->getCollisionBitmask();

    if ((COLLISION_NV == aCollision && COLLISION_TUONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG == aCollision))
    {
        _character->scheduleOnce([=](float dt) {
            /*  if (_numJum)
              {
                  _character->getPhysicsBody()->setVelocity(Vec2(0, -2));
              }*/
            }, 0.01f, "delay_down");
        /*if (COLLISION_GO_TRON == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                _currentFrogState = State::JUMP;
                OnContactSeparateFrogAndGoTron();
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                _currentFrogState = State::JUMP;
                OnContactSeparateFrogAndGoTron();
            }
        }*/
    }
    else if ((COLLISION_NV == aCollision && COLLISION_TUONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG == aCollision)) {

    }
}

bool SFGameScene::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    int aCollision = a->getCollisionBitmask();
    int bCollision = b->getCollisionBitmask();

    if ((COLLISION_NV == aCollision && COLLISION_TUONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG == aCollision))
    {
        _numJum = 0;
    }
    return true;
}

void SFGameScene::OnCollisionCharaterAndNam(Node* nam)
{
    nam->scheduleOnce([=](float dt) {
        nam->removeFromParent();
        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndDiamon(Node* diamon)
{
    diamon->scheduleOnce([=](float d) {
        updateDiamond(1);
        diamon->removeFromParent();
        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndChiaKhoa(Node* ck)
{
    ck->scheduleOnce([=](float d) {
        ck->removeFromParent();

        for (auto tc : _listTuong)
        {
            auto physice = tc->getPhysicsBody();
            physice->setCollisionBitmask(false);
            physice->setRotationEnable(true);
            physice->setDynamic(true);

            float x = cocos2d::random(-50, 50);
            float y = cocos2d::random(-200, 500);
            physice->setVelocity(Vec2(x, y));

            tc->scheduleOnce([tc](float dt) {
                tc->removeFromParent();
                }, 2.25f, "delay_delete");
        }

        _listTuong.clear();

        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndNhac(Node* ck)
{
    ck->scheduleOnce([=](float d) {
        ck->removeFromParent();
        updateScore(1);
    }, 0.005f, "OnCollisionCharaterAndNhac");
}

void SFGameScene::OnCollisionCharaterAndXuongRong()
{
    _character->scheduleOnce([=](float d) {
        OnGameOver();
        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::onShopButtonClicked(cocos2d::Ref* sender)
{
    
}


cocos2d::ui::Widget::ccWidgetClickCallback SFGameScene::onLocateClickCallback(const std::string& callBackName)
{
    std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(SFGameScene, onPauseButtonClicked),
        CLICK_MAP(SFGameScene, onShopButtonClicked),
    };

    if (function_map.find(callBackName) != function_map.end())
    {
        return function_map.at(callBackName);
    }

    return nullptr;
}

void SFGameScene::updateLabel(std::string labelName, std::string data)
{
    if (auto scoreText = utils::findChild<cocos2d::ui::Text*>(this, labelName)) {
        scoreText->stopAllActions();
        scoreText->setString(data);
        scoreText->runAction(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(0.25f, 1.5f)), EaseBackOut::create(ScaleTo::create(0.25f, 1.1f))));
    }
}

Sprite* SFGameScene::GetAnim(Anim anim)
{
    Sprite* sprite = nullptr;

    switch (anim)
    {
    case Anim::MUSHROM_WORD_1:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/enemy/mushroom/mushrom_world_1/mushroom_run_0.png",
            "MUSHROM_WORD_1", "res/BlackPink/animation/enemy/mushroom/mushrom_world_1/mushroom_run_%d.png", 0, 4, 0.05f, -1);
        break;
    case Anim::DIAMOND:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/get_diamond/animation_get_dianond01.png",
            "DIAMOND", "res/BlackPink/animation/get_diamond/animation_get_dianond0%d.png", 1, 7, 0.05f, -1);
        break;
    case Anim::GET_NOTE:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/note/animation_note00.png",
            "GET_NOTE", "res/BlackPink/animation/note/animation_note0%d.png", 0, 7, 0.05f, -1);
        break;
    case Anim::KEY:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/key/aniamtion_key00.png",
            "KEY", "res/BlackPink/animation/key/aniamtion_key0%d.png", 0, 11, 0.05f, -1);
        break;
    case Anim::MUSIC:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/note/animation_note00.png",
            "MUSIC", "res/BlackPink/animation/note/animation_note0%d.png", 0, 19, 0.05f, 1);
        break;
    default:
        break;
    }

    return sprite;
}

void SFGameScene::onPauseButtonClicked(cocos2d::Ref* sender)
{
    this->onGamePause();
    SOUND_MANAGER->playClickEffect();
    auto view = BPEndLayer::create(false, _currentGem, _currentCoin);
   
    view->setCallback([this]() {
        onGameResume();
        });
    this->addChild(view, INT_MAX);
}

void SFGameScene::gameOver(int score)
{
    if (_isGameOver)
    {
        return;
    }
    _isGameOver = true;


    _currentStatusNv = StatusNV::DIE;
    RunActionCharator(Anim::NV_1);

   // _scroreAdd = score;
    //updateScore(_scroreAdd);

   // SOUND_MANAGER->playOnGameOver();

    this->unschedule("delay_update_level");

   // onGamePause();

    this->scheduleOnce([=](float dt) {
        onGamePause();
        if (auto lvl = utils::findChild(this, "new_level_level"))
        {
            lvl->removeFromParent();
        }

        auto view = BPEndLayer::create(true, _currentGem, _currentCoin);
        /*view->updateHighScore({ _scroreAdd, _currentLevelID });
        view->OnShowNumStar(0);*/

        auto closeButton = utils::findChild(view, "btn_close");
        if (closeButton) {
            if (auto node = utils::findChild(this, "top_game"))
                closeButton->setScale(node->getScale());
        }

        this->addChild(view, INT_MAX);

        },1.0f, "delay_game_over");

    
    //ANIMATION_MANAGER->transitionSlideIn(CaculateQuickAnimationManager::Direction::LEFT, 0.25f, utils::findChild(view, "background"));
}

void SFGameScene::updateTime(float dt)
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

void SFGameScene::updateLevel(bool isLevelUp)
{
    
}

void SFGameScene::onGamePause()
{
    this->pause();

    this->pauseSchedulerAndActions();

    this->enumerateChildren(StringUtils::format("//%s.*", "objectPause_"), [](Node* child)
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

void SFGameScene::onPauseOrResumNode(Node* node, bool isPause)
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
    if (auto physic = node->getPhysicsBody())
    {
        physic->setEnabled(!isPause);
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

void SFGameScene::onGameResume()
{
    _isGameOver = false;
    this->resumeSchedulerAndActions();
    this->resume();

    this->enumerateChildren(StringUtils::format("//%s.*", "objectPause_"), [](Node* child)
        {

            if (child) {

                child->resumeSchedulerAndActions();
            }

            return false; });

    auto children = this->getChildren();

    onPauseOrResumNode(this, false);
}

void SFGameScene::OnGameWin(int score)
{
   
}

