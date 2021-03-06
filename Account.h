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
	int numFail;
	bool logSuccess;

public:
	Account();
	Account(int numFail_, string id_, string name_, string user_name_, string password_, int money_, string timeCreat_);
	~Account();
	void creatData(string name_, string username_, string password_);
	void print();
	void writeToSource(string st);
	void writeStatus(string s);
	bool checkPass(string pw);
	void showHistory();
	bool deposit(int tg);
	bool sendMoney(int sm);
	bool recieveMoney(int sm);
	bool checkAccount(string s);

	string getDateCreat() const { return timeCreat; }
	//string getUserName() const { return user_name; }
	bool checkActive() const { return numFail <= 3; }
	bool loginSuccess() const { return logSuccess; }
	int getAccountBalance() const { return money; }
};