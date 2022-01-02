#include "master.h"


void ShowActiveEvents();
void DeleteTicketFromDatabase(int);

void BuyTicket()
{
    system("cls");
    
    ShowActiveEvents();

    long int eventSelected = 0;
    char userInput[50];
    printf("\nPlease choose the ID of the Event you want to buy: ");
    GetInfo(userInput, 6, &eventSelected);

    if (!ValidUserSelection(eventSelected, MAX) || Event[eventSelected - 1].auxID == 0)
    {
        printf("\nThat event does not exist\n");
        system("pause");
        return;
    }

    printf("\nDo you want to buy:\n[1] VIP seat for %d euros\n[2] Regular seat for %d euros\n", Event[eventSelected - 1].auxVipPrice, Event[eventSelected - 1].auxPrice);
    int selection = 0;
    GetInfo(userInput, 3, &selection);
    if (!ValidUserSelection(selection, 3)) return;

    int quantity = 0;
    printf("\nHow many tickets do you want? (%d available) ", Event[eventSelected - 1].auxMaxPeople - Event[eventSelected - 1].auxTicketsSold);
    GetInfo(userInput, 6, &quantity);
    if (!ValidUserSelection(selection, 34567)) return;

    if (quantity + Event[eventSelected - 1].auxTicketsSold > Event[eventSelected - 1].auxMaxPeople)
    {
        printf("You cant buy that many tickets!");
        system("pause");
        return;
    }
    system("cls");

    if (selection == 1)
    {
        printf("Congratulations!\nYou bought %d VIP tickets for %d euros", quantity, quantity * Event[eventSelected - 1].auxVipPrice);
        Event[eventSelected - 1].MoneyMade += quantity * Event[eventSelected - 1].auxVipPrice;
    }
    else if (selection == 2)
    {
        printf("Congratulations!\nYou bought %d tickets for %d euros", quantity, quantity * Event[eventSelected - 1].auxPrice);
        Event[eventSelected - 1].MoneyMade += quantity * Event[eventSelected - 1].auxPrice;
    }
    printf("\nTickets ID (Save these in order to validate your purchase):");

    Event[eventSelected - 1].auxTicketsSold += quantity;

    // vip corresponds to 0 and regular seat corresponds to 1
    int j;
    for (j = 0; j < quantity; j++)
    {
        printf("\n%u", GenerateID(Event[eventSelected - 1].auxName, selection - 1));
    }

    //Update the amount of tickets sold and money made
    UpdateEventDatabase();

    GetData();
    printf("\n");
    system("pause");
}

void TicketsSold()
{
    unsigned long ticketsSold = 0;

    int i;
    for (i = 0; i < MAX; i++)
    {
        ticketsSold += Event[i].auxTicketsSold;
    }

    printf("\nThere were sold %lu tickets to this moment!", ticketsSold);
    getchar();
    system("cls");
}

void RecordOfSales()
{
    system("cls");

    unsigned long MaxTickets = 0;
    unsigned long MaxProfit = 0;
    char* nameOfEventT = "";
    char* nameOfEventM = "";

    int i;
    for (i = 0; i < MAX; i++)
    {
        if (MaxTickets < Event[i].auxTicketsSold)
        {
            MaxTickets = Event[i].auxTicketsSold;
            nameOfEventT = Event[i].auxName;
        }
        if (MaxProfit < Event[i].MoneyMade)
        {
            MaxProfit = Event[i].MoneyMade;
            nameOfEventM = Event[i].auxName;
        }
    }

    printf("Event with record of tickets sold [%d]: %s", MaxTickets, nameOfEventT);
    printf("\nEvent with the most profit [%deuros]: %s", MaxProfit, nameOfEventM);
    getchar();
}

void DayOfRecordAffluence()
{
    FILE* ID = fopen("IDs.txt", "r");

    if (!ID)
    {
        printf("\nDatabase is missing!\n");
        getchar();
        return;
    }

    //Gets current reading Date and the Date before
    int auxDay = 0, auxMonth = 0, auxYear = 0;
    int cDay = 0, cMonth = 0, cYear = 0;

    //stores trash
    char aux[50];
    unsigned aux2 = 0;
    
    //saves the amount of times the program counted the same date, once it starts counting other date, we change the position in the array
    int count[MAX] = {0};
    //links every position of the array 'count' with a date
    char Date[MAX][10] = { 0, 0 }; 

    int i = 0;
    while (!feof(ID))
    {
        fscanf(ID, "%u %s %d %d %d %d", &aux2, aux, &aux2, &cDay, &cMonth, &cYear);

        if (cDay == 0 && cMonth == 0 && cYear == 0) continue;
        if (cDay == auxDay && cMonth == auxMonth && cYear == auxYear)
        {
            count[i]++;
            sprintf(aux, "%d/%d/%d", auxDay, auxMonth, auxYear);
            sprintf(Date[i], "%s", aux);
        }
        else
        {
            i++; // change the position in the array because the date now is different
            count[i]++;
            auxDay = cDay;
            auxMonth = cMonth;
            auxYear = cYear;
            sprintf(aux, "%d/%d/%d", auxDay, auxMonth, auxYear);
            sprintf(Date[i], "%s", aux);
        }
    }

    int max = 0;
    for (i = 0; i < MAX; i++)
    {
        if (count[i] > max)
        {
            max = count[i];
            //aux2 will enable us to track the position in which the array 'count' has the most affluence
            aux2 = i;
        }
    }

    //weird bug displayind Date[aux2]
    char Display[10] = {0};
    strcat(Display, Date[aux2]);

    printf("\nDay with record of afluence was %s\n",Display);
    fclose(ID);

    getchar();
}

