#include"speechManager.h"

int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	sm.loadRecord();
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
	//	cout << it->second.name << " " << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice) {
		case 1:  //开始比赛
			sm.startSpeech();
			break;
		case 2:	//查看往届比赛记录
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default://清屏
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}