#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

bool bank_check_for_emptiness() {
	ifstream bank("bank.bin", ios::binary);
	if (bank.is_open()) {
		return true;
	}
	else {
		cout << "Bank is empty\n";
		bank.close();
		ofstream bank_first("bank.bin", ios::binary);
		if (!bank_first.is_open()) {
			cout << "Error file\n";
		}
		for (int i = 0; i < 1000; i++) {
			int j = 0;
			bank_first.write(reinterpret_cast<char*>(&j), sizeof(j));
		}
		bank_first.close();
		return false;
	}
}

void current_state_bank(int& c_100,int& c_200,int& c_500, int& c_1000, int& c_2000, int& c_5000, long int& all_money) {
	cout << "State bank now\n";
	ifstream bank("bank.bin", ios::binary);
	if (!bank.is_open()) {
		cout << "Error file\n";
	}
	all_money = 0; c_100 = 0; c_200 = 0; c_500 = 0; c_1000 = 0; c_2000 = 0; c_5000 = 0;
	int curret_money = 0;
	while (bank.read(reinterpret_cast<char*>(&curret_money), sizeof(curret_money))) {
		all_money += curret_money;
		if (curret_money == 100) { c_100 += 1; }
		else if (curret_money == 200) { c_200 += 1; }
		else if (curret_money == 500) { c_500 += 1; }
		else if (curret_money == 1000) { c_1000 += 1; }
		else if (curret_money == 2000) { c_2000 += 1; }
		else if (curret_money == 5000) { c_5000 += 1; }
	}
	cout << "All money: " << all_money << "\n";
	cout << "Count 100: " << c_100 << "\n";
	cout << "Count 200: " << c_200 << "\n";
	cout << "Count 500: " << c_500 << "\n";
	cout << "Count 1000: " << c_1000 << "\n";
	cout << "Count 2000: " << c_2000 << "\n";
	cout << "Count 5000: " << c_5000 << "\n";
	bank.close();
}

void filling_money() {
	ifstream bank("bank.bin", ios::binary);
	ofstream  bank_1("bank_1.bin", ios::binary | ios::app);
	if (!bank.is_open() || !bank_1.is_open()) {
		cout << "Error file\n";
	}
	int cur_money;
	while (bank.read(reinterpret_cast<char*>(&cur_money),sizeof(cur_money))) {
		if (cur_money == 0) {
			int base[6] = { 100,200,500,1000,2000,5000 };
			cur_money = base[rand() % 6];
			bank_1.write(reinterpret_cast<char*>(&cur_money), sizeof(cur_money));
		}
		else {
			bank_1.write(reinterpret_cast<char*>(&cur_money), sizeof(cur_money));
		}
	}
	bank.close();
	bank_1.close();
	if (remove("bank.bin") != 0) {
		cout << "Error remove file";
	}
	if (rename("bank_1.bin", "bank.bin") != 0) {
		cout << "Error rename file\n";
	};
	return;
}

bool cashing_out(int& c_100, int& c_200, int& c_500, int& c_1000, int& c_2000, int& c_5000,long int& all_money, int& user_money) {
	if (user_money > all_money || user_money < 0) {
		cout << "Operation is not valide";
		return false;
	}
	{	
	if (user_money / 5000 >= 1) {
		if (user_money / 5000 > c_5000) {
			return false;
		}
		else {
			c_5000 = user_money / 5000;
			user_money %= 5000;
		}
	}
	if (user_money / 2000 >= 1) {
		if (user_money / 2000 > c_2000) {
			return false;
		}
		else {
			c_2000 = user_money / 2000;
			user_money %= 2000;
		}
	}
	if (user_money / 1000 >= 1) {
		if (user_money / 1000 > c_1000) {
			return false;
		}
		else {
			c_1000 = user_money / 1000;
			user_money %= 1000;
		}
	}
	if (user_money / 500 >= 1) {
		if (user_money / 500 > c_500) {
			return false;
		}
		else {
			c_500 = user_money / 500;
			user_money %= 500;
		}
	}
	if (user_money / 200 >= 1) {
		if (user_money / 200 > c_200) {
			return false;
		}
		else {
			c_200 = user_money / 200;
			user_money %= 200;
		}
	}
	if (user_money / 100 >= 1) {
		if (user_money / 100 > c_100) {
			return false;
		}
		else {
			c_100 = user_money / 100;
			user_money %= 100;
		}
	}
    }
	ifstream bank("bank.bin", ios::binary);
	ofstream bank_1("bank_1.bin", ios::binary | ios::app);
	if (!bank.is_open() || !bank_1.is_open()) {
		cout << "Error file open\n";
	}
	int bank_cash;
	while (bank.read(reinterpret_cast<char*>(&bank_cash), sizeof(bank_cash))) {
		int zero = 0;

		{
			if (bank_cash == 5000 && c_5000 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_5000--;
			}
			else if (bank_cash == 2000 && c_2000 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_2000--;
			}
			else if (bank_cash == 1000 && c_1000 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_1000--;
			}
			else if (bank_cash == 500 && c_500 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_500--;
			}
			else if (bank_cash == 200 && c_200 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_200--;
			}
			else if (bank_cash == 100 && c_100 != 0) {
				bank_1.write(reinterpret_cast<char*>(&zero), sizeof(zero));
				c_100--;
			}
			else {
				bank_1.write(reinterpret_cast<char*>(&bank_cash), sizeof(bank_cash));
			}
		}
	}
	bank.close();
	bank_1.close();
	if (remove("bank.bin") != 0 || rename("bank_1.bin", "bank.bin") != 0) {
		cout << "Error file remove or rename";
	}
	return true;
}


int main() {
	int count_100 = 0, count_200 = 0, count_500 = 0, count_1000 = 0, count_2000 = 0, count_5000 = 0;
	long int all_money = 0;
	int comand;
	cout << "\tWelcome to BANK!!!\n";
	if (bank_check_for_emptiness()) {
		current_state_bank(count_100, count_200, count_500, count_1000, count_2000, count_5000, all_money);
	}
	do {
		cout << "Input commands:\n1.Fill the ATM\n2.Withdraw money\n3.Exit\n";
		cin >> comand;
		if (comand == 1) {
			filling_money();
			current_state_bank(count_100, count_200, count_500, count_1000, count_2000, count_5000, all_money);
		}
		else if (comand == 2) {
			int user_number;
			cout << "how much money do you want to withdraw";
			cin >> user_number;
			cashing_out(count_100, count_200, count_500, count_1000, count_2000, count_5000, all_money, user_number);
			current_state_bank(count_100, count_200, count_500, count_1000, count_2000, count_5000, all_money);
		}
	} while (comand != 3);
}