void EventIncome()
{
    system("cls");

    DisplayEventList();

    char UserInput[7];
    int selection = 0;
    printf("\nSelect an Event to see it's income: ");
    GetInfo(UserInput, 4, &selection);

    if (Event[selection - 1].auxID == 0)
    {
        printf("\nThe Event you selected is invalid...");
        getchar();
        return;
    }

    system("cls");

    //display specified event
    printf("%d %s Date:%d/%d/%d Duration:%d Price:%d VIP Price:%d Max people:%d \n",
        (Event[selection - 1].auxID), (Event[selection - 1].auxName), (Event[selection - 1].auxDay),
        (Event[selection - 1].auxMonth), (Event[selection - 1].auxYear),
        (Event[selection - 1].auxDuration), (Event[selection - 1].auxPrice),
        (Event[selection - 1].auxVipPrice), (Event[selection - 1].auxMaxPeople));

    printf("\nThis Event generated %deuros of income.", Event[selection - 1].MoneyMade);
    getchar();
}

void PeriodIncome()
{
    system("cls");
    char UserInput[5];
    unsigned int s_Day = 0, s_Month = 0, s_Year = 0; // s_ its meant for start

    printf("Date of start:");
    printf("\nDay: ");
    GetInfo(UserInput, 3, &s_Day);
    printf("\nMonth: ");
    GetInfo(UserInput, 3, &s_Month);
    printf("\nYear: ");
    GetInfo(UserInput, 5, &s_Year);

    if (!ValidUserSelection(s_Day, MonthNumOfDays(s_Month, s_Year)) || s_Month > 12)
    {
        printf("\nDate is invalid");
        system("pause");
        return;
    }

    unsigned int e_Day = 0, e_Month = 0, e_Year = 0;
    printf("Date of end:");
    printf("\nDay: ");
    GetInfo(UserInput, 3, &e_Day);
    printf("\nMonth: ");
    GetInfo(UserInput, 3, &e_Month);
    printf("\nYear: ");
    GetInfo(UserInput, 5, &e_Year);

    if (!ValidUserSelection(e_Day, MonthNumOfDays(e_Month, e_Year)) || e_Month > 12)
    {
        printf("\nDate is invalid");
        system("pause");
        return;
    }

    system("cls");

    if (s_Year > e_Year ||
        (s_Month > e_Month && s_Year == e_Year) ||
        (s_Day > e_Day && s_Month == e_Month && s_Year == e_Year))
    {
        printf("\nEnd date is after the start date!");
        system("pause");
        return;
    }

    printf("Period | %u/%u/%u - %u/%u/%u", s_Day, s_Month, s_Year, e_Day, e_Month, e_Year);

    unsigned long income = 0;
    while (s_Year != e_Year || s_Month != e_Month || s_Day != e_Day)
    {
        int i;
        for (i = 0; i < MAX; i++)
        {
            if (Event[i].auxDay == s_Day && Event[i].auxMonth == s_Month && Event[i].auxYear == s_Year)
            {
                income += Event[i].MoneyMade;
            }
        }

        if (++s_Day > MonthNumOfDays(s_Month, s_Year))
        {
            s_Day = 1;
            s_Month++;

            if (s_Month > 12)
            {
                s_Month = 1;
                s_Year++;
            }
        }

    }
    printf("\nMoney made in this period was %lueuros\n", income);
    system("pause");
}

