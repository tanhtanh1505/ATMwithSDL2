#pragma once
#include"ta.h"

using namespace TA;

class Account
{
private:
	string name;
	string user_name;
	string password;
	string id;
	string timeCreat;
	string history;
	int money;
	bool active;
	int numFail;
	bool logSuccess;

public:
	Account();
	Account(int numFail_, string id_, string name_, string user_name_, string password_, int money_, string timeCreat_);
	~Account();
	void creatData(string name_, string username_, string password_);
	string getDateCreat() { return timeCreat; }
	void print();
	void writeToSource(string st);
	void writeStatus(string s);
	string getUserName() { return user_name; }
	bool checkPass(string pw);
	bool checkActive() { return active; }
	bool loginSuccess() { return logSuccess; }
	void showHistory();
	bool deposit(int tg);
	bool sendMoney(int sm);
	bool recieveMoney(int sm);
	int getAccountBalance() { return money; }
};