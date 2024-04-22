#pragma once

#include "cocos2d.h"
#include "CocostudioMacro.h"
#include "BaseSingleton.h"
#include "spine/SkeletonAnimation.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "ensRippleNode.h"
using namespace ens;
using namespace cocos2d;

enum StatusNV
{
    DEFAULT,
    RELEAX, 
    RUN,
    JUMP,
    DIE
};

enum class Anim {
    DEFAULT,
    NV_1,
    MUSHROM_WORD_1,
    DIAMOND,
    GET_NOTE,
    KEY,
    MUSIC,
};

struct DataPathAnim {

    string _pathSpr = "";
    string _pahtAnim = "";
    int _numStart = 0;
    int _numnEnd = 0;
    string _nameAnim = "";
    StatusNV _state = StatusNV::DEFAULT;
    int _loop = -1;
   
    DataPathAnim() {}

    DataPathAnim(string nameAnim, StatusNV state, std::string pathSpr, std::string pathAnim, int numStart, int numEnd, int loop) {
        _pahtAnim = pathAnim;
        _pathSpr = pathSpr;
        _numStart = numStart;
        _numnEnd = numEnd;
        _state = state;
        _nameAnim = nameAnim;
        _loop = loop;
    }
};

#define COLLISION_NV 10
#define COLLISION_TUONG 20
#define COLLISION_ENEMY 12
#define COLLISION_DIAMOND 13
#define COLLISION_XUONG_RONG 14
#define COLLISION_CHIA_KHOA 15
#define COLLISION_NHAC 17
#define COLLISION_OBJ_DIE 18




class SFGameScene : public cocos2d::ui::Layout, public cocostudio::WidgetCallBackHandlerProtocol
{
public:

    CREATE_FUNC(SFGameScene);

    static cocos2d::Scene* createScene();

    static SFGameScene* createView();//1.

    void onGamePause();
    void onGameResume();
    void onPauseOrResumNode(Node* node, bool isPause);
    void OnGameWin(int score);
    void gameOver(int score);

private:

    void didLoadFromCSB();
    void onPauseButtonClicked(cocos2d::Ref* sender);
    void onSoundButtonClicked(cocos2d::Ref* sender);
    void onMusicButtonClicked(cocos2d::Ref* sender);
    void updateTime(float dt);
    void updateLevel(bool isLevelup = false);
    void updateScore(int scoreAdd);
    void updateDiamond(int scoreAdd);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string& callback_name) override;//3.

    Sprite* GetAnim(Anim anim);

    void SetUpdataLevel();
    void SetDataCurrentLevel(int level_id);
    void RunAnimNv();

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onContactSeparate(PhysicsContact& contact);
    bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
    void update(float dt);
    void OnGameOver();

    void OnCollisionCharaterAndNam(Node* nam);
    void OnCollisionCharaterAndDiamon(Node* diamon);
    void OnCollisionCharaterAndChiaKhoa(Node* ck);
    void OnCollisionCharaterAndNhac(Node* ck);
    void OnCollisionCharaterAndXuongRong();

    void CreateMap(TMXTiledMap* map);
    void SetDataAnimForCharater();
    DataPathAnim GetCurrentAnimCharater();

    //////

/// <summary>
/// 
/// </summary>
/// 
/// 
/// 
/// 
/// 
    void RunActionCharator(Anim anim);
    void getGroupNameByPoint(std::string name, std::string pathSr, int collison, float scale = 0.5f);
    Sprite* CreateObject(std::string path, Vec2 point, std::string nameSprite = "", int collison = 0, Anim anim = Anim::DEFAULT);

    void updateLabel(std::string labelName, std::string data);

    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
        _physicSceneWorld = world;
    }

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:

    cocos2d::Size           _screenSize;
    cocos2d::Vec2           _origin;
    bool                    _isUpdate = false;
    cocos2d::PhysicsWorld* _physicSceneWorld;
    int                     _score = 0;
    int                     _Diamond = 0;
    bool                    _isGameOver = false;
    bool _isSetHp = true;


    cocos2d::Node* _bar = nullptr;
    cocos2d::Node* _root = nullptr;
    cocos2d::ui::ImageView* _levelBar = nullptr;

    cocos2d::Size _catSize;

    bool _isHitFirstDame = false;

    int _currentLevelID = 0;

    //////
    bool _isGamePlay = false;

    Sprite* _character;

    float _speed = 250.0f;
    float _gravity = 350.0f;
    std::chrono::steady_clock::time_point _clickStartTime;
    Vec2 _currentPointVelocity;


    bool _isUseSkillTime = false;
    LoadingBar* _loadingBarFrog = nullptr;

    Node* _NStar = nullptr;

    int _scroreAdd = 0;

    int _numSkillHammer = 0;
    int _numSkillKhien = 0;
    int _numSkillFrog = 0;
    int _numStar = 0;

    bool _isUseSkillHammer = false;
    bool _isUseSkillKhien = false;
    bool _isUseSkillFrog = false;

    bool _isJump = false;
    bool _isCkick = false;

    float pointX = 0.0f;
    float _timer = 0.0f;

    /// <summary>
    /// 
    /// </summary>
    TMXTiledMap* _tileMap = nullptr;
    TMXTiledMap* _mapBg = nullptr;

    int _numJum = 0;    
    bool _isRun = false;
    Vec2 _currentVelocity = Vec2(0, 0);
    int _indexJump = 0;
    bool isMoveLeft = false;
    bool isMoveRight = false;
    bool isMoveUp = false;
    bool isMoveDowh = false;
    float _pointX = 0;  
    std::vector<Node*> _listMapBg = {};
    int _indexMap = 0;
    Node* root_layout = nullptr;
    std::vector<Node*> _listTuong = {};
    StatusNV _currentStatusNv = StatusNV::RELEAX;
    StatusNV _NewStatusNv = StatusNV::DEFAULT;
    int _currentIdCharater = 1;

    std::vector<DataPathAnim> _dataAnimCharater;

    int _currentCoin = 0;
    int _currentGem = 0;

};

CREATE_READER(SFGameScene);