/*  
    If the previous ticket was VIP,
    the new one WILL BE VIP too and vice - versa 
*/
void TradeTicket()
{
    system("cls");

    char userInput[50];
    int ticketID = 0;
    printf("What is the ID of the ticket you want to trade? ");
    GetInfo(userInput, 8, &ticketID);

    //get info about the ID and check if the Ticket exists
    FILE* databaseID = fopen("IDs.txt", "r");

    if (!databaseID)
    {
        printf("\nDatabase is missing!\n");
        getchar();
        return;
    }

    unsigned auxID = 0;
    int aux = 0;
    char eventTicket[50];
    int VIP = 1;

    myBool found = 0;
    while (!feof(databaseID))
    {
        fscanf(databaseID, "%u %s %d %d %d %d", &auxID, eventTicket, &VIP, &aux, &aux, &aux);

        if (auxID == ticketID)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nThe ticket does not exist\n");
        system("pause");
        fclose(databaseID);
        return;
    }
    fclose(databaseID);

    //Check if the event is still active or not
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (!strcmp(Event[i].auxName, eventTicket))
        {
            if (!CheckUserInputDate(Event[i].auxDay, Event[i].auxMonth, Event[i].auxYear))
            {
                printf("\nThe event ID %d is not legible for trade\n", ticketID);
                system("pause");
                return;
            }
            break;
        }
    }

    //select event to trade for
    ShowActiveEvents();

    int selection = 0;
    printf("\nSelect the event ID you want to trade your ticket for: ");
    GetInfo(userInput, 7, &selection);

    if (Event[selection - 1].auxID == 0)
    {
        printf("\nThe event you chose does not exists\n");
        system("cls");
        return;
    }
    if (Event[selection - 1].auxMaxPeople == Event[selection - 1].auxTicketsSold)
    {
        printf("\nThe event you chose is already full\n");
        system("cls");
        return;
    }

    //delete the previous ticket
    DeleteTicketFromDatabase(ticketID);

    //display the new ticket ID and the price difference
    if (VIP == 0)
    {
        printf("New ticket acquired! ID:%u Price difference: %deuros\n", GenerateID(Event[selection - 1].auxName, VIP), Event[i].auxVipPrice - Event[selection - 1].auxVipPrice);

        //update the income of the event
        Event[selection - 1].MoneyMade += Event[selection - 1].auxVipPrice;
        Event[i].MoneyMade -= Event[i].auxVipPrice;
    }
    else if (VIP == 1)
    {
        printf("New ticket acquired! ID:%u Price difference: %deuros\n", GenerateID(Event[selection - 1].auxName, VIP), Event[i].auxPrice - Event[selection - 1].auxPrice);

        //update the income of the event
        Event[selection - 1].MoneyMade += Event[selection - 1].auxPrice;
        Event[i].MoneyMade -= Event[i].auxPrice;
    }

    //update EventsDataBase.txt
    Event[selection - 1].auxTicketsSold++;
    Event[i].auxTicketsSold--;

    UpdateEventDatabase();

    GetData();
    printf("\n");

    system("pause");
}

void ReturnTicket()
{
    system("cls");

    char userInput[50];
    int ticketID = 0;
    printf("Type the id of the ticket you want to return: ");
    GetInfo(userInput, 9, &ticketID);

    //get info about the ID and check if the Ticket exists
    FILE* databaseID = fopen("IDs.txt", "r");

    if (!databaseID)
    {
        printf("\nDatabase is missing!\n");
        getchar();
        fclose(databaseID);
        return;
    }

    unsigned auxID = 0;
    int aux = 0;
    char eventTicket[50];
    int VIP = 1;

    myBool found = 0;
    while (!feof(databaseID))
    {
        fscanf(databaseID, "%u %s %d %d %d %d", &auxID, eventTicket, &VIP, &aux, &aux, &aux);

        if (auxID == ticketID)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nThe ticket does not exist\n");
        system("pause");
        fclose(databaseID);
        return;
    }
    fclose(databaseID);

    //check if the ticket´s event is still active or not
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (!strcmp(Event[i].auxName, eventTicket))
        {
            if (!CheckUserInputDate(Event[i].auxDay, Event[i].auxMonth, Event[i].auxYear))
            {
                printf("\nThe event ID %d cannot be returned because the event is not active anymore\n", ticketID);
                system("pause");
                return;
            }
            break;
        }
    }

    //delete ticket from database
    FILE* file1 = fopen("IDs.txt", "r");
    FILE* file2 = fopen("tempIDs.txt", "w"); //creates temp file

    int auxID2 = 0;
    int Day = 0, Month = 0, Year = 0;
    char name[50] = "";

    myBool adjust = 0;
    while (!feof(file1))
    {
        fscanf(file1, "%u %s %d %d %d %d", &auxID2, name, &VIP, &Day, &Month, &Year);
        if (ticketID == auxID2)
        {
            adjust = 1;
        }
        else
        {
            fprintf(file2, "\n%u %s %d %d %d %d", auxID2, name, VIP, Day, Month, Year);    
        }
    }
    fclose(file1);
    fclose(file2);

    remove("IDs.txt");
    rename("tempIDs.txt", "IDs.txt");

    //get price of the old ticket´s event
    for (i = 0; i < MAX; i++)
    {
        if (!strcmp(Event[i].auxName, eventTicket))
        {
            break;
        }
    }
    
    if (VIP == 0)
    {
        printf("\nDone, returning %deuros to you\n", Event[i].auxVipPrice);
        Event[i].auxVipPrice -= Event[i].auxVipPrice;
        Event[i].auxTicketsSold -= 1;
    }
    else
    {
        printf("\nDone, returning %deuros to you\n", Event[i].auxPrice);
        Event[i].auxPrice -= Event[i].auxPrice;
        Event[i].auxTicketsSold -= 1;
    }
    
    //update events info
    UpdateEventDatabase();

    system("pause");
    return;
}

