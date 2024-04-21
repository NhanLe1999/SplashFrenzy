//
// Created by ThangNguyen on 23/10/2023.
//
#pragma one
#include "cocos2d.h"
#include "../lib/BaseSingleton.h"
struct DataScorePlayer
{
    int score;
    int lv;
    std::string name;
    DataScorePlayer(){
        score = 0;
        lv = 0;
        name = "User";
    }
    DataScorePlayer(int s, int l, std::string n){
        score = s;
        lv = l;
        name = n;
    }
};class BPGameManager : public BaseSingleton<BPGameManager> {
public:

	bool initHightScore();
	int getMaxScore();
	void addScore(int score, std::string name, int lv);
	void saveHightScoreToLocal();
	std::vector<DataScorePlayer> getListDataScore();
	std::vector<DataScorePlayer> _listHightScore;
	int _currentLv;
	int _forceLv;
	int _currentSocre;
	int _heart;
};
