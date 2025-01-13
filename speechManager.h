#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<ctime>
#include<fstream>
using namespace std;

class SpeechManager {
public:
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void createSpeaker();
	~SpeechManager();
	void initSpeech();
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void showRecord();
	void clearRecord();
	bool fileIsEmpty;
	map<int, vector<string>>m_Record;
	vector<int>v1;//保存第一轮比赛选手容器
	vector<int>v2;//第一轮晋级选手容器
	vector<int>victory;//胜出前三名选手容器
	map<int, Speaker>m_Speaker;//存放编号以及对应具体选手容器
	int m_Index;//比赛轮数
};