void VerifyTicket()
{
    system("cls");
    char userInput[10];
    int ticketID = 0;
    printf("Please insert the ID of ticket you want to verify:");
    GetInfo(userInput, 9, &ticketID);

    //get info about the ID and check if the Ticket exists
    FILE* databaseID = fopen("IDs.txt", "r");

    if (!databaseID)
    {
        printf("\nDatabase is missing!\n");
        getchar();
        fclose(databaseID);
        return;
    }

    unsigned auxID = 0;
    int aux = 0;
    char eventTicket[50];
    int VIP = 1;

    myBool found = 0;
    while (!feof(databaseID))
    {
        fscanf(databaseID, "%u %s %d %d %d %d", &auxID, eventTicket, &VIP, &aux, &aux, &aux);

        if (auxID == ticketID)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nThe ticket does not exist\n");
        system("pause");
        fclose(databaseID);
        return;
    }

    //check if the ticket´s event is still active or not
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (!strcmp(Event[i].auxName, eventTicket))
        {
            if (!CheckUserInputDate(Event[i].auxDay, Event[i].auxMonth, Event[i].auxYear))
            {
                printf("Ticket state: INVALID\n");
                break;
            }
            break;
        }
    }

    //display final info
    if (VIP == 0)
    {
        printf("\n%d - %s VIP seat\n", ticketID, eventTicket);
    }
    else
    {
        printf("\n%d - %s Regular seat\n", ticketID, eventTicket);
    }
    
    fclose(databaseID);

    system("pause");
}

void ShowActiveEvents()
{
    //Display only active events
    FILE* Original = fopen("EventsDataBase.txt", "r");

    CurrentTime();

    int count = 0;
    while (!feof(Original))
    {
        
        //otherwise this simply bugs
        fscanf(Original, "%d %s %d %d %d %d %d %d %d %d %d",
            &(Event[count].auxID), Event[count].auxName, &(Event[count].auxDay),
            &(Event[count].auxMonth), &(Event[count].auxYear),
            &(Event[count].auxDuration), &(Event[count].auxPrice),
            &(Event[count].auxVipPrice), &(Event[count].auxMaxPeople),
            &(Event[count].auxTicketsSold), &(Event[count].MoneyMade));

        if (Event[count].auxID == 0) break;

        if (Event[count].auxYear < todayDate.Year ||
            (Event[count].auxMonth < todayDate.Month && Event[count].auxYear == todayDate.Year) ||
            (Event[count].auxDay < todayDate.Day && Event[count].auxMonth == todayDate.Month && Event[count].auxYear == todayDate.Year))
        {
        }
        else
        {
            printf("%d %s Date:%d/%d/%d Duration:%d Price:%d VIP Price:%d Max people:%d\n",
                Event[count].auxID, Event[count].auxName, Event[count].auxDay,
                Event[count].auxMonth, Event[count].auxYear,
                Event[count].auxDuration, Event[count].auxPrice,
                Event[count].auxVipPrice, Event[count].auxMaxPeople);
        }
        count++;
    }
    fclose(Original);
}

void DeleteTicketFromDatabase(int ID)
{
    FILE* file1 = fopen("IDs.txt", "r");
    FILE* file2 = fopen("tempIDs.txt", "w"); //creates temp file
    
    unsigned auxID = 0;
    int Day = 0, Month = 0, Year = 0, VIP = 0; 
    char name[50] = "";

    myBool adjust = 0;
    while (!feof(file1))
    {
        fscanf(file1, "%u %s %d %d %d %d", &auxID, name, &VIP, &Day, &Month, &Year);
        if (ID == auxID)
        {
            adjust = 1;
        }
        else
        {
            fprintf(file2, "\n%u %s %d %d %d %d", auxID, name, VIP, Day, Month, Year);
        }     
    }
    fclose(file1); 
    fclose(file2);

    remove("IDs.txt");
    rename("tempIDs.txt", "IDs.txt");
}

