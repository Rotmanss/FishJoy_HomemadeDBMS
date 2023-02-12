#include "Menu.h"
#include <iostream>

Menu::Menu()
	: choice(0), is_running(true)
{
	m_CategoryTable = new FishCategoriesTable();
	m_FishTable = new FishTable((FishCategoriesTable*)m_CategoryTable);
}

Menu::~Menu()
{
	delete m_CategoryTable;
	delete m_FishTable;
}

void Menu::ShowMenu(int& choice)
{
	std::cout << "Select an option:\n\n1) See 'Fish list'\n2) See 'Category list'\n3) Add record to 'Fish table'\n" <<
		"4) Add record to 'Category table'\n5) Remove record from 'Fish table'\n6) Remove record from 'Category table'\n" <<
		"7) Update record in 'Fish table'\n8) Update record in 'Category table'\n9) Get the number of records of 'Fish table'\n" <<
		"10) Get the number of records of 'Category table'\n11) Exit\n";
	std::cin >> choice;
	std::cout << "\n";
}

void Menu::DoAction()
{
	while (is_running)
	{
		if (choice == 0)
			ShowMenu(choice);

		switch (choice)
		{
		case 1:
			m_FishTable->PrintList();
			choice = 0;
			break;
		case 2:
			m_CategoryTable->PrintList();
			choice = 0;
			break;
		case 3:
			m_FishTable->AddRecord();
			choice = 0;
			break;
		case 4:
			m_CategoryTable->AddRecord();
			choice = 0;
			break;
		case 5:
			m_FishTable->RemoveRecord();
			choice = 0;
			break;
		case 6:
			m_CategoryTable->RemoveRecord();
			choice = 0;
			break;
		case 7:
			m_FishTable->UpdateRecord();
			choice = 0;
			break;
		case 8:
			m_CategoryTable->UpdateRecord();
			choice = 0;
			break;
		case 9:
			m_FishTable->PrintRecordsNumber();
			choice = 0;
			break;
		case 10:
			m_CategoryTable->PrintRecordsNumber();
			choice = 0;
			break;
		case 11:
			is_running = false;
			break;
		default:
			std::cout << "You selected wrong option!\n";
			choice = 0;
			break;
		}
	}
}
