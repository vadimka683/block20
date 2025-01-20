#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void play(string& using_fish) {
	ifstream check_lake("C:\\Users\\vivas\\Downloads\\Telegram Desktop\\block20\\river.txt");
	if (!check_lake.is_open()) {
		cout << "Error file open";
		return;
	}
	string fish_in_lake;
	int count_fish = 0;
	while (getline(check_lake, fish_in_lake)) {
		if (fish_in_lake == using_fish) {
			ofstream basket("C:\\Users\\vivas\\Downloads\\Telegram Desktop\\block20\\basket.txt", ios::app);
			basket << fish_in_lake << "\n";
			count_fish++;
		}
	}
	cout << "Your catch " << count_fish << " of fish";
}

int main() {
	string answer;
	cout << "Input name of fish: ";
	cin >> answer;
	play(answer);
}