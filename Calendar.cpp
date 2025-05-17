#include "Calendar.h"

Date::Date(int yr , int mon, int d ) :
    year(yr),
    month(mon),
    day(d)
{
    nDay[0] = 31;
    nDay[1] = (isLeap(year)) ? 29 : 28;
    nDay[2] = 31;
    nDay[3] = 30;
    nDay[4] = 31;
    nDay[5] = 30;
    nDay[6] = 31;
    nDay[7] = 31;
    nDay[8] = 30;
    nDay[9] = 31;
    nDay[10] = 30;
    nDay[11] = 31;
    months[0] = "January";
    months[1] = "February";
    months[2] = "March";
    months[3] = "April";
    months[4] = "May";
    months[5] = "June";
    months[6] = "July";
    months[7] = "August";
    months[8] = "September";
    months[9] = "October";
    months[10] = "November";
    months[11] = "December";
}
bool Date::isLeap(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return true;
    return false;
}

Calendar::Calendar(int yr, int mon, int d) : Date(yr, mon, d), firstDay(0), id(0), exist(false), fileName("")
{ 
    cFile.open("2.718281828459045235.txt", ios::in);
    if (!cFile.is_open())
    {
        return;
    }
    int size, year, month, dy;
    size = year = month = dy = 0;
	string event;
    if (cFile >> size)
    {
        exist = true;
        id = size;
		for (int i = 0; i < size; i++)
		{
			cFile >> year >> month >> dy;
            cFile.ignore();
			getline(cFile, event);
			events.push_back(Event(dy, month, year, event));
		}
    }
    cFile.close();
}
Calendar::~Calendar()
{
    cFile.open("2.718281828459045235.txt", ios::out | ios::trunc);
    if (id >= 1)
    {
	    if (!cFile)
	    {
		    cerr << "An error has occurred\n";
		    exit(1);
	    }
		cFile << id << endl;
        for (int i = 0; i < id; i++)
        {
            events[i].vipPrintFile(cFile);
        }
    }
    cFile.close();
}

int Calendar::getFirstDay(int yr, int mon)
{
    int days = 0;
    int m = mon;
    if (mon < 3)
    {
        m += 12;
        yr--;
    }
    return (days + (13 * (m + 1)) / 5 + yr + (yr / 4) - (yr / 100) + (yr / 400)) % 7;
}

void Calendar::printMenu()
{
    cout << "\n\n==============================================================================================\n"
        << setw(54) << "Program Commands\n"
        << "==============================================================================================\n"
        << "1. [p] - Previous Month " << "                                2. [n] - Next Month\n"
        << "3. [c] - Current Month  " << "                                4. [s] - Select a specific Date\n"
        << "5. [a] - Add Event      " << "                                6. [l] - Show all events created\n"
        << "7. [d] - Input ID to Delete Event " << "                      8. [f] - Write events to a file\n"
        << "9. [i] - Read all the events stored in file " << "           10. [g] - Go to a specific event\n"
        << "11.[u] - Go to the same day last week " << "                 12. [b] - Go to the same day next week\n"
        << "13.[< / >] - Go to the next day or previous day" << "        14. [q] - Quit the program\n\n";
        
}

void Calendar::enterEvent(int day, int mon, int yr, string ev)
{
    int d = day,
        m = mon,
        y = yr;
    string event = ev;
    events.push_back(Event(d, m, y, event));
    id++;
}

void Calendar::deleteEvent(int index)
{
    if (index >= 0 && index < events.size())
    {
        events.erase(events.begin() + index);
        id--;
    }
    else
    {
        cout << "Invalid event id." << endl;
    }
}

void Calendar::eReminder(bool created)
{
    int leastDays = 30000;
    bool found = false;
    if (created)
    {
        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getyear() == year && events[i].getmonth() == month)
            {
                int dRem = events[i].getday();
                if (dRem == day)
                {
                    cout << "Event Day!\n";
                    found = false;
                    break;
                }
                else if (dRem > day)
                {
                    if (leastDays > (dRem - day))
                    {
                        leastDays = dRem - day;
                    }
                    found = true;
                }
            }
        }
        if (found)
            cout << leastDays << " days remaining to next event!\n";
        else
            cout << endl;
    }
    else { cout << endl; }
}

