#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <limits>
#include <sys/stat.h>
using namespace std;


class Date
{
protected: 
    int day, month, year;
   int nDay[12];
   string months[12];

public:
    Date(int yr = 2000, int mon = 1, int d = 1);
    bool isLeap(int yr);
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    string getMonthName() const { return months[month - 1]; }
    int getDaysInMonth() const { return nDay[month - 1]; }
};

class Event {
    string eDesc;
    Date date; 

public:
    Event(int d, int m, int y, string ev) : eDesc(ev), date(y, m, d) {}
    int getyear() const { return date.getYear(); }
    int getmonth() const { return date.getMonth(); }
    int getday() const { return date.getDay(); }
    void printEvent() const {
        cout << "Date: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear()
            << "\nDescription: " << eDesc << endl << endl;
    }
    void printinFile(fstream& obj)
    {
        obj << "Date: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear()
            << "\nDescription: " << eDesc << endl << endl;
    }
    void vipPrintFile(fstream& obj)
    {
        obj << getyear() << " " << getmonth() << " " << getday() << endl
			<< eDesc << endl;
    }
};

class Calendar : public Date
{
    int firstDay;
    int id;
    fstream cFile;
    //bool exist;
    string fileName;
   
public:
	vector<Event> events;
    Calendar(int yr, int mon, int d);
    ~Calendar();
    int getFirstDay(int year, int month);
	void printcuCal();
    void printspecCal(int mon, int yr, int d, int);
    void printCal(int mon, int yr, int d, int ID = 0);
    void printMenu();
    void enterEvent(int day, int mon, int yr, string ev);
    void deleteEvent(int index);
    void printEvents();
    int printID()
    {
        return id; 
    }
    string getfName()
    {
        return fileName;
    }
    void eReminder();
    void especReminder(int mon, int yr, int d);
    void fileOperation(string file);
    void fileReading(string file);
};
