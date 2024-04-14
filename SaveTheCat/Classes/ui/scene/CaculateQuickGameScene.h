#pragma once

#include "CaculateQuickCocostudioMacro.h"
#include "spine/SkeletonAnimation.h"
#include "LevelGamePlay.h"



using namespace spine;
using namespace cocos2d;

#define KEY_SAVE_LEVEL "key_current_level_save"
#define KEY_CURENT_LEVEL "key_current_level_"
#define KEY_SAVE_NUM_DICE "key_save_num_dice"
#define KEY_SAVE_NUM_TIME "key_save_num_time"
#define KEY_SAVE_NUM_HEAERT "key_save_num_heart"
#define KEY_SAVE_LEVEL_START "key_save_level_start_"
#define KEY_STAR_LEVEL "key_Star_level_%d"

#define KEY_SKILL_KHIEN "key_skill_khien"
#define KEY_SKILL_HAMMER "key_skill_hammer"
#define KEY_SKILL_FROG "key_skill_frog"

#define COLLISION_NV 10
#define COLLISION_GO 11
#define COLLISION_NAM 12
#define COLLISION_GO_TRON 13
#define COLLISION_GO_DIC 14
#define COLLISION_GO_MUC 15
#define COLLISION_SEN 16    
#define COLLISION_NC 17
#define COLLISION_SAO 18
#define COLLISION_COIN 19

#define TIME_SKILL_BAR 2.0f

#define KEY_THE_FIRST "key_the_first"



enum class Anim {
    COIN,
    FROG_JUMP,
    FROG_RELAX,
    SPARK,
    STAR,
    WATER,
    WIN,
};

enum State
{
    RELAX,
    JUMP
};


class CaculateQuickGameScene : public cocos2d::ui::Layout,public cocostudio::WidgetCallBackHandlerProtocol 
{
public:
   
    CREATE_FUNC(CaculateQuickGameScene);

    static cocos2d::Scene* createScene();
    
    static CaculateQuickGameScene* createView();//1.
        
    void onGamePause();
    void onGameResume();
    void OnUpdateNumSkillGame();
    void onPauseOrResumNode(Node* node, bool isPause);
    void OnGameWin(int score);
    void gameOver(int score);

private:
    
    void didLoadFromCSB();
    void onPauseButtonClicked(cocos2d::Ref* sender);
    void updateTime(float dt);
    void updateLevel(bool isLevelup = false);
    void updateScore(int scoreAdd);

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string & callback_name) override;//3.

    Sprite* GetAnim(Anim anim);

    void onSkillHammer(cocos2d::Ref* sender);
    void onSkillKhien(cocos2d::Ref* sender);
    void onSkillFrog(cocos2d::Ref* sender);
    void onShopButtonClicked(cocos2d::Ref* sender);

    void SetUpdataLevel();
    void SetDataCurrentLevel(int level_id);
    void RunAnimNv(Anim anim);

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
    void getGroupNameByPoint(std::string name, std::string pathSr, int collison);
    Sprite* CreateObject(std::string path, Vec2 point, std::string nameSprite = "", int collison = 0);


    void updateLabel(std::string labelName, std::string data);

    void UpdateTextSkillHammer();
    void UpdateTextSkillKhien();
    void UpdateTextSkillFrog();


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
    bool                    _isGameOver = false;
    bool _isSetHp = true;


    cocos2d::Node* _bar = nullptr;
    cocos2d::Node* _root = nullptr;
    cocos2d::ui::ImageView* _levelBar = nullptr;

    cocos2d::Size _catSize;

    bool _isHitFirstDame = false;

    int _currentLevelID = 0;

    std::vector<LevelConfig> _levels;
    LevelConfig _currentLevelConfig;

    //////
    bool _isGamePlay = false;

    Sprite* _character;

    float _speed = 250.0f;
    float _gravity = 350.0f;
    std::chrono::steady_clock::time_point _clickStartTime;
    Vec2 _currentPointVelocity;

    State _currentFrogState = State::RELAX;
    LevelGamePlay* _levelGame = nullptr;

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

    TMXTiledMap* _tileMap = nullptr;


};

CREATE_READER(CaculateQuickGameScene);

