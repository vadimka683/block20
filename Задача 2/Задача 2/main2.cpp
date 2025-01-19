#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<ctime>
using namespace std;

int main() {
	srand(time(nullptr));
	ofstream paint("C:\\Users\\vivas\\Downloads\\Telegram Desktop\\block20\\magazin.txt", ios::binary);
	cout << "Input weght and height paint: ";
	int weght, height;
	cin >> weght >> height;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < weght; j++) {
			int pixel = rand()%2;
			paint << pixel;
		}
		paint << "\n";
	}
}