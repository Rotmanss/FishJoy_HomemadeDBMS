#include <iostream>
#include "Menu.h"


int main()
{
	Menu* menu = new Menu();
	menu->DoAction();

	delete menu;
	return 0;
}
