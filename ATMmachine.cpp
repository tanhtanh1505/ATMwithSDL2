#include "ATMmachine.h"

void ATM::initDaTa(vector<Account> &list_account, int bank[], vector<NumberButton>& obn, vector<MenuButton>& obb)
{
	list_account.erase(list_account.begin(), list_account.end());
	ifstream file("Account.txt");
	if (file.is_open()) {
		string nf, id, username, name, password, mo, timecreat;
		while (getline(file, nf, '.')) {
			getline(file, id, '.');
			getline(file, name, '.');
			getline(file, username, '.');
			getline(file, password, '.');
			getline(file, mo, '.');
			getline(file, timecreat, '.');
			Account p(stoi(nf), id, name, username, password, stoi(mo), timecreat);
			list_account.push_back(p);
		}
		file.close();
	}
	ifstream fi("Bank.txt");
	if (fi.is_open()) {
		int e, f;
		while (!fi.eof() && fi >> e >> f) {
			bank[e] = f;
		}
		fi.close();
	}

	obn.at(0).setRect(300, 665);
	obn.at(1).setRect(254, 600);
	obn.at(2).setRect(304, 600);
	obn.at(3).setRect(354, 600);
	obn.at(4).setRect(250, 620);
	obn.at(5).setRect(302, 620);
	obn.at(6).setRect(354, 620);
	obn.at(7).setRect(246, 642);
	obn.at(8).setRect(300, 642);
	obn.at(9).setRect(354, 642);
	obn.at(10).setRect(415, 600);
	obn.at(10).setSize(70, 13);
	obn.at(11).setRect(415, 620);
	obn.at(11).setSize(70, 13);
	obn.at(12).setRect(417, 641);
	obn.at(12).setSize(70, 13);

	obb.at(0).setRect(82, 249);
	obb.at(1).setRect(82, 285);
	obb.at(2).setRect(82, 323);
	obb.at(3).setRect(82, 360);
	obb.at(4).setRect(471, 360);
}

void ATM::selectMenu(SDL_Renderer* renderer, SDL_Event event, vector<MenuButton>& obb, int& choose, Mix_Chunk*& soundbeep)
{
	for (int ib = 0; ib < obb.size(); ib++) {
		if (obb.at(ib).clicked(event)) {
			Mix_PlayChannel(-1, soundbeep, 0);
			SDL_Delay(200);
			choose = ib + 1;
			break;
		}

	}
}

bool ATM::creatAccount(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<Account>& list_account, Mix_Chunk*& soundbeep)
{
	string name_, username_, password_;
	Inputer namei, usernamei, passwordi;
	SDL_Texture* creatacc = loadTexture(renderer, "yourname.png");

	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
			}
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, creatacc, NULL, NULL);

		namei.showInput(renderer, 265, 240);
		namei.readNumberInput(event, obn, soundbeep);
		if (namei.done()) {
			name_ = namei.getInput();
			creatacc = loadTexture(renderer, "creatusername.png");
			break;
		}

		SDL_RenderPresent(renderer);
	}
XXX:
	usernamei.setDone(false);
	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
			}
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, creatacc, NULL, NULL);

		usernamei.showInput(renderer, 265, 240);
		usernamei.readNumberInput(event, obn, soundbeep);
		if (usernamei.done()) {
			username_ = usernamei.getInput();
			break;
		}

		SDL_RenderPresent(renderer);
	}
	for (auto x : list_account) {
		if (x.checkAccount(username_)) {
			renderError(renderer, "acexist.png");
			goto XXX;
		}
	}
	
	creatacc = loadTexture(renderer, "creatpassword.png");

	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
			}
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, creatacc, NULL, NULL);

		passwordi.showInput(renderer, 265, 240);
		passwordi.readNumberInput(event, obn, soundbeep);
		if (passwordi.done()) {
			password_ = passwordi.getInput();
			break;
		}

		SDL_RenderPresent(renderer);
	}

	Account p;
	p.creatData(name_, username_, password_);
	p.print();
	p.writeToSource(getTimeNow());
	p.writeStatus("Account is created!");
	list_account.push_back(p);
	Inputer input;
	creatacc = loadTexture(renderer, "creatsuccess.png");
	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, creatacc, NULL, NULL);
		if (input.readNumberInput(event, obn, soundbeep) == false) return true;
		SDL_RenderPresent(renderer);
	}
	return false;
}

