#include "BPGameManager.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"

bool BPGameManager::initHightScore() {
	_currentLv = 0;
	_currentSocre = 0;
	std::string data = UserDefault::getInstance()->getStringForKey("dataScore", "");
	rapidjson::Document doc;
	if( data.empty()) return false;
	doc.Parse<0>(data.c_str());
	if (doc.HasParseError()) {
		CCLOG("data json error");
		return false;
	}
	_listHightScore.clear();
	for (int i = 1; i <= 100; i++)
	{
		std::string st = StringUtils::format("st%d", i);
		if (doc.HasMember(st.c_str()))
		{
			auto ob = doc[st.c_str()].GetObject();
			auto name = ob["Name"].GetString();
			auto score = ob["Score"].GetInt();
			int lv = 1;
			if (ob.HasMember("Lv"))
			{
				lv = ob["Lv"].GetInt();
			}
			DataScorePlayer data;
			data.score = score;
			data.name = name;
			data.lv = lv;
			_listHightScore.push_back(data);
		}
        else break;
	}
	return true;
}
int BPGameManager::getMaxScore() {
    if(_listHightScore.empty()) return -1;
	return _listHightScore.at(0).score;
}
void  BPGameManager::addScore(int score, std::string name, int lv) {
	DataScorePlayer data;
	data.score = score;
	data.name = name;
	data.lv = lv;
    if(_listHightScore.empty())
    {
        _listHightScore.push_back(data);
        saveHightScoreToLocal();
        return;
    }
    int size = _listHightScore.size();
    size = std::min(size, 100);
	int insertIndex = -1;

	for (int i = 0; i < size; i++) {
		if (score > _listHightScore[i].score) {
			insertIndex = i;
			break;
		}
	}
    if(insertIndex == -1)
    {
        if(_listHightScore.size()>=100) return;
        _listHightScore.push_back(data);

    }
    else
        _listHightScore.insert(_listHightScore.begin() + insertIndex, data);
    saveHightScoreToLocal();

}
void BPGameManager::saveHightScoreToLocal() {
	std::string jsonResult = "{";
    int size = std::min((int)_listHightScore.size(), 100);
	for (size_t i = 0; i < size; ++i) {
		if (i > 0) {
			jsonResult += ",";
		}
		jsonResult += "\"st" + std::to_string(i + 1) + "\":{";
		jsonResult += "\"Name\":\"" + _listHightScore[i].name + "\",";
		jsonResult += "\"Lv\":" + std::to_string(_listHightScore[i].lv) + ",";
		jsonResult += "\"Score\":" + std::to_string(_listHightScore[i].score);
		jsonResult += "}";
	}
	jsonResult += "}";
	UserDefault::getInstance()->setStringForKey("dataScore", jsonResult);
}
std::vector<DataScorePlayer> BPGameManager::getListDataScore() {
	return _listHightScore;
}
