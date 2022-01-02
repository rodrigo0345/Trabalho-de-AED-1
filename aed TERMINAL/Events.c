#include "master.h"

void DisplayEventList();

void Create()
{
    system("cls");

    printf("______________________| Create |______________________");

    printf("\nName of the event:");
    fgets(Current.Name, 20, stdin);
    freeBuffer();

    //Gets rid of the '\n' in the end of the string
    Current.Name[strlen(Current.Name) - 1] = 0;

    if (Current.Name == "\n")
    {
        printf("\nName is invalid, returning to MainMenu...");
        getchar();
        return;
    }
    char UserInput[8];

    printf("\nDay of the event:");
    GetInfo(UserInput, 3, &Current.Day);

    printf("\nMonth of the event:");
    GetInfo(UserInput, 3, &Current.Month);

    printf("\nYear of the event:");
    GetInfo(UserInput, 5, &Current.Year);

    printf("\nDuration of the event:");
    GetInfo(UserInput, 5, &Current.Duration);

    if (CheckUserInputDate(Current.Day, Current.Month, Current.Year) == error || Current.Duration == 0)
    {
        printf("\nDate is invalid, returning to MainMenu...");
        getchar();
        return;
    }

    printf("\nPrice of the ticket:");
    GetInfo(UserInput, 5, &Current.Price);

    printf("\nvipPrice of the ticket:");
    GetInfo(UserInput, 5, &Current.VipPrice);

    printf("\nMax people for the Event:");
    GetInfo(UserInput, 7, &Current.MaxPeople);

    if (!ValidUserSelection(Current.MaxPeople, 34568))
    {
        printf("\nMax People is invalid, returning to MainMenu...");
        getchar();
        return;
    }

    Current.ID = -1; //this enables the event to be saved

    if (SaveData() == 0) {
        printf("Database is missing!");
        return;
    }

    printf("\nEvent Created!");
    getchar();
}
void Search()
{
    system("cls");

    char c_auxInput[50];
    printf("Search for event name: ");

    scanf("%s", c_auxInput);

    int i;
    for (i = 0; i < MAX; i++)
    {
        if (!strcmp(c_auxInput, Event[i].auxName))
        {
            printf("% d % s Day:% d Month:% d Year:% d Duration:% d Price:% d VIP Price:% d Max people:% d Tickets sold:% d Money made:% d \n",
                (Event[i].auxID), Event[i].auxName, (Event[i].auxDay),
                (Event[i].auxMonth), (Event[i].auxYear),
                (Event[i].auxDuration), (Event[i].auxPrice),
                (Event[i].auxVipPrice), (Event[i].auxMaxPeople),
                (Event[i].auxTicketsSold), (Event[i].MoneyMade));
        }
    }
    system("pause"); //getchar() is not working here!!!
}
void UpdateEventInfo()
{
    system("cls");

    DisplayEventList();

    char UserInput[50];
    int selection = 0;
    printf("\nSelect an Event to update info: ");
    GetInfo(UserInput, 4, &selection);

    if (Event[selection - 1].auxID == 0) return;

    if (Event[selection - 1].auxTicketsSold != 0)
    {
        printf("The event you selected already sold tickets!");
        system("pause");
        return;
    }

    system("cls");

    //display specified event
    printf("%d %s Date:%d/%d/%d Duration:%d Price:%d VIP Price:%d Max people:%d Tickets sold:%d Money made:%d \n",
        (Event[selection - 1].auxID), (Event[selection - 1].auxName), (Event[selection - 1].auxDay),
        (Event[selection - 1].auxMonth), (Event[selection - 1].auxYear),
        (Event[selection - 1].auxDuration), (Event[selection - 1].auxPrice),
        (Event[selection - 1].auxVipPrice), (Event[selection - 1].auxMaxPeople),
        (Event[selection - 1].auxTicketsSold), (Event[selection - 1].MoneyMade));

    int newSelection = 0;
    printf("\n[1] Update Name");
    printf("\n[2] Update Date");
    printf("\n[3] Update Duration");
    printf("\n[4] Update Prices");
    printf("\n[5] Update Max People");
    printf("\nSelect one of the items above: ");
    GetInfo(UserInput, 4, &newSelection);

    int aux1 = 0, aux2 = 0, aux3 = 0;
    switch (newSelection)
    {
    case 1:
        freeBuffer();
        printf("\nWrite a new name: ");
        scanf("%s", Event[selection - 1].auxName);

        break;
    case 2:
        //Save data in case of error
        aux1 = Event[selection - 1].auxDay;
        aux2 = Event[selection - 1].auxMonth;
        aux3 = Event[selection - 1].auxYear;

        printf("\nSelect a new Day: ");
        GetInfo(UserInput, 4, &Event[selection - 1].auxDay);

        printf("Select a new Month: ");
        GetInfo(UserInput, 4, &Event[selection - 1].auxMonth);

        printf("Select a new Year: ");
        GetInfo(UserInput, 5, &Event[selection - 1].auxYear);

        //Check the input
        if (!CheckUserInputDate(Event[selection - 1].auxDay, Event[selection - 1].auxMonth, Event[selection - 1].auxYear))
        {
            Event[selection - 1].auxDay = aux1;
            Event[selection - 1].auxMonth = aux2;
            Event[selection - 1].auxYear = aux3;
            printf("\nThe Date you typed is invalid...\n");
            system("pause");
            return;
        }
        break;
    case 3:
        //Save data in case of error
        aux1 = Event[selection - 1].auxDuration;
        printf("\nSelect a new Duration: ");
        GetInfo(UserInput, 6, &Event[selection - 1].auxDuration);

        if (Event[selection - 1].auxDuration <= 0)
        {
            Event[selection - 1].auxDuration = aux1;
            printf("\nInput not accepted!\n");
            system("pause");
            return;
        }
        break;
    case 4:
        //Save data in case of error
        aux1 = Event[selection - 1].auxPrice;
        aux2 = Event[selection - 1].auxVipPrice;

        printf("\nNew Price: ");
        GetInfo(UserInput, 6, &Event[selection - 1].auxPrice);

        printf("New VIP Price : ");
        GetInfo(UserInput, 6, &Event[selection - 1].auxVipPrice);

        if (Event[selection - 1].auxPrice < 0 || Event[selection - 1].auxVipPrice < 0)
        {
            Event[selection - 1].auxPrice = aux1;
            Event[selection - 1].auxVipPrice = aux2;
            printf("\nInput not accepted!\n");
            system("pause");
            return;
        }
        break;
    case 5:
        //Save data in case of error
        aux1 = Event[selection - 1].auxMaxPeople;
        printf("\nSelect a new Maximum seats: ");
        GetInfo(UserInput, 6, &Event[selection - 1].auxMaxPeople);

        if (Event[selection - 1].auxMaxPeople <= 0)
        {
            Event[selection - 1].auxMaxPeople = aux1;
            printf("\nInput not accepted!\n");
            system("pause");
            return;
        }
        break;
    default:
        printf("\nInvalid Input");
    }

    //Save information again in the database
    UpdateEventDatabase();

    GetData();
    printf("\n");
    printf("\nDone!");
    
    system("pause");
}
void Delete()
{
    system("cls");

    DisplayEventList();

    char UserInput[5];
    int selection = 0;

    printf("\nSelect an event to delete: ");
    GetInfo(UserInput, 4, &selection);

    if (!ValidUserSelection(selection, MAX)) return;

    //Check if the event has 0 tickets sold
    if (Event[selection - 1].auxTicketsSold != 0)
    {
        printf("\nThe event you are trying to delete already has sold tickets!\n");
        system("pause");
        return;
    }

    //Deleting the event and reorganizing other events
    FILE* Original = fopen("EventsDataBase.txt", "w");

    myBool AdjustIDs = 0;

    int count = 0;
    while (!feof(Original))
    {   
        if (Event[count].auxID == 0 || Event[count].auxID == -1)
        {
            break;
        }
        if (Event[count].auxID == selection)
        {
            AdjustIDs = 1;
        }
        else
        {
            if (AdjustIDs)
            {
                fprintf(Original, "\n%d %s %d %d %d %d %d %d %d %d %d",
                    (--Event[count].auxID), (Event[count].auxName), (Event[count].auxDay),
                    (Event[count].auxMonth), (Event[count].auxYear),
                    (Event[count].auxDuration), (Event[count].auxPrice),
                    (Event[count].auxVipPrice), (Event[count].auxMaxPeople),
                    (Event[count].auxTicketsSold), (Event[count].MoneyMade));
            }
            else
            {
                fprintf(Original, "\n%d %s %d %d %d %d %d %d %d %d %d",
                    (Event[count].auxID), (Event[count].auxName), (Event[count].auxDay),
                    (Event[count].auxMonth), (Event[count].auxYear),
                    (Event[count].auxDuration), (Event[count].auxPrice),
                    (Event[count].auxVipPrice), (Event[count].auxMaxPeople),
                    (Event[count].auxTicketsSold), (Event[count].MoneyMade));
            }
        }
        count++;
    }
    fclose(Original);

    GetData();
    system("pause");
}
void SearchByDate()
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

    while (s_Year != e_Year || s_Month != e_Month || s_Day != e_Day)
    {
        int i;
        for (i = 0; i < MAX; i++)
        {
            if (Event[i].auxDay == s_Day && Event[i].auxMonth == s_Month && Event[i].auxYear == s_Year)
            {
                printf("\n%d Name:%s Date:%d/%d/%d Duration: %ddays", Event[i].auxID, Event[i].auxName, Event[i].auxDay, Event[i].auxMonth, Event[i].auxYear, Event[i].auxDuration);
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
    printf("\n");
    system("pause");
}
void SearchInactiveEvents()
{
    FILE* Original = fopen("EventsDataBase.txt", "r");
    system("cls");

    printf("______________________| Inactive |______________________\n\n");
    CurrentTime();

    int count = 0;
    while (!feof(Original))
    {
        if (Event[count].auxID == 0) break;

        //otherwise this simply bugs
        fscanf(Original, "%d %s %d %d %d %d %d %d %d %d %d",
            &(Event[count].auxID), Event[count].auxName, &(Event[count].auxDay),
            &(Event[count].auxMonth), &(Event[count].auxYear),
            &(Event[count].auxDuration), &(Event[count].auxPrice),
            &(Event[count].auxVipPrice), &(Event[count].auxMaxPeople),
            &(Event[count].auxTicketsSold), &(Event[count].MoneyMade));

        if (Event[count].auxYear < todayDate.Year ||
            (Event[count].auxMonth < todayDate.Month && Event[count].auxYear == todayDate.Year) ||
            (Event[count].auxDay < todayDate.Day && Event[count].auxMonth == todayDate.Month && Event[count].auxYear == todayDate.Year))
        {
            printf("%d %s Date:%d/%d/%d Duration:%d Price:%d VIP Price:%d Max people:%d Tickets sold:%d Money made:%d \n",
                Event[count].auxID, Event[count].auxName, Event[count].auxDay,
                Event[count].auxMonth, Event[count].auxYear,
                Event[count].auxDuration, Event[count].auxPrice,
                Event[count].auxVipPrice, Event[count].auxMaxPeople,
                Event[count].auxTicketsSold, Event[count].MoneyMade);
        }
        count++;
    }
    fclose(Original);

    system("pause");
}
void CheckDayAvailability()
{
    system("cls");

    char UserInput[6];
    int userDay = 0, userMonth = 0, userYear = 0;

    printf("Day: "); GetInfo(UserInput, 3, &userDay);
    printf("Month: "); GetInfo(UserInput, 3, &userMonth);
    printf("Year: "); GetInfo(UserInput, 5, &userYear);

    if (CheckUserInputDate(userDay, userMonth, userYear))
    {
        printf("\nThe date you selected is free!\n");
    }
    else
    {
        printf("\nThe date you selected is NOT free!\n");
    }
    system("pause");
}
void Update()
{
    system("cls");

    printf("Updating...");

    if (GetData() == NULL)
    {
        printf("\nDatabase is missing\n");
        system("pause");
        return;
    }
    if (SaveData() == NULL)
    {
        printf("\nNo event available to save\n");
        system("pause");
        return;
    }

    printf("\n\nDone!");
    system("pause");
}
void DisplayEventList()
{
    FILE* Data = fopen("EventsDataBase.txt", "r+");

    //Display all events
    int count = 0;
    while (!feof(Data))
    {
        //otherwise this simply bugs
        fscanf(Data, "%d %s %d %d %d %d %d %d %d %d %d",
            &(Event[count].auxID), Event[count].auxName, &(Event[count].auxDay),
            &(Event[count].auxMonth), &(Event[count].auxYear),
            &(Event[count].auxDuration), &(Event[count].auxPrice),
            &(Event[count].auxVipPrice), &(Event[count].auxMaxPeople),
            &(Event[count].auxTicketsSold), &(Event[count].MoneyMade));

        if (Event[count].auxID == 0)
        {
            fclose(Data);
            return;
        }

        printf("%d %s Day:%d Month:%d Year:%d Duration:%d Price:%d VIP Price:%d Max people:%d Tickets sold:%d Money made:%d \n",
            Event[count].auxID, Event[count].auxName, Event[count].auxDay,
            Event[count].auxMonth, Event[count].auxYear,
            Event[count].auxDuration, Event[count].auxPrice,
            Event[count].auxVipPrice, Event[count].auxMaxPeople,
            Event[count].auxTicketsSold, Event[count].MoneyMade);

        count++;
    }
    fclose(Data);
}