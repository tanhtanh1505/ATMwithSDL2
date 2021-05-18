#include"ATMmachine.h"

using namespace ATM;

int main(int argc, char* argv[]) {

	initSDL(window, renderer, soundbeep);
LOOP:
	const int numTexture = 8;
	string menuTexture[numTexture] = { "atmstart.png", "menuatm.png", "iduser.png",
		"pwuser.png", "notexist.png", "depo.png", "deposuc.png", "cashwd.png"};
	int menuCurrent = 0;
	vector<SDL_Texture*> listAtmTexture(numTexture);
	for (int lat = 0; lat < listAtmTexture.size(); lat++) {
		listAtmTexture.at(lat) = loadTexture(renderer, menuTexture[lat]);
	}

	vector<NumberButton> obn(13);

	vector<MenuButton> obb(5);


	initDaTa(list_account, bank, obn, obb);
START:

	Inputer userInput;
	Inputer passwordInput;
	choose = -1;
	menuCurrent = 0;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			
		}
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, listAtmTexture.at(menuCurrent), NULL, NULL);
		
		selectMenu(renderer, event, obb, choose, soundbeep);
		
		if (choose == 1) {
			if (loginAccount(list_account, currentAccount, event, obn, userInput, passwordInput, menuCurrent, renderer, soundbeep)) {
				goto MENUSELECT;
				//"\n1.Nap tien\n2.Rut tien\n3.Chuyen tien\n4.lich su\n5.so du\n";
			}
		}
		else if (choose == 2) {
			goto CREATACCOUNT;
		}
		SDL_RenderPresent(renderer);
	}

	//Menu Select-------------------------------------------------
	if (false) {
	MENUSELECT:
		Inputer checklog;
		saveDaTa(list_account, bank);
		menuCurrent = 1;
		choose = -1;
		while (!quit) {
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, listAtmTexture.at(menuCurrent), NULL, NULL);

			selectMenu(renderer, event, obb, choose, soundbeep);
			if (choose == 1) {
				goto DEPOSITMONEY;
			}
			if (choose == 2) {
				goto CASHWITHDRAWALS;
			}
			else if (choose == 3) {
				goto SENDMONEY;
			}
			else if (choose == 4) {
				currentAccount->showHistory();
				choose = 0;
			}
			else if (choose == 5) {
				currentAccount->print();
				choose = 0;
			}
			if (checklog.readNumberInput(event, obn, soundbeep) == false) {
				currentAccount = NULL;
				goto START;
			}
			SDL_RenderPresent(renderer);
		}

	}

	//CreatAccount----------------------------------------------
	if (false) {
	CREATACCOUNT:
		if (creatAccount(renderer, event, obn, list_account, soundbeep)) goto START;
	}

	//DepositMoney----------------------------------------------
	if (false) {
	DEPOSITMONEY:
		if (depositMoney(renderer, event, obn, obb, currentAccount, list_account, bank, soundbeep)) goto MENUSELECT;
	}

	//CASHWITHDRAWALS-------------------------------------------

	if (false) {
	CASHWITHDRAWALS:
		if (cashWithdrawals(renderer, event, obb, obn, choose, bank, currentAccount, list_account, soundbeep)) goto MENUSELECT;
	}

	//SENDMONEY--------------------------------------------------
	if (false) {
	SENDMONEY:
		if (sendMoney(renderer, event, obn, obb, currentAccount, list_account, bank, soundbeep)) goto MENUSELECT;

	}

	currentAccount = NULL;
	TA::quitSDL(window, renderer);
	
	return 0;
}