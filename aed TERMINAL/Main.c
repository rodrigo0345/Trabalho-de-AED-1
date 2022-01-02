#include "master.h"

enum bool
{
	false = 0 , true
};

int main()
{

	if (GetData() == false) {
		printf("Database is missing!");
		return -1;
	}

	Open.MainMenu = true;
	Open.SubMenu = false;

	while (Open.MainMenu)
	{
		DisplayMainMenu();
		while (Open.SubMenu) 
		{
			DisplaySubMenu();
		}
	}

	return 0;
}

