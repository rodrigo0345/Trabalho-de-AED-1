#include "master.h"

int ValidUserSelection(unsigned short Input, unsigned short Max)
{
	if (1 > Input || Max < Input)
	{
		return error;
	}
	return accepted;
}

void freeBuffer()
{
	while (getchar() != '\n');
}

void UpdateData()
{
	if (SaveData()) 
	{
		printf("Database is missing!");
	}
	if (GetData()) 
	{
		printf("Database is missing!");
	}
}

void Exit()
{
	Open.MainMenu = 0;
	Open.SubMenu = 0;
}

void GoBack()
{
	Open.MainMenu = 1;
	Open.SubMenu = 0;
}

void GetInfo(char variable[], int buffer, int* store) 
{
	fgets(variable, buffer, stdin);
	(*store) = atoi(variable);
	freeBuffer();
}

unsigned int GenerateID(char event[50], int vip)
{
	FILE* listID = fopen("IDs.txt", "r+");

	if (!listID)
	{
		printf("\nIDs.txt is missing\n");
		system("pause");
		return error;
	}

	CurrentTime();

	unsigned lastID = 0;
	char eventName[50];
	unsigned lastVip = 0;
	unsigned date = 0;

	while (!feof(listID))
	{
		fscanf(listID, "%u %s %u %d %d %d", &lastID, eventName, &lastVip, &date, &date, &date);
	}

	//save new ID
	fprintf(listID, "\n%u %s %u %d %d %d", ++lastID, event, vip, todayDate.Day, todayDate.Month, todayDate.Year);

	fclose(listID);

	return lastID;
}