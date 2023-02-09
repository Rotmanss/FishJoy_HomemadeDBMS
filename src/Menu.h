#pragma once
#include "FishCategoryTable.h"
#include "FishTable.h"


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
};
