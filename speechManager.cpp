#include"speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
}

void SpeechManager::show_Menu() {
	cout << "****************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 ***********" << endl;
	cout << "***********  1.开始演讲比赛  ***********" << endl;
	cout << "***********  2.查看往届记录  ***********" << endl;
	cout << "***********  3.清空比赛记录  ***********" << endl;
	cout << "***********  0.退出比赛程序  ***********" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i+10001, sp));
	}
}

void SpeechManager::startSpeech() {
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->m_Index++;
	//第二轮比赛开始
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->saveRecord();
	this->loadRecord();
	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "------------------------" << endl;
	cout << "抽签后演讲顺序如下" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout<<"------------------------";
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest() {
	cout << "-------------第" << this->m_Index << "轮比赛正式开始--------------" << endl;
	vector<int>v_Src;
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//6人一组
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		deque<double>d;
		num++;
		for (int i = 0; i < 10;i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum /= (double)d.size();
		//cout << "编号:" << *it << " 选手：" << this->m_Speaker[*it].name << " 获取平均分：" << avg << endl;
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		//每6人取出前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				cout << "编号：" << mit->second << " 姓名：" << this->m_Speaker[mit->second].name << " 得分：" << this->m_Speaker[mit->second].m_Score[this->m_Index-1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end() && count < 3; mit++, count++) {
				if (this->m_Index == 1) {
					v2.push_back(mit->second);
				}
				else {
					victory.push_back(mit->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "---------------第" << this->m_Index << "轮比赛完毕！------------------" << endl;
	system("pause");
}

void SpeechManager::showScore() {
	cout << "-------------第" << this->m_Index << "轮晋级选手信息如下--------------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].name << " 得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->victory.begin(); it != this->victory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
	ifstream ifs;
	ifs.open("speech.csv",ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data) {
		/*cout << data << endl;*/
		int pos = -1;
		int start = 0;
		vector<string>v;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			start = pos + 1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	//for (map<int,vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++) {
	//	cout << it->first << "冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl;
	//}
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空或者不存在" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1]
				<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3]
				<< "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "是否确定清空文件" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager() {

}