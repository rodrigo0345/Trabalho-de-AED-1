#include "master.h"
#include "time.h"

myBool CheckMonthDays(int, int, int);

int MonthNumOfDays(int, int);

void CurrentTime()
{
	time_t now;
	struct tm* tm_now;
	now = time(NULL);
	tm_now = gmtime(&now);

	todayDate.Day = tm_now->tm_mday;
	todayDate.Month = (tm_now->tm_mon) + 1;
	todayDate.Year = (tm_now->tm_year) + 1900;
}

myBool CheckDateAvailability(int Day, int Month, int Year, int auxDay, int auxMonth, int auxYear, int count)
{
	int i;
	for (i = 0; i < Current.Duration; i++)
	{
		//
		// checks according to the duration of the event created
		//
		if (Day + i > MonthNumOfDays(Month, Year))
		{
			Day = 1;
			Month++;
			if (Month > 12)
			{
				Month = 1;
				Year++;
			}
			if (auxDay == Day && auxMonth == Month && auxYear == Year)
			{
				//date already filled
				return error;
			}
		}
		else if (Day + i == auxDay && Month == auxMonth && Year == auxYear)
		{
			return error;
		}

		int j;
		for (j = 0; j < Event[i].auxDuration; j++)
		{
			//
			// checks according to the duration of the existing event
			//
			if (auxDay + j > MonthNumOfDays(auxMonth, auxYear))
			{
				auxDay = 1;
				auxMonth++;
				if (auxMonth > 12)
				{
					auxMonth = 1;
					auxYear++;
				}
				if (auxDay == Day && auxMonth == Month && auxYear == Year)
				{
					//date already filled
					return error;
				}
			}
			else if (auxDay + j == Day && auxMonth == Month && auxYear == Year)
			{
				return error;
			}
		}
	}
	return accepted;
}

myBool CheckUserInputDate(int Day, int Month, int Year)
{
	//update current time
	CurrentTime();

	if (CheckMonthDays(Day, Month, Year))
	{
		//Check if new event date is not "past"
		if (Year < todayDate.Year ||
			(Month < todayDate.Month && Year == todayDate.Year) ||
			(Day < todayDate.Day && Month == todayDate.Month && Year == todayDate.Year))
		{
			return error;
		}
		else
		{
			return accepted;
		}
	}

	int i = 0;
	for (i = 0; i < 200; i++)
	{
		if (!CheckDateAvailability(Day, Month, Year, Event[i].auxDay, Event[i].auxMonth, Event[i].auxYear, i))
		{
			return error;
		}
	}

	return error;
}

enum MonthList
{
	January = 1, February, March,
	April, May, June, July,
	August, September, October,
	November, December
};

myBool CheckMonthDays(int Day, int Month, int year)
{
	switch (Month)
	{
	case January:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case February:
		if (year % 4 == 0)
		{
			if (Day <= 29)
			{
				return accepted;
			}
		}
		else
		{
			if (Day <= 28)
			{
				return accepted;
			}
		}
		break;
	case March:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case April:
		if (Day <= 30)
		{
			return accepted;
		}
		break;
	case May:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case June:
		if (Day <= 30)
		{
			return accepted;
		}
		break;
	case July:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case August:
		if (Day <= 30)
		{
			return accepted;
		}
		break;
	case September:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case October:
		if (Day <= 30)
		{
			return accepted;
		}
		break;
	case November:
		if (Day <= 31)
		{
			return accepted;
		}
		break;
	case December:
		if (Day <= 30)
		{
			return accepted;
		}
		break;
	default:
		return error;
	}
	return error;
}

int MonthNumOfDays(int month, int year)
{
	switch (month)
	{
	case January:
			return 31;
		break;
	case February:
		if (year % 4 == 0)
		{
				return 29;	
		}
		else
		{
				return 28;
		}
		break;
	case March:
			return 31;
		break;
	case April:
			return 30;
		break;
	case May:
			return 31;
		break;
	case June:
			return 30;
		break;
	case July:
			return 31;
		break;
	case August:
			return 31;
		break;
	case September:
			return 30;
		break;
	case October:
			return 31;
		break;
	case November:
			return 30;
		break;
	case December:
			return 31;
		break;
	default:
		return error;
	}
}