bool ATM::loginAccount(vector<Account>& list_account, Account*& currentAccount, SDL_Event event, vector<NumberButton>& obn, 
	Inputer& userInput, Inputer& passwordInput, int& menuCurrent, SDL_Renderer* renderer, Mix_Chunk*& soundbeep)
{
	bool exist_account = false;
	if (userInput.done() == false) {
		menuCurrent = 2;
		userInput.readNumberInput(event, obn, soundbeep);
		userInput.showInput(renderer, 240, 265);
	}
	else {
		for (int i = 0; i < list_account.size(); i++) {
			if (list_account.at(i).checkAccount(userInput.getInput())) {
				exist_account = true;
				if (list_account.at(i).checkActive() == false) {
					renderError(renderer, "lockedaccount.png");
					return false;
					break;
				}
				if (passwordInput.done() == false) {
					menuCurrent = 3;
					passwordInput.readNumberInput(event, obn, soundbeep);
					passwordInput.showInput(renderer, 267, 266);
				}
				else {
					if (list_account.at(i).checkPass(passwordInput.getInput())) {
						currentAccount = &list_account.at(i);
						remove("Account.txt");
						for (auto x : list_account) {
							x.writeToSource(x.getDateCreat());
						}
						return true;
					}
					else {
						renderError(renderer, "pwerror.png");
						remove("Account.txt");
						for (auto x : list_account) {
							x.writeToSource(x.getDateCreat());
						}
						passwordInput.setDone(false);
					}
				}
				break;
			}
		}
		if (!exist_account) {
			renderError(renderer, "notexist.png");
			userInput.setDone(false);
		}
	}
	return false;
}


bool ATM::depositMoney(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<MenuButton> obb,
	Account*& currentAccount, vector<Account>& list_account, int bank[], Mix_Chunk*& soundbeep)
{
	SDL_Texture* texturedepo = loadTexture(renderer, "depo.png");

	choose = -1;
	vector<Inputer> inputNumber(4);
	int rectY[4] = { 250, 288, 324, 361 };
	Text resultsDepos(fontText);
	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturedepo, NULL, NULL);

		selectMenu(renderer, event, obb, choose, soundbeep);

		if (choose >= 1) {
			inputNumber.at(choose - 1).readNumberInput(event, obn, soundbeep);
			if (inputNumber.at(choose - 1).done()) {
				texturedepo = NULL;
				goto RESULTSDEPOSIT;
			}
		}

		for (int ipt = 0; ipt < inputNumber.size(); ipt++) {
			inputNumber.at(ipt).showInput(renderer, 196, rectY[ipt]);
		}
		SDL_RenderPresent(renderer);
	}

RESULTSDEPOSIT:
	int sumDepoMoney = inputNumber.at(0).getNumberInput() * 50 + inputNumber.at(1).getNumberInput() * 100 + inputNumber.at(2).getNumberInput() * 200 + inputNumber.at(3).getNumberInput() * 500;
	bank[50] += inputNumber.at(0).getNumberInput();
	bank[100] += inputNumber.at(1).getNumberInput();
	bank[200] += inputNumber.at(2).getNumberInput();
	bank[500] += inputNumber.at(3).getNumberInput();

	if (currentAccount->deposit(sumDepoMoney)) {
		texturedepo = loadTexture(renderer, "deposuc.png");
	}
	else texturedepo = loadTexture(renderer, "error.png");

	saveDaTa(list_account, bank);
	resultsDepos.setText("+" + to_string(sumDepoMoney));
	resultsDepos.setRect(228, 290);
	resultsDepos.setSize(to_string(sumDepoMoney).length() * 34, 50);

	Inputer inputer;
	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{

		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturedepo, NULL, NULL);

		resultsDepos.showText(fontText, renderer);

		SDL_RenderPresent(renderer);

		if (inputer.readNumberInput(event, obn, soundbeep) == false) return true;
	}
	return false;
}

bool ATM::sendMoney(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<MenuButton> obb,
	Account*& currentAccount, vector<Account>& list_account, int bank[], Mix_Chunk*& soundbeep)
{
	int sm;
	string usn;
	bool suc = false;

	SDL_Texture* texturedepo = loadTexture(renderer, "sendmoney1.png");

	Inputer inputNumber, inputUser;
	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturedepo, NULL, NULL);
		
		inputNumber.readNumberInput(event, obn, soundbeep);
		inputNumber.showInput(renderer, 240, 256);
		if (inputNumber.done()) {
			sm = inputNumber.getNumberInput();
			break;
		}
		SDL_RenderPresent(renderer);
	}

	texturedepo = loadTexture(renderer, "sendmoney2.png");
	
	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturedepo, NULL, NULL);

		inputUser.readNumberInput(event, obn, soundbeep);
		inputUser.showInput(renderer, 240, 256);

		if (inputUser.done()) {
			usn = inputUser.getInput();
			break;
		}

		SDL_RenderPresent(renderer);
	}

	for (int i = 0; i < list_account.size(); i++) {
		if (list_account.at(i).checkAccount(usn)) {
			suc = true;
			if (currentAccount->sendMoney(sm)) {
				if (list_account.at(i).recieveMoney(sm)) {
					texturedepo = loadTexture(renderer, "sendmoney3.png");
					break;
				}
				else texturedepo = loadTexture(renderer, "servererror.png");
			}
			else texturedepo = loadTexture(renderer, "notenough.png");
		}
	}
	if (!suc) texturedepo = loadTexture(renderer, "canfindusn.png");
	
	Inputer inputer;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturedepo, NULL, NULL);

		if (inputer.readNumberInput(event, obn, soundbeep) == false) return true;

		SDL_RenderPresent(renderer);
	}
	return false;
}

