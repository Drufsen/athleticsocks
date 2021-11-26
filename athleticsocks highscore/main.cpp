#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

string names[10];
int points[10];
int count = 0;

void list();
void add();
void fileRead();
void fileSave();

int main() {
	SetConsoleOutputCP(1252);
	fileRead();
	while (true) {
		list();
		fileSave();
		cout << endl;
		system("pause");
		add();
		}
	}

void fileRead() {
	//names from memory
	string line;
	ifstream file_names;
	ifstream file_points;
	file_names.open("names.txt");
	file_points.open("points.txt");

	//names
	int nr = 0;
	while (getline(file_names, line)) {
		names[nr] = line;
		nr++;
	}
	file_names.close();

	//points
	nr = 0;
	while (getline(file_points, line)) {
		points[nr] = stoi(line);
		nr++;
	}
	file_points.close();
}

void fileSave() {
	//names
	ofstream file_names;
	ofstream file_points;
	file_names.open("names.txt", ios::out);
	file_points.open("points.txt", ios::out);
	for (int i = 0; i < 10; i++) {
		file_names << names[i] + "\n";
		file_points << to_string(points[i]) + "\n";
	}
	file_names.close();
	file_points.close();
}

void list() {
	system("cls");
	cout << " TOP 10 BÄSTA\n";
	cout << "--------------------\n";
	for (int i = 0; i < 10; i++) {
		cout << i + 1;
		if (i < 9)
			cout << " ";
		//if (points[i] > 0)
		cout << " " + names[i] + " med " + to_string(points[i]) + " poäng";
		cout << endl;
	}
}

void add() {
	system("cls");

	int point;
	string name;

	while (true) {
		cout << "--------------------\n";
		cout << "Ange ditt namn: ";
		getline(cin, name);
		cout << "Ange din poäng: ";
		cin >> point;

		if (!std::cin.fail()) {
			//to dump
			ofstream file_dump;
			file_dump.open("dump.csv", ios::app);
			file_dump << name + ";" + to_string(point) + "\n";
			file_dump.close();

			cout << to_string(point) + " poäng har registrerats till " + name + "\n";
			system("pause");
			for (int z = 0; z < 10; z++) {
				if (point > points[z]) {
					for (int i = 8; i >= z; i--) {
						points[i + 1] = points[i];
						names[i + 1] = names[i];
					}
					points[z] = point;
					names[z] = name;
					z = 10;
				}
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			break;
		}
		else {
			cout << "Det var inte dina poäng! :P\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("pause");
		}
	}
}