#pragma once

#include "CaculateQuickCocostudioMacro.h"

struct InfoItem
{
    int a = 0;
    std::string allow1 = "";
    int b = 0;
    std::string allow2 = "";
    int c = 0;
    std::string allow3 = "";
    int d = 0;

    InfoItem() {}
};

struct LevelConfig {

    int _levelID = 1;

    int _max = 0;
    int _min = 0;

    std::vector<std::string> _listAllow = { "+", "-", "x" };

    LevelConfig() {}

    LevelConfig(int min, int max, std::vector<std::string> listAllow) {
        _min = min;
        _max = max;
        _listAllow = listAllow;
    }
};

struct DataButton
{
    int _typeBtn = -1;
    std::string _pathSpineWin = "";
    std::string _pathThanNormal = "";
    std::string _pathDauNormal = "";
    std::string _pathDichNormal = "";
    std::string _pathThanWin = "";
    std::string _pathDauWin = "";
    std::string _pathDichWin = "";
    std::string _pathRe = "";

    DataButton()
    {

    }

    DataButton(int typeBtn, std::string pathSpineWin, std::string pathThanNormal,std::string pathDauNormal,std::string pathDichNormal,std::string pathThanWin,std::string pathDauWin, std::string pathDichWin, std::string pathRe )
    {
        _typeBtn = typeBtn; 
        _pathSpineWin = pathSpineWin;
        _pathThanNormal = pathThanNormal;
        _pathDauNormal = pathDauNormal;
        _pathDichNormal = pathDichNormal;
        _pathThanWin = pathThanWin;
        _pathDauWin = pathDauWin;
        _pathDichWin = pathDichWin;
        _pathRe = pathRe;
    }
};


class LevelGamePlay : public cocos2d::ui::Layout, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
    CREATE_FUNC(LevelGamePlay);

    static cocos2d::Scene *createScene();

    static LevelGamePlay *createView(int id); // 1.

    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string& callback_name) override;//3.

    ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string& callback_name) override;
    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type);
    void SetDataLevelConfig(LevelConfig lv);
    void SetDataForGame();
    InfoItem GetDataForGame(int numAllow, int min, int max, std::vector<std::string> listAllow);
    int GetResult(int a, int b, std::string allow);
    void CheckComlete(bool ischeckEndGamne);
public:

private:
    void didLoadFromCSB();
    void SetDataForResult(std::vector<int> listResult);
    void SetRotationForParent(Node* n);
    void OnGameWin();
    void RunActionWin(Node* node, std::function<void()> callback, float time);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);


private:

    std::vector<Node*> _listNResult= {};
    std::vector<Node*> _listNPhysic = {};

    std::vector<std::pair<bool, Node*>> _listNDich;

    Vec2 _PointBegin;
    Node* _nodeCurrentDrag = nullptr;

    std::vector<Node*> _listNode = {};
    LevelConfig _currentLevelConfig;

    std::vector<std::pair<Node*, std::vector<Node*>>> _dataCalulator;

    std::vector<DataButton> _dataButton;



};

CREATE_READER(LevelGamePlay);
