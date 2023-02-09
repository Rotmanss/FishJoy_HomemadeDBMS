#include <iostream>
#include "Table.h"
#include "FishTable.h"
#include "FishCategoryTable.h"

#include "Menu.h"

// to do abbility to exit from choice like addRecord, removeRecored etc.

int main()
{
	Menu* menu = new Menu();
	menu->DoAction();

	return 0;
}