bool ATM::cashWithdrawals(SDL_Renderer* renderer, SDL_Event event, vector<MenuButton>& obb, vector<NumberButton> obn,
	int& choose, int bank[], Account*& currentAccount, vector<Account>& list_account, Mix_Chunk*& soundbeep)
{
CASHAGAIN:
	SDL_Texture* texturecashwd = loadTexture(renderer, "cashwd.png");
	choose = -1;
	Inputer inputMoney;

	int totals;
	int minmoney, maxmoney;
	totals = bank[50] * 50 + bank[100] * 100 + bank[200] * 200 + bank[500] * 500;
	minmoney = (bank[50] > 0) ? (50) : ((bank[100] > 0) ? (100) : ((bank[200] > 0) ? (200) : ((bank[500] > 0) ? (500) : (0))));
	maxmoney = (totals > currentAccount->getAccountBalance()) ? (currentAccount->getAccountBalance()) : (totals);
	
	Text maxMoney(fontText), minMoney(fontText);
	maxMoney.setText(to_string(maxmoney));
	maxMoney.setRect(305, 160);
	maxMoney.setSize(17 * 5, 28);
	minMoney.setText(to_string(minmoney));
	minMoney.setSize(17 * 3, 28);
	minMoney.setRect(308, 218);

	while (true) {
		while (SDL_PollEvent(&event) != 0)
		{
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturecashwd, NULL, NULL);

		maxMoney.showText(fontText, renderer);
		minMoney.showText(fontText, renderer);

		inputMoney.readNumberInput(event, obn, soundbeep);
		inputMoney.showInput(renderer, 330, 308);
		if (inputMoney.done()) {
			break;
		}

		SDL_RenderPresent(renderer);
	}

	int money = inputMoney.getNumberInput();

	if (money > maxmoney) {
		renderError(renderer, "toobig.png");
		goto CASHAGAIN;
	}
	else if (money < minmoney) {
		renderError(renderer, "toosmall.png");
		goto CASHAGAIN;
	}
	else if(cashW(bank, money)){
		currentAccount->sendMoney(money);
		saveDaTa(list_account, bank);
	}
	else if (cashW(bank, money) == false) {
		renderError(renderer, "error.png");
		goto CASHAGAIN;
	}
	texturecashwd = loadTexture(renderer, "success.png");

	SDL_Texture* receipt = loadTexture(renderer, "receipt.png");
	SDL_Rect r1;
	r1.h = 0;
	r1.w = 1080;
	r1.x = 0;
	r1.y = 1920;
	SDL_Rect r2;
	r2.h = 0;
	r2.w = 108;
	r2.x = 600;
	r2.y = 102;

	SDL_Texture* cashout = loadTexture(renderer, "casho.png");
	SDL_Rect r3;
	r3.h = 0;
	r3.w = 1920;
	r3.x = 0;
	r3.y = 1080;
	SDL_Rect r4;
	r4.h = 0;
	r4.w = 200;
	r4.x = 190;
	r4.y = 536;

	Inputer inputer;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texturecashwd, NULL, NULL);

		SDL_RenderCopy(renderer, receipt, &r1, &r2);

		SDL_RenderCopy(renderer, cashout, &r3, &r4);

		if (r1.h < 900) {
			r1.h += 10;
			r1.y -= 10;
			r2.h = r1.h / 10;
		}

		if (r3.h < 339) {
			r3.h += 5;
			r3.y -= 5;
			r4.h = r3.h / 5;
		}

		if (inputer.readNumberInput(event, obn, soundbeep) == false) return true;

		SDL_RenderPresent(renderer);
	}
	return false;
}

void ATM::saveDaTa(vector<Account> list_account, int bank[])
{
	remove("Account.txt");
	for (auto x : list_account) {
		x.writeToSource(x.getDateCreat());
	}
	remove("Bank.txt");
	fstream file;
	file.open("Bank.txt", ios::out);
	if (file.is_open()) {
		file << "50 " << bank[50] << endl;
		file << "100 " << bank[100] << endl;
		file << "200 " << bank[200] << endl;
		file << "500 " << bank[500] << endl;
		file.close();
	}
	
}
