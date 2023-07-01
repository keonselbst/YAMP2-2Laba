#include "TrieTree.h"
#include <fstream>
#include <Windows.h>

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream inputFile("words.txt"), menuFile("menu.txt");

	Trie tree;
	bool end = false;
	string MENU;
	while (!menuFile.eof()) {
		string temp;
		getline(menuFile, temp);
		temp += '\n';
		MENU += temp;
	}
	cout << MENU;
	while (!end) {
		cout << "�������� ��������: ";
		int operation;
		cin >> operation;
		string str;

		switch (operation) {
		case 1: {
			if (inputFile.is_open()) {
				string word;
				while (!inputFile.eof())
				{
					inputFile >> word;
					tree.insert(word);
				}
			}
			break;
		}
		case 2: {
			tree.delete_chet();
			break; }
		case 3: {
			cout << "\n������� �����, ������� ������ �����: ";
			cin >> str;
			if (tree.find(str)) { cout << "\n������� ��� ������\n"; }
			else cout << "\n������� �� ��� ������\n";
			break;
		}
		case 4: {
			cout << "------------------------------------\n";
			tree.print();
			cout << "------------------------------------\n";
			break;
		}
		case 5: {
			cout << "\n������� �����, ������� ������ ������� �� ������:\n->";
			string str;
			cin >> str;
			tree.remove(str);
			break;
		}
		case 6: {
			tree.clear();
			break;
		}
		case 7: {
			system("cls");

			cout << MENU;
			break;
		}
		case 8: {
			end = true;
			break;
		}
		default: cout << "\n��������� ����\n";
		}
	}

	inputFile.close();
}

