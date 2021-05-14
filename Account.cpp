#include "Account.h"

Account::Account()
{

}

Account::Account(int numFail_, string id_, string name_, string user_name_, string password_, int money_, string timeCreat_)
{
	id = id_;
	name = name_;
	user_name = user_name_;
	password = password_;
	money = money_;
	timeCreat = timeCreat_;
	numFail = numFail_;
	logSuccess = false;
	if (numFail > 3) active = false;
	else active = true;
	history = to_string(stoi(id) % 8) + user_name + ".txt";
}

Account::~Account()
{
}

void Account::creatData(string name_, string username_, string password_)
{
	name = name_;
	user_name = username_;
	password = password_;
	money = 0;
	active = true;
	id = to_string(rand() % 1000000);
	timeCreat = getTimeNow();
	numFail = 0;
	logSuccess = false;
	history = to_string(stoi(id) % 8) + user_name + ".txt";
}

void Account::print()
{
	system("cls");
	cout << "\n-----------------------------------------\nTime creat: " << timeCreat << endl;
	cout <<"ID: "<< id << "\nName: " << name << "\nAccount Balance: " << money << endl;
	cout << "-----------------------------------------\n";
}

void Account::writeToSource(string gt)
{
	fstream file;
	file.open("Account.txt", ios::app);
	if (file.is_open()) {
		file << numFail << "." << id << "." << name << "." << user_name << "." << password << "." << money << "." << gt << ".";
	}
	file.close();
}

void Account::writeStatus(string s)
{
	fstream f;
	f.open(history.c_str(), ios::app);
	f << getTimeNow() << endl << s << "\n----------------------------\n";
	f.close();
}

bool Account::checkPass(string pw) {
	numFail += 1;
	if (numFail > 3) {
		active = false;
		writeStatus("Account locked!");
		return false;
	}
	if (pw == password) {
		logSuccess = true;
		writeStatus("Login Successfully");
		numFail = 0;
		return true;
	}
	writeStatus("Login Fail");
	return false;
}

void Account::showHistory()
{
	system("cls");
	ifstream file(history.c_str(), ios::in);
	if (file.is_open()) {
		while (!file.eof()) {
			string s;
			getline(file, s);
			cout << s << endl;
		}
		file.close();
	}
	
}

bool Account::deposit(int tg)
{
	money += tg;
	writeStatus("+" + to_string(tg) + ", Account Balance: " + to_string(money));
	return tg;
}

bool Account::sendMoney(int sm)
{
	if (sm <= money) {
		money -= sm;
		writeStatus("-" + to_string(sm) + ", Account Balance: " + to_string(money));
		return true;
	}
	else return false;
}

bool Account::recieveMoney(int sml)
{
	if (sml > 0) {
		money += sml;
		writeStatus("+" + to_string(sml) + ", Account Balance: " + to_string(money));
		return true;
	}
	else return false;
}