void Calendar::especReminder(int mon, int yr, int d, bool created)
{
    int leastDays = 30000;
    bool found = false;
    if (created)
    {
        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getyear() == yr && events[i].getmonth() == mon)
            {
                int dRem = events[i].getday();
                if (dRem == d)
                {
                    cout << "Event Day!";
                    found = false;
                    break;
                }
                else if (dRem > d)
                {
                    if (leastDays > (dRem - d))
                    {
                        leastDays = dRem - d;
                    }
                    found = true;
                }
            }
        }
        if (found)
            cout << leastDays << " days remaining to next event!\n";
        else
            cout << endl;
    }
    else { cout << endl; }
}

void Calendar::fileOperation(string file)
{
    fstream ioFile(file.c_str(), ios::out | ios::trunc);
    if (!ioFile)
    {
        cerr << "Error opening file for writing.\n";
        return;
    }
    fileName = file;
    system("CLS");
    cout << "File operation underway...";
    Sleep(1000);
    cout << "\nWriting all " << id << " into file...";
    Sleep(id * 500);
    for (int i = 0; i < events.size(); i++)
    {
        events[i].printinFile(ioFile);
    }
    cout << "\nOperation complete\n";
    ioFile.close();
}

void Calendar::printEvents()
{
    cout << "\nALL Events:\n";
    for (int i = 0; i < events.size(); i++)
    {
        cout << i + 1 << ". ";
        events[i].printEvent();
    }
}

void Calendar::fileReading(string file)
{
	
    ifstream ioFile(file.c_str());
    string line;
    while (getline(ioFile, line)) {
        cout << line << endl;
    }
    ioFile.close();
}

void Calendar::printcuCal(bool created)
{
    if (exist)
        created = true;
    firstDay = getFirstDay(year, month);
    cout << setw(13) << getMonthName() << setw(13) << year << " "; eReminder(created);
    cout << "***************************" << endl
        << "Sun Mon Tue Wed Thu Fri Sat" << endl;
	printCal(month, year, day, created);
    printMenu();
}

void Calendar::printspecCal(int mon, int year, int d, int ID,  bool created)
{
    if (mon == 2)
        nDay[mon-1] = (isLeap(year)) ? 29 : 28;

    if (d > nDay[mon - 1])
        d = nDay[mon - 1];

    system("CLS");
    if (exist)
        created = true;
    if (year < 1)
    {
        year = (-year) + 1;
        cout << setw(13) << months[mon - 1] << setw(13) << year << " BCE "; especReminder(mon, year, d, created);
        cout << "***************************" << endl
            << "Sun Mon Tue Wed Thu Fri Sat" << endl;
    }
    else
    {
        cout << setw(13) << months[mon - 1] << setw(13) << year << " "; especReminder(mon, year, d, created);
        cout << "***************************" << endl
            << "Sun Mon Tue Wed Thu Fri Sat" << endl;
    }

    /*if (mon == month && year == this->year && !ID)
        d = day;*/

	printCal(mon, year, d, created);
    printMenu();
}

