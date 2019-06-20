#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

class Date
{
    private:
    int day, month, year;

    public:
    Date();
    Date(int, int, int);
    void setDate(int, int, int);
    void setDate(Date);
    int getDay();
    int getMonth();
    int getYear();
    Date getDate();
    void validateDate();
    void askForDate();
    void printDate();
    int operator==(Date otherDate);
    int operator!=(Date othreDate);
    int operator>(Date otherDate);
    int operator<(Date otherDate);
    int operator>=(Date otherDate);
    int operator<=(Date otherDate);
};

Date ::Date()
{
    day = month = year = 0;
}

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
    validateDate();
}

void Date::setDate(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
    validateDate();
}

void Date::setDate(Date date)
{
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
    validateDate();
}

int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}

Date Date::getDate()
{
    Date date(day, month, year);
    return date;
};

void Date::validateDate()
{
    if (month > 12)
        month = month % 12;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31)
            day %= 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            day %= 30;
    }
    else if (month == 4)
    {
        if (year / 4 == 0 && day > 29)
        {
            day %= 29;
        }
        else if (day > 28)
        {
            day %= 28;
        }
    }
}

void Date::askForDate()
{
    char temp;
    printf("Enter the date (dd/mm/yyyy) : ");
    fflush(stdin);
    scanf("%d%c%d%c%d", &day, &temp, &month, &temp, &year);
    validateDate();
}

void Date ::printDate()
{
    printf("%02d/%02d/%d", day, month, year);
}

int Date::operator==(Date otherDate)
{
    if (this->year == otherDate.year && this->month == otherDate.month && this->day == otherDate.day)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Date::operator!=(Date otherDate)
{
    if (*this == otherDate)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Date::operator>(Date otherDate)
{
    if (this->year > otherDate.year)
    {
        return 1;
    }
    else if (this->year < otherDate.year)
    {
        return 0;
    }

    if (this->month > otherDate.month)
    {
        return 1;
    }
    else if (this->month < otherDate.month)
    {
        return 0;
    }

    if (this->day > otherDate.day)
    {
        return 1;
    }
    return 0;
}

int Date::operator<(Date otherDate)
{
    if (this->year < otherDate.year)
    {
        return 1;
    }
    else if (this->year > otherDate.year)
    {
        return 0;
    }

    if (this->month < otherDate.month)
    {
        return 1;
    }
    else if (this->month > otherDate.month)
    {
        return 0;
    }

    if (this->day < otherDate.day)
    {
        return 1;
    }
    return 0;
}

int Date::operator>=(Date otherDate)
{
    if (*this < otherDate)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Date::operator<=(Date otherDate)
{
    if (*this > otherDate)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}