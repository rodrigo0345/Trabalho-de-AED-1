#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <windows.h>

#define MAX 200

typedef char myBool;

enum verification
{
	error = 0, accepted
};

struct Menu
{
	myBool MainMenu;
	myBool SubMenu;
} Open;

struct createdEvent
{
	char Name[50];
	int  ID;
	int  Day;
	int  Month;
	int  Year;
	int  Duration;
	int  Price;
	int  VipPrice;
	int  MaxPeople;
	int  TicketsSold;
	int  MoneyMade;
} Current;

struct EventData
{
	char auxName[50];
	int  auxID;
	int  auxDay;
	int  auxMonth;
	int  auxYear;
	int  auxDuration;
	int  auxPrice;
	int  auxVipPrice;
	int  auxMaxPeople;
	int  auxTicketsSold;
	int  MoneyMade;
} Event[200];

struct TIME
{
	int Day;
	int Month;
	int Year;
} todayDate;

//security.c
void freeBuffer();
void Exit();
void GoBack();
void Update();
void GetInfo(char[], int, int*);
unsigned int GenerateID(char[], int);
int ValidUserSelection(unsigned short, unsigned short);

//time.c
void CurrentTime();
int MonthNumOfDays(int, int);
myBool CheckUserInputDate(int, int, int);

//DisplayMenus.c
void DisplayMainMenu();
void DisplaySubMenu();

//Database.c
int GetData();
int SaveData();
void UpdateEventDatabase();

//Events.c
void DisplayEventList();









