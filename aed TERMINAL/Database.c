#include <conio.h>
#include "master.h"

void resetStruct()
{
	memset(Event, 0, sizeof(Event));
}
int GetData()
{
	FILE* openEvent = fopen("EventsDataBase.txt", "r");

	if (openEvent == NULL)
	{
		return error;
	}

	//pass the first "ghost" line in the .txt || program does not work if the database is tottaly empty
	char ch = fgetc(openEvent);
	while (ch != '\n')
	{
		ch = fgetc(openEvent);
	}

	resetStruct();

	unsigned int count = 0;
	while (!feof(openEvent))
	{
		//
		//getting events data
		//
		fscanf(openEvent, "%d %s %d %d %d %d %d %d %d %d %d",
			&(Event[count].auxID), Event[count].auxName, &(Event[count].auxDay),
			&(Event[count].auxMonth), &(Event[count].auxYear),
			&(Event[count].auxDuration), &(Event[count].auxPrice),
			&(Event[count].auxVipPrice), &(Event[count].auxMaxPeople),
			&(Event[count].auxTicketsSold), &(Event[count].MoneyMade));

		count++;
	}

	//close the .txt
	fclose(openEvent);
	return accepted;
}

int SaveData()
{
	FILE* saveEvent = fopen("EventsDataBase.txt", "a");

	if (saveEvent == NULL)
	{
		return error;
	}

	if (Current.ID == 0) // the struct often stores data with Current.ID = 0 meaning there is no event in that pole
	{
		fclose(saveEvent);
		return error;
	}
	else
	{
		Current.ID = 0;
	}

	int i;
	for (int i = 0; i < MAX; i++)
	{
		if (Event[i].auxID < Event[i + 1].auxID)
		{
			Current.ID = Event[i + 1].auxID;
		}
	}

	fprintf(saveEvent, "\n%d %s %d %d %d %d %d %d %d %d %d", ++Current.ID, Current.Name, Current.Day,
		Current.Month, Current.Year,
		Current.Duration, Current.Price,
		Current.VipPrice, Current.MaxPeople,
		Current.TicketsSold, Current.MoneyMade);

	GetData();

	//close the .txt
	fclose(saveEvent);

	return accepted;
}

void UpdateEventDatabase()
{
	FILE* rewrite = fopen("temp.txt", "w+");
	FILE* Original = fopen("EventsDataBase.txt", "r");

	char userInput[50];
	int id = 0, aux1 = 0;
	while (!feof(Original))
	{
		fscanf(Original, "%d %s %d %d %d %d %d %d %d %d %d",
			&id, userInput, &aux1,
			&aux1, &aux1,
			&aux1, &aux1,
			&aux1, &aux1,
			&aux1, &aux1);

		if (id == 0)
		{
			break;
		}

		fprintf(rewrite, "\n%d %s %d %d %d %d %d %d %d %d %d", (Event[id - 1].auxID),
			(Event[id - 1].auxName), (Event[id - 1].auxDay),
			(Event[id - 1].auxMonth), (Event[id - 1].auxYear),
			(Event[id - 1].auxDuration), (Event[id - 1].auxPrice),
			(Event[id - 1].auxVipPrice), (Event[id - 1].auxMaxPeople),
			(Event[id - 1].auxTicketsSold), (Event[id - 1].MoneyMade));
	}
	fclose(Original);
	fclose(rewrite);

	remove("EventsDataBase.txt");
	rename("temp.txt", "EventsDataBase.txt");
}