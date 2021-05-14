#include "CashWithdrawals.h"

void CASHW::solve(int a[], int tg, bool& check) {
	if (!check) {
		for (int i = 3; i >= 0; i--)
			if (!check && tg >= a[i] && a[i] > 0) {
				int value = 0;
				if (i == 0) value = 50;
				else if (i == 1) value = 100;
				else if (i == 2) value = 200;
				else if (i == 3) value = 500;
				tg -= value;
				a[i] -= 1;
				if (tg == 0) {
					check = true;
					return;
				}
				else if (tg > 0) {
					solve(a, tg, check);
				}
				if (!check) {
					a[i] += 1;
					tg += value;
				}
			}
	}
}

bool CASHW::cashW(int bank[], int money) {
	if (money % 50 == 0) {
		int cashout[4];
		cashout[0] = bank[50];
		cashout[1] = bank[100];
		cashout[2] = bank[200];
		cashout[3] = bank[500];
		bool check = false;
		solve(cashout, money, check);
		if (check) {
			cout << "\n------------------------------------------\n\n"<< TA::getTimeNow() << "\n\nSuccessfully!\nYou recieve:\n\n";
			cout << "Value          Amount\n";
			cout << "50.000         " << bank[50] - cashout[0] << endl;
			cout << "100.000        " << bank[100] - cashout[1] << endl;
			cout << "200.000        " << bank[200] - cashout[2] << endl;
			cout << "500.000        " << bank[500] - cashout[3] << endl;
			cout << "\n------------------------------------------\n";
			bank[50] = cashout[0];
			bank[100] = cashout[1];
			bank[200] = cashout[2];
			bank[500] = cashout[3];
			return true;
		}
		else {
			cout << "Error:(Bank)";
			return false;
		}
	}
	else {
		cout << "Error:(Money)";
		return false;
	}
}