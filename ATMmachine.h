#ifndef ATMmachine_H_
#define ATMmachine_H_

#include"ta.h"
#include"Account.h"
#include"CashWithdrawals.h"
#include"Text.h"
#include"NumberButton.h"
#include"Inputer.h"
#include "MenuButton.h"

static vector<Account> list_account;

static int choose = -1;
static Account* currentAccount = NULL;
static int bank[501];

static Inputer userInput;
static Inputer passwordInput;

using namespace TA;
using namespace CASHW;

namespace ATM {
	void initDaTa(vector<Account>& list_account, int bank[], vector<NumberButton>& obn, vector<MenuButton>& obb);
	void selectMenu(SDL_Renderer* renderer, SDL_Event event, vector<MenuButton>& obb, int& choose, Mix_Chunk*& soundbeep);
	void creatAccount(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<Account>& list_account, Mix_Chunk*& soundbeep);
	bool loginAccount(vector<Account>& list_account, Account*& currentAccount, SDL_Event event, vector<NumberButton>& obn,
		Inputer& userInput, Inputer& passwordInput, int & menuCurrent, SDL_Renderer* renderer, Mix_Chunk*& soundbeep);
	
	bool depositMoney(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<MenuButton> obb,
		Account*& currentAccount, vector<Account>& list_account, int bank[], Mix_Chunk*& soundbeep);

	bool sendMoney(SDL_Renderer* renderer, SDL_Event event, vector<NumberButton> obn, vector<MenuButton> obb,
		Account*& currentAccount, vector<Account>& list_account, int bank[], Mix_Chunk*& soundbeep);
	bool cashWithdrawals(SDL_Renderer* renderer, SDL_Event event, vector<MenuButton>& obb, vector<NumberButton> obn,
		int& choose, int bank[], Account*& currentAccount, vector<Account>& list_account, Mix_Chunk*& soundbeep);
	void saveDaTa(vector<Account> list_account, int bank[]);
	
}


#endif // !ATMmachine_H_

