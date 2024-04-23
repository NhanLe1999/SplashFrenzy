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
      //  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    std::vector<int> ListMap = { 1, 2, 3, 3, 2, 1, 1 ,2, 3, 3, 2, 1, 1 ,2 ,3};
    _screenSize = Director::getInstance()->getVisibleSize();
    UserDefault::getInstance()->setBoolForKey("key_is_play_anim_swip", false);


    auto idMap = cocos2d::random(0, (int)ListMap.size() - 1);

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

    getGroupNameByPoint("tuong", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_8.png", COLLISION_TUONG, 0.5f);
    getGroupNameByPoint("tuong_opacity", "", COLLISION_TUONG_DIE, 0.5f);
    getGroupNameByPoint("tuong_opacity_not_die", "", COLLISION_TUONG, 0.5f);

    getGroupNameByPoint("tuong_phai_cao_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_3.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_phai_thap_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_4.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_cao_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_2.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_thap_tam_giac", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_1.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_trai_thap", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_12.png", COLLISION_TUONG);
    getGroupNameByPoint("tuong_phai_thap", "res/BlackPink/ground/ground_world_1/bis_object_ground_world_1_13.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_t_1", "res/BlackPink/ground/ground_world_1/t_1.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_rotation", "res/BlackPink/object/bis_object_rotate.png", COLLISION_TUONG);
    getGroupNameByPoint("mushrom_world_1", "", COLLISION_TUONG_DIE, sca);
    getGroupNameByPoint("kim_cuong", "res/BlackPink/object/PTModelSprite_ID56969.png", COLLISION_DIAMOND, 0.7);
    getGroupNameByPoint("kim_cuong_dynamic", "res/BlackPink/object/PTModelSprite_ID56969.png", COLLISION_DIAMOND, 0.7);
    getGroupNameByPoint("chia_khoa", "", COLLISION_CHIA_KHOA, sca);
    getGroupNameByPoint("xuong_rong_1", "res/BlackPink/object/PTModelSprite_ID55205.png", COLLISION_XUONG_RONG, 0.5f);
    getGroupNameByPoint("xuong_rong_doc", "res/BlackPink/object/PTModelSprite_ID37838.png", COLLISION_XUONG_RONG, sca);
    getGroupNameByPoint("tuong_khoa", "res/BlackPink/object/bis_object_rotate.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_tuong_move_up", "res/BlackPink/ground/ground_world_1/t_1.png", COLLISION_TUONG);
    getGroupNameByPoint("go_tuong", "res/BlackPink/object/bis_object_rotate.png", COLLISION_TUONG);
    getGroupNameByPoint("go_rotation", "res/BlackPink/object/box.png", COLLISION_TUONG);
    getGroupNameByPoint("obj_nhac", "", COLLISION_NHAC, sca);

    this->scheduleUpdate();

    std::string nameMap = cocos2d::StringUtils::format("res/map/map_bg/%d/map_bg.tmx", 1);
    _mapBg = TMXTiledMap::create(nameMap);
    _mapBg->setAnchorPoint(Vec2(0, 0));
    _mapBg->setPosition(Vec2(_pointX, 0));
    this->addChild(_mapBg, 1);
    float scale = _screenSize.height / _mapBg->getContentSize().height;
    _mapBg->setScale(scale);

    cocos2d::Follow* followAction1 = cocos2d::Follow::create(_character, Rect(0, 0, _mapBg->getContentSize().width , _screenSize.height));
    _mapBg->runAction(followAction1);

    cocos2d::Follow* followAction = cocos2d::Follow::create(_character, Rect(0, 0, sizeMap.width, _screenSize.height));
    _tileMap->runAction(followAction);

    _physicSceneWorld->setGravity(Vec2(0, -1000));

    if (auto btn_left = utils::findChild<Button*>(this, "btn_left"))
    {
        btn_left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                OnMoveLeft();
                break;
            case ui::Widget::TouchEventType::ENDED:
                _character->unschedule("check_run_charater");
                CCLOG("Left arrow key is released.");
                isMoveLeft = false;
                _currentStatusNv = StatusNV::RELEAX;
                _currentStatusNv = isMoveRight ? OnResetSateNv() : StatusNV::RELEAX;

                break;
            case ui::Widget::TouchEventType::CANCELED:
                _character->unschedule("check_run_charater");
                isMoveLeft = false;
                _currentStatusNv = isMoveRight ? OnResetSateNv() : StatusNV::RELEAX;

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
                OnMoveRight();
                break;
            case ui::Widget::TouchEventType::ENDED:
                isMoveRight = false;
                _character->unschedule("check_run_charater");
                _currentStatusNv = isMoveLeft ? StatusNV::JUMP_UP : StatusNV::RELEAX;

                break;
            case ui::Widget::TouchEventType::CANCELED:
                isMoveRight = false;
                _character->unschedule("check_run_charater");
                _currentStatusNv = isMoveLeft ? StatusNV::JUMP_UP : StatusNV::RELEAX;

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
                OnJump();
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


    _score = HELPER_MANAGER->GetTotalNumberCoin(false);
    _Diamond = HELPER_MANAGER->GetTotalNumberCoin(true);

    updateScore(0);
    updateDiamond(0);

    if (auto button = utils::findChild<ui::Button*>(this, "btn_sound"))
    {
        button->loadTextureNormal(StringUtils::format("res/BlackPink/button_world/button_world_1/bis_button_sound_%s_world_1.png", !SOUND_MANAGER->isSoundEffectEnable() ? "off" : "on"));
    }

    if (auto button = utils::findChild<ui::Button*>(this, "music"))
    {
        button->loadTextureNormal(StringUtils::format("res/BlackPink/button_world/button_world_1/bis_button_music_%s_world_1.png", !SOUND_MANAGER->isMusicEffectEnable() ? "off" : "on"));
    }
}

StatusNV SFGameScene::OnResetSateNv()
{
    auto vig = _character->getPhysicsBody()->getVelocity();

    if (vig.y <= 0.01)
    {
        return StatusNV::JUMP_DOWN;
    }

    return StatusNV::JUMP_UP;
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
        std::string n1 = name;

        if (name == "tuong_trai_thap" || name == "tuong_phai_thap" || name == "go_tuong" || name == "tuong_opacity" || name == "tuong_opacity_not_die")
        {
            name = "tuong";
        }

        Anim ani = Anim::DEFAULT;
        bool isCollisonBismask = true;

        if (name == "mushrom_world_1")
        {
            ani = Anim::MUSHROM_WORD_1;
        }

        if (name == "chia_khoa")
        {
            ani = Anim::KEY;
            isCollisonBismask = false;
        }
        if (name == "obj_nhac")
        {
            ani = Anim::NOTE;
        }

        sprite = CreateObject(pathSr, cocos2d::Vec2(x, y) + Vec2(width / 2, height), name, collison, ani);

        if (n1 == "tuong_opacity" || n1 == "tuong_opacity_not_die")
        {
            sprite->setVisible(false);
        }


        sprite->setPositionY(sprite->getPositionY() + 25);

        if (name == "obj_rotation")
        {
            j++;
        }

        if (name == "mushrom_world_1")
        {
            int s = cocos2d::random(90, 120);
            sprite->setTag(s);
            sprite->setPositionY(sprite->getPositionY() - 10);

            /*sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getTag(), 0));
            sprite->setTag(-sprite->getTag());
            sprite->setScaleX(sprite->getScaleX());*/

            sprite->schedule([=](float  dt) {
                auto tag = sprite->getTag();

                sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getTag(), 0));
                sprite->setTag(-sprite->getTag());
                sprite->setScaleX(-sprite->getScaleX());

                }, 1.55f, "delay_mushRom_run");

            sprite->getPhysicsBody()->setContactTestBitmask(true);

            auto sp = Sprite::create("res/BlackPink/animation/enemy/mushroom/mushrom_world_1/mushroom_run_1.png");
            sp->setAnchorPoint(Vec2(0.5f, 0.5f));
            sp->setPosition(sprite->getContentSize() / 2);
            sprite->addChild(sp);
            sprite->setPositionY(sprite->getPositionY() + 10);
            sp->setName("mushroom_run_die");

            sp->setVisible(false);

            PhysicsShapeCache::getInstance()->setBodyOnSprite("mushroom_run_die", sp, COLLISION_ENEMY);

        }

        if (name == "obj_tuong_move_up")
        {
            auto point1 = this->convertToWorldSpaceAR(sprite->getPosition());
            sprite->setTag(7);

            sprite->schedule([=](float dt) {

                auto point2 = this->convertToWorldSpaceAR(_character->getPosition());
                if (std::abs(point1.x - point2.x) <= 25.0f)
                {
                    sprite->getPhysicsBody()->setVelocity(Vec2(0, 500));
                    sprite->unschedule("check_point");
                    sprite->scheduleOnce([=](float dt) {
                        sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
                        }, 0.8f, "delay_mushRom_run_schedleOnce");
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
                if (std::abs(point1.x - point2.x) <= 20.0f)
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


    if (anim != Anim::DEFAULT)
    {
        sprite = GetAnim(anim);
    }else if (path == "")
    {
        sprite = Sprite::create();
    }
    else {
        sprite = Sprite::create(path);
    }

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
            {"RUN_1", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58595.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58595,58601, -1},
            {"JUMP_UP_1", StatusNV::JUMP_UP, "res/BlackPink/character/jump/nv_1/PTModelSprite_ID58593.png", "res/BlackPink/character/jump/nv_1/PTModelSprite_ID%d.png", 58593,58593, 0},
            {"JUMP_DOWN_1", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/nv_1/PTModelSprite_ID58594.png", "res/BlackPink/character/jump/nv_1/PTModelSprite_ID%d.png", 58594,58594, 0},
            {"RELEAX_1", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58592.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58592,58595, -1},
            {"DIE_1", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58596.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58596,58596, 0}

        };

        break;
    }
    case 2:
    {
        _dataAnimCharater = {
            {"RUN_2", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58668.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58668,58674, -1},
            {"JUMP_2_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID62581.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62581,62581, 0},
            {"JUMP_2_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID62582.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62582,62582, 0},
            {"RELEAX_2", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58659.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58659,58662, -1},
            {"DIE_2", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58660.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58660,58660, 0}
        
        };

        break;
    }
    case 3:
    {
        _dataAnimCharater = {
            {"RUN_3", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58636.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58636,58641, -1},
            {"JUMP_3_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID62678.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62678,62678, 0},
            {"JUMP_3_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID62679.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62679,62679, 0},
            {"RELEAX_3", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58627.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58627,58630, -1},
            {"DIE_3", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58644.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58644,58644, 0}

        };

        break;
    }
    case 4:
    {
        _dataAnimCharater = {
            {"RUN_4", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58700.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58700,58705, -1},
            {"JUMP_4_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID62658.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62658,62658, 0},
            {"JUMP_4_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID62659.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62659,62659, 0},
            {"RELEAX_4", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58691.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58691,58694, -1},
            {"DIE_4", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58692.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58692,58692, 0}
        };
        break;
    }
    case 5:
    {
        _dataAnimCharater = {
            {"RUN_5", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63292.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63292,63297, -1},
            {"JUMP_5_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID63246.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63246,63246, 0},
            {"JUMP_5_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID63247.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63247,63247, 0},
            {"RELEAX_5", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63238.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63238,63241, -1},
            {"DIE_5", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID63239.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 63239,63239, 0}
        };

        break;
    }
    case 6:
    {
        _dataAnimCharater = {
            {"RUN_6", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58732.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58732,58737, -1},
            {"JUMP_6_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID62663.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62663,62663, 0},
            {"JUMP_6_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID62664.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62664,62664, 0},
            {"RELEAX_6", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58723.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58723,58726, -1},
            {"DIE_6", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58724.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58724,58724, 0}
        };

        break;
    }
    case 7:
    {
        _dataAnimCharater = {
            {"RUN_7", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63303.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63303,63308, -1},
            {"JUMP_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID63266.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63266,63266, 0},
            {"JUMP_7_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID63267.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63267,63267, 0},
            {"RELEAX_7", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID63257.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 63257,63260, -1},
            {"DIE_7", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID63258.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 63257,63258, 0}
        };

        break;
    }
    case 8:
    {
        _dataAnimCharater = {
            {"RUN_8", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID58764.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 58764,58769, -1},
            {"JUMP_8_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID62666.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62666,62666, 0},
            {"JUMP_8_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID62667.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 62667,62667, 0},
            {"RELEAX_8", StatusNV::RELEAX, "res/BlackPink/character/releax/PTModelSprite_ID58755.png", "res/BlackPink/character/releax/PTModelSprite_ID%d.png", 58755,58758, -1},
            {"DIE_8", StatusNV::DIE, "res/BlackPink/character/die/PTModelSprite_ID58756.png", "res/BlackPink/character/die/PTModelSprite_ID%d.png", 58756,58756, 0}
        };

        break;
    }
    case 9:
    {
        _dataAnimCharater = {
            {"RUN_9", StatusNV::RUN, "res/BlackPink/character/run/PTModelSprite_ID63313.png", "res/BlackPink/character/run/PTModelSprite_ID%d.png", 63313,63318, -1},
            {"JUMP_9_UP", StatusNV::JUMP_UP, "res/BlackPink/character/jump/PTModelSprite_ID63287.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63287,63287, 0},
            {"JUMP_9_DOWN", StatusNV::JUMP_DOWN, "res/BlackPink/character/jump/PTModelSprite_ID63288.png", "res/BlackPink/character/jump/PTModelSprite_ID%d.png", 63288,63288, 0},
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
    _character->getPhysicsBody()->setEnabled(false);
    gameOver(_score);
}

void SFGameScene::OnMoveLeft()
{
    isMoveLeft = true;
    isMoveRight = false;
    CCLOG("Left arrow key is pressed.");
    _character->setScaleX(-std::abs(_character->getScaleX()));
    _currentStatusNv = StatusNV::RUN;
}

void SFGameScene::OnMoveRight()
{
    isMoveRight = true;
    isMoveLeft = false;
    CCLOG("Right arrow key is pressed.");
    _character->setScaleX(std::abs(_character->getScaleX()));
    _currentStatusNv = StatusNV::RUN;
}

void SFGameScene::OnJump()
{
    isMoveUp = true;
    CCLOG("Up arrow key is pressed.");
    if (_numJum >= 2)
    {
        return;
    }
    SOUND_MANAGER->playJump();
    _numJum++;
    _character->getPhysicsBody()->setVelocity(Vec2(_character->getPhysicsBody()->getVelocity().x, 550));
    _currentStatusNv = StatusNV::JUMP_UP;
    _character->scheduleOnce([this](float dt) {
        //   _currentStatusNv = StatusNV::RELEAX;

        }, 1.0f, "delay_change_state");

    auto py = _character->getPhysicsBody();

    _character->schedule([=](float dt) {
        //   _currentStatusNv = StatusNV::RELEAX;
        CCLOG("NHAAN__%f___%f", py->getVelocity().x, py->getVelocity().y);

        if (py->getVelocity().y < 0)
        {
            _character->unschedule("delay_change_state1");
            _currentStatusNv = StatusNV::JUMP_DOWN;
        }

        }, "delay_change_state1");
}

void SFGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    float x = 350, y = 550;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        OnJump();
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        CCLOG("Down arrow key is pressed.");
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        OnMoveLeft();
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        OnMoveRight();
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
        _currentStatusNv = isMoveRight ? OnResetSateNv() : StatusNV::RELEAX;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        isMoveRight = false;
        CCLOG("Right arrow key is released.");
        _character->unschedule("check_run_charater");
        _currentStatusNv = isMoveLeft ? OnResetSateNv() : StatusNV::RELEAX;
        break;
    default:
        break;
    }
}

bool SFGameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{

    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    int aCollision = a->getCollisionBitmask();
    int bCollision = b->getCollisionBitmask();

    if ((COLLISION_NV == aCollision && COLLISION_TUONG == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG == aCollision))
    {
        _numJum = 0;
        _isRun = false;
        _character->unschedule("delay_down");
        if (_currentStatusNv == OnResetSateNv())
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
    else if ((COLLISION_NV == aCollision && COLLISION_TUONG_DIE == bCollision) || (COLLISION_NV == bCollision && COLLISION_TUONG_DIE == aCollision))
    {
        if (COLLISION_TUONG_DIE == aCollision)
        {
            auto parent = a->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndTuongDie(parent);
            }
        }
        else {
            auto parent = b->getOwner();
            if (parent != nullptr)
            {
                OnCollisionCharaterAndTuongDie(parent);
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

void SFGameScene::OnCollisionCharaterAndTuongDie(Node* node)
{
    if (auto sp = node->getChildByName("mushroom_run_die"))
    {
        sp->getPhysicsBody()->setEnabled(false);
    }
    node->scheduleOnce([=](float dt) {
       
        OnGameOver();

        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndNam(Node* nam)
{
    nam->getParent()->getPhysicsBody()->setEnabled(false);
    nam->scheduleOnce([=](float dt) {

        auto parent = nam->getParent();

        SOUND_MANAGER->chooseCorect();

        auto sp = Sprite::create("res/BlackPink/animation/enemy/mushroom/mushrom_world_1/mushroom_die.png");
        sp->setPosition(parent->getPosition());
        sp->setAnchorPoint(parent->getAnchorPoint());
        parent->getParent()->addChild(sp);
        sp->setScaleY(parent->getScaleY());
        sp->setScaleX(parent->getScaleX());
        sp->scheduleOnce([=](float dt) {
            sp->removeFromParent();
            }, 0.5f, "OnCollisionCharaterAndNam");

        parent->removeFromParent();


        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndDiamon(Node* diamon)
{
    diamon->scheduleOnce([=](float d) {
        SOUND_MANAGER->chooseCorect();
        updateDiamond(1);

        auto anim = GetAnim(Anim::DIAMOND);
        anim->setPosition(diamon->getPosition());
        anim->setAnchorPoint(diamon->getAnchorPoint());
        diamon->getParent()->addChild(anim);

        anim->scheduleOnce([=](float d) {
            anim->removeFromParent();
            }, 0.05 * 8, "OnCollisionCharaterAndNam");


        diamon->removeFromParent();

        }, 0.005f, "OnCollisionCharaterAndNam");
}

void SFGameScene::OnCollisionCharaterAndChiaKhoa(Node* ck)
{
    ck->scheduleOnce([=](float d) {
        ck->removeFromParent();
        SOUND_MANAGER->chooseCorect();
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

        auto anim = GetAnim(Anim::GET_NOTE);
        anim->setPosition(ck->getPosition());
        anim->setAnchorPoint(ck->getAnchorPoint());
        ck->getParent()->addChild(anim);

        anim->scheduleOnce([=](float d) {
            anim->removeFromParent();
            }, 0.05 * 11, "scheduleOnce");

        ck->removeFromParent();
        SOUND_MANAGER->chooseCorect();
        updateScore(1);
    }, 0.005f, "OnCollisionCharaterAndNhac");
}

void SFGameScene::OnCollisionCharaterAndXuongRong()
{
    _character->scheduleOnce([=](float d) {
        OnGameOver();
        }, 0.005f, "OnCollisionCharaterAndNam");
}

cocos2d::ui::Widget::ccWidgetClickCallback SFGameScene::onLocateClickCallback(const std::string& callBackName)
{
    std::unordered_map<std::string, ui::Widget::ccWidgetClickCallback> function_map =
    {
        CLICK_MAP(SFGameScene, onPauseButtonClicked),
        CLICK_MAP(SFGameScene, onSoundButtonClicked),
        CLICK_MAP(SFGameScene, onMusicButtonClicked),
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
            "MUSHROM_WORD_1", "res/BlackPink/animation/enemy/mushroom/mushrom_world_1/mushroom_run_%d.png", 1, 4, 0.1f, -1);
        break;
    case Anim::DIAMOND:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/get_diamond/animation_get_dianond01.png",
            "DIAMOND", "res/BlackPink/animation/get_diamond/animation_get_dianond0%d.png", 1, 7, 0.05f, -1);
        break;
    case Anim::NOTE:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/note/animation_note00.png",
            "NOTE", "res/BlackPink/animation/note/animation_note0%d.png", 0, 13, 0.05f, -1);
        break;
    case Anim::GET_NOTE:
        sprite = HELPER_MANAGER->getAnimateSprite("res/BlackPink/animation/get_note/animation_get_note01.png",
            "GET_NOTE", "res/BlackPink/animation/get_note/animation_get_note0%d.png", 1, 7, 0.1f, -1);
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

void SFGameScene::onSoundButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();

    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);

    UserDefault::getInstance()->setBoolForKey(IS_SOUND_KEY_ON, !isSoundOn);

    button->loadTextureNormal(StringUtils::format("res/BlackPink/button_world/button_world_1/bis_button_sound_%s_world_1.png", !SOUND_MANAGER->isSoundEffectEnable() ? "off" : "on"));

}

void SFGameScene::onMusicButtonClicked(cocos2d::Ref* sender)
{
    SOUND_MANAGER->playClickEffect();

    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);

    UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, !isSoundOn);

    if (SOUND_MANAGER->isMusicEffectEnable()) {

        SOUND_MANAGER->resumeAllBackgroundMusics();
    }
    else
    {
        SOUND_MANAGER->pauseAllBackgroundMusics();
    }
    button->loadTextureNormal(StringUtils::format("res/BlackPink/button_world/button_world_1/bis_button_music_%s_world_1.png", !SOUND_MANAGER->isMusicEffectEnable() ? "off" : "on"));

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

    this->unschedule("delay_update_level");

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

