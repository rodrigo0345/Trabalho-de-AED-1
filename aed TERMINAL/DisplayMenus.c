#include "master.h"
#include "SubMenus.h"

unsigned short auxUserSelection;

void DisplayMainMenu()
{
	char userSelection[5];
	
	system("cls");
	printf("______________________| Events |______________________\n");
	printf("[1] Create.\n");
	printf("[2] Search.\n");
	printf("[3] Update Event Information.\n");
	printf("[4] Delete.\n");
	printf("[5] Search by date.\n");
	printf("[6] Search inactive events.\n");
	printf("[7] Check date availability.\n");
	printf("\n______________________| Tickets |______________________\n");
	printf("[8] Buy.\n");
	printf("[9] Tickets sold.\n");
	printf("[10] Record of sales.\n");
	printf("[11] Day of record of affluence.\n"); 
	printf("[12] Event`s income.\n");
	printf("[13] Period income.\n");
	printf("[14] Trade Ticket.\n");
	printf("[15] Return Ticket.\n");
	printf("[16] Verify Ticket.\n");
	printf("\n__________________| Update Database |__________________\n");
	printf("[17] Update.\n");
	printf("[18] Exit.\n");
	printf("\n- Select an option: ");
	fgets(userSelection, 4, stdin);

	freeBuffer();

	auxUserSelection = atoi(userSelection);

	if (ValidUserSelection(auxUserSelection, 19))
	{
		Open.SubMenu = 1;
	}
}

void DisplaySubMenu()
{
	switch (auxUserSelection)
	{
		//events
		case 1: 
			Create();
			break;
		case 2: 
			Search();
			break;
		case 3: 
			UpdateEventInfo();
			break;
		case 4: 
			Delete();
			break;
		case 5: 
			SearchByDate();
			break;
		case 6: 
			SearchInactiveEvents();
			break;
		case 7: 
			CheckDayAvailability();
			break;
		//tickets
		case 8:
			BuyTicket();
			break;
		case 9: 
			TicketsSold();
			break;
		case 10: 
			RecordOfSales();
			break;
		case 11: 
			DayOfRecordAffluence();
			break;
		case 12: 
			EventIncome();
			break;
		case 13: 
			PeriodIncome();
			break;
		case 14:
			TradeTicket();
			break;
		case 15:
			ReturnTicket();
			break;
		case 16:
			VerifyTicket();
			break;
		case 17: 
			Update();
			break;
		//Exit
		default:
			Exit();
	}
	Open.SubMenu = 0;
}

