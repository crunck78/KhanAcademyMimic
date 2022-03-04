#include <stdlib.h>
#include <iostream>
#include "Menu.h"

int main()
{
	initMenuTree();
	Menu *actual = &K_main;
	while (actual != &K_exit)
	{
		actual->displayOptions();
		actual = actual->selectOption();
		//system("cls"); moved in class menu, selectOption methode
	}
}