void Calendar::printCal(int mon, int yr, int d, bool created)
{
    int fDay = getFirstDay(yr, mon);

    if (fDay == 1)
        cout << setw(5 * fDay);
    else if (fDay == 2)
        cout << setw(4.5 * fDay);
    else if (fDay == 4 || fDay == 5 || fDay == 6)
        cout << setw(4.33 * fDay);
    else
        cout << setw(4.5 * fDay);

    int dCount = fDay + 1;
    int tday = nDay[mon - 1];
    vector<int>eday;
    if (created)
    {
        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getyear() == year && events[i].getmonth() == mon)
            {
                eday.push_back(events[i].getday());
            }
        }
        sort(eday.begin(), eday.end());
        int size = eday.size(), j = 0;
        for (int i = 1; i <= tday; i++)
        {
            if (j < size && i == eday[j])
            {
                if (i < 10)
                {
                    if (d != eday[j])
                    {
                        if (dCount % 7 != 0)
                        {
                            if (i == d)
                                cout << "[" << i << "]" << setw(2);
                            if (i == eday[j])
                                cout << "|" << i << "|" << setw(2);
                            else
                                cout << " " << i << setw(3);
                        }
                        else
                        {
                            if (i == d)
                                cout << "[" << i << "]" << endl;
                            if (i == eday[j])
                                cout << "|" << i << "|" << endl;
                            else
                                cout << " " << i << endl;
                        }
                    }
                    else
                    {
                        if (dCount % 7 != 0)
                        {
                            if (i == d)
                                cout << "[" << i << "]" << setw(2);
                            else
                                cout << " " << i << setw(3);
                        }
                        else
                        {
                            if (i == d)
                                cout << "[" << i << "]" << endl;
                            else
                                cout << " " << i << endl;
                        }
                    }
                }
                else
                {
                    if (d != eday[j])
                    {
                        if (dCount % 7 != 0)
                        {
                            if (i == d)
                                cout << "[" << i << "]" << setw(1);
                            if (i == eday[j])
                                cout << "|" << i << "|" << setw(1);
                            else
                                cout << " " << i << setw(2);
                        }

                        else
                        {
                            if (i == d)
                                cout << "[" << i << "]\n";
                            if (i == eday[j])
                                cout << "|" << i << "|\n";
                            else
                                cout << " " << i << endl;
                        }
                    }
                    else
                    {
                        if (dCount % 7 != 0)
                        {
                            if (i == d)
                                cout << "[" << i << "]" << setw(1);
                            else
                                cout << " " << i << setw(2);
                        }
                        else
                        {
                            if (i == d)
                                cout << "[" << i << "]\n";
                            else
                                cout << " " << i << endl;
                        }
                    }
                }
                dCount++;
                j++;
            }
            else
            {
                if (i < 10)
                {
                    if (dCount % 7 != 0)
                    {
                        if (i == d)
                            cout << "[" << i << "]" << setw(2);
                        else
                            cout << " " << i << setw(3);
                    }
                    else
                    {
                        if (i == d)
                            cout << "[" << i << "]" << endl;
                        else
                            cout << " " << i << endl;
                    }
                }
                else
                {
                    if (dCount % 7 != 0)
                    {
                        if (i == d)
                            cout << "[" << i << "]" << setw(1);
                        else
                            cout << " " << i << setw(2);
                    }
                    else
                    {
                        if (i == d)
                            cout << "[" << i << "]\n";
                        else
                            cout << " " << i << endl;
                    }
                }
                dCount++;
            }
        }
    }
    else
    {
        for (int i = 1; i <= tday; i++)
        {
            if (i < 10)
            {
                if (dCount % 7 != 0)
                {
                    if (i == d)
                        cout << "[" << i << "]" << setw(2);
                    else
                        cout << " " << i << setw(3);
                }
                else
                {
                    if (i == d)
                        cout << "[" << i << "]" << endl;
                    else
                        cout << " " << i << endl;
                }
            }
            else
            {
                if (dCount % 7 != 0)
                {
                    if (i == d)
                        cout << "[" << i << "]" << setw(1);
                    else
                        cout << " " << i << setw(2);
                }
                else
                {
                    if (i == d)
                        cout << "[" << i << "]\n";
                    else
                        cout << " " << i << endl;
                }
            }
            dCount++;
        }
    }
    bool found = false;
    if (created)
    {
        cout << "\n\nEvents for " << months[mon - 1] << " " << yr << ":" << endl;
        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getyear() == yr && events[i].getmonth() == mon)
            {
                events[i].printEvent();
                found = true;
            }
        }
        if (!found)
        {
            cout << "\nNo events for this month.\n";
        }
    }
}