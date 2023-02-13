#pragma once
#include "FishCategoriesTable.h"
#include "FishTable.h"
#include "GarbageCollector.h"


class Menu 
{
public:
	Menu();
	~Menu();

	void ShowMenu(int& choice);
	void DoAction();

private:
	Table* m_CategoryTable;
	Table* m_FishTable;
	GarbageCollector* m_Garbage;

private:
	bool is_running;
	int choice;
};
