#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main() {
	ofstream magazin("C:\\Users\\vivas\\Downloads\\Telegram Desktop\\block20\\magazin.txt", ios::app);
	magazin.setf(ios::skipws);
	if (!magazin.is_open()) {
		cout << "Error file open";
		return 0;
	}
	cout << "Input name: ";
	string data;
	cin >> data;
	magazin << data << " ";
	cout << "Input surname: ";
	cin >> data;
	magazin << data << " ";
	int data_month, data_day, data_year;
	do {
		cout << "Input payment date: ";
		cin >> data;
		data_month = stoi(data.substr(3, 2));
		data_day = stoi(data.substr(0, 2));
		data_year = stoi(data.substr(6, 4));
		if (data_month > 12 || data_day > 31 || data_year < 2024) {
			cout << "Wrong data\n";
		}
	} while (data_month > 12 || data_day > 31 || data_year < 2024);
	magazin << data << " ";
	int pay;
	do {
		cout << "Input payment amount: ";
		cin >> data;
		pay = stoi(data);
		if (pay <= 0) {
			cout << "Wrong payment amount\n";
		}
	} while (pay <= 0);
	magazin << data << " RUB\n";
}