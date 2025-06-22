
#include "Calendar.h"

int typeValidation();

bool fileExists(const string& filename) 
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool isLeap(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return true;
    return false;
}

int nDay[] = { 31, 28, 31, 30, 31,
                30, 31, 31, 30,
                31, 30, 31 };

bool choiceA(int &yr, int &mon, int &d)
{
    cout << "Enter Month (>=1) and (<=12): ";
    //cin.ignore();
    mon = typeValidation();
    if (mon > 0)
    {
        while (mon > 12)
        {
            cerr << "Invalid month. Please enter a month (<=12): ";
            mon = typeValidation();
            if (mon > 0)
            {
                if (mon <= 12)
                    break;
                else
                    continue;
            }
            else if (mon < 0)
            {
                cout << "Invalid input. Month is out of range!\n\n";
                mon = 0;
                break;
            }
            else
                break;
        }
    }
    else if (mon < 0)
    {
        cout << "Invalid input. Month is out of range!\n\n";
        return false;
    }
    else
    {
        cout << "Try again!\n\n";
        return false;
    }
    if (!mon)
    {
        cout << "Try again!\n\n";
        return false;
    }
    cout << "Enter Year (>=1): ";
    //cin.ignore();
    yr = typeValidation();
    if (!yr)
    {
        cout << "Try again!\n\n";
        return false;
    }
    cout << "Enter Day: ";
    //cin.ignore();
    d = typeValidation();
    if (d > 0)
    {
        while (d > nDay[mon - 1])
        {
            cerr << "Invalid day. Please enter a day (<" << nDay[mon - 1] << "): ";
            d = typeValidation();
            if (d > 0)
            {
                if (d <= nDay[mon - 1])
                    break;
                else
                    continue;
            }
            else if (d < 0)
            {
                cout << "Invalid input. Day is out of range!\n\n";
                d = 0;
                break;
            }
            else
                break;
        }
    }
    else if (d < 0)
    {
        cout << "Invalid input. Day is out of range!\n\n";
        d = 0;
        return false;
    }
    else
    {
        cout << "Try again!\n\n";
        return false;
    }
    if (!d)
    {
        cout << "Try again!\n\n";
        return false;
    }
    return true;
}

bool choiceS(int& yr, int& mon, int& day, int currentDay)
{
    char choice;
    cout << "Enter Month (>=1) and (<=12): ";
    //cin.ignore();
    mon = typeValidation();
    if (mon > 0)
    {
        while (mon > 12)
        {
            cerr << "Invalid month. Please enter a month (<=12): ";
            mon = typeValidation();
            if (mon > 0)
            {
                if (mon <= 12)
                    break;
                else
                    continue;
            }
            else if (mon < 0)
            {
                cout << "Invalid input. Month is out of range!\n\n";
                mon = 0;
                break;
            }
            else
                break;
        }

    }
    else if (mon < 0)
    {
        cout << "Invalid input. Month is out of range!\n\n";
        return false;
    }
    else
    {
        cout << "Try again!\n\n";
        return false;
    }
    if (!mon)
    {
        cout << "Try again!\n\n";
        return false;
    }
    cout << "Enter Year (>=1): ";
    //cin.ignore();
    yr = typeValidation();
    if (!yr)
    {
        cout << "Try again!\n\n";
        return false;
    }

    cout << "Do you want to [ENTER] a specific day? (Y/N): ";
    cin >> choice;
    cin.ignore();
    choice = toupper(choice);

    if (choice == 'Y')
    {
        cout << "Enter Day: ";
        //cin.ignore();
        day = typeValidation();
        if (day > 0)
        {
            while (day > nDay[mon - 1])
            {
                cerr << "Invalid day. Please enter a day (<" << nDay[mon - 1] << "): ";
                day = typeValidation();
                if (day > 0)
                {
                    if (day <= nDay[mon - 1])
                        break;
                    else
                        continue;
                }
                else if (day < 0)
                {
                    cout << "Invalid input. Day is out of range!\n\n";
                    day = 0;
                    break;
                }
                else
                    break;
            }
        }
        else if (day < 0)
        {
            cout << "Invalid input. Day is out of range!\n\n";
            day = currentDay;
            return false;
        }
        else
        {
            cout << "Try again!\n";
            return false;
        }
        if (!day)
        {
            cout << "Try again!\n\n";
            return false;
        }
    }
    else if (choice == 'N')
    {
        day = 1;
    }
    else
    {
        cerr << "Invalid input. Enter Y/N next time!\n";
        return false;
    }
    return true;
}



int main()
{

    time_t now = time(NULL);
    tm cTime;
    tm* pTime = &cTime;
    localtime_s(pTime, &now);
    
    int currentYear = pTime->tm_year + 1900;
    int currentMonth = pTime->tm_mon + 1;
    int currentDay = pTime->tm_mday;
    bool created = false;
    Calendar cal(currentYear, currentMonth, currentDay);
    cal.printcuCal();
    
	
    string fName; char choice;
    
    int mon = currentMonth, yr = currentYear, day = currentDay;
    int id = 0;
    do 
    {
        if (mon == 0 || day == 0 || yr == 0)
        {
			mon = currentMonth;
			day = currentDay;
			yr = currentYear;
        }
        cout << "[ENTER] Program Command: ";
        string input;
        getline(cin, input);
        choice = input.empty() ? '\0' : toupper(input[0]);
        switch (choice) 
        {
            case 'N': // Next month
                mon++;
                if (mon > 12) 
                {
                    yr++;
                    mon = 1;
                }
                cal.printspecCal(mon, yr, day, id);
                break;

            case 'P': // Previous month
                mon--;
                if (mon < 1) 
                {
                    yr--;
                    mon = 12;
                }
                cal.printspecCal(mon, yr, day, id);
                break;
            case 'C': // Current month
            {
                mon = currentMonth;
                yr = currentYear;
                day = currentDay;
                system("CLS");
                cal.printcuCal();
                break;
            }

            case 'U':
            {
                day -= 7;
                if (day < 1)
                {
                    mon--;
                    nDay[1] = isLeap(yr) ? 29 : 28;
                    if (mon < 1)
                    {
                        yr--;
                        mon = 12;
                        nDay[1] = isLeap(yr) ? 29 : 28;
                    }
                    day += nDay[mon - 1]; 
                }
                cal.printspecCal(mon, yr, day, id);
                break;
            }
            case 'B':
            {
                day += 7;
                if (day > nDay[mon - 1])
                {
                    day -= nDay[mon - 1];
                    mon++;
                    nDay[1] = isLeap(yr) ? 29 : 28;
                    if (mon > 12)
                    {
                        yr++;
                        mon = 1;
                        nDay[1] = isLeap(yr) ? 29 : 28;
                    }
                }
                cal.printspecCal(mon, yr, day, id);
                break;
            }
            case '<':
            {
				day--;
				if (day < 1)
				{
					mon--;
                    nDay[1] = isLeap(yr) ? 29 : 28;
					if (mon < 1)
					{
						yr--;
						mon = 12;
                        nDay[1] = isLeap(yr) ? 29 : 28;
					}
					day = nDay[mon - 1]; 
				}
				cal.printspecCal(mon, yr, day, id);
				break;
            }
            case '>':
            {
				day++;
				if (day > nDay[mon - 1])
				{
                    day = 1;
					mon++;
                    nDay[1] = isLeap(yr) ? 29 : 28;
					if (mon > 12)
					{
						yr++;
						mon = 1;
                        nDay[1] = isLeap(yr) ? 29 : 28;
					}
				}
				cal.printspecCal(mon, yr, day, id);
				break;
            }
            case 'S': // Select specific date
            {
                if (choiceS(yr, mon, day, currentDay))
                    cal.printspecCal(mon, yr, day, id);

                break;
            }

            case 'A': // Add event
            {
                string event;
                if (choiceA(yr, mon, day))
                {
                    cout << "[ENTER] Event: ";
                    cin.ignore();
                    getline(cin, event);
                    cal.enterEvent(day, mon, yr, event);
                    cal.printspecCal(mon, yr, day, id);
                }
                break;
            }

            case 'L':
                if (cal.printID() > 0)
                    cal.printEvents();
                else
                    cout << "\nNo events to display.\n"
                        << "Press [a] - to add an event\n\n";
                break;

            case 'D': // Delete event
            {
                id = 0;
                if (cal.printID() > 0)
                {
                    cal.printEvents();
                    cout << "Total number of ids is: " << cal.printID()
                        << "\n[ENTER] the id to delete: ";
                    id = typeValidation();
                    if (id > 0)
                    {
                        if (id > cal.printID())
                        {
                            cout << "\nInvalid input. Value out of range. Next time enter an id (<=" << cal.printID() << ")\n\n";
                            continue;
                        }
                        else
                        {
                            cal.deleteEvent(id - 1);
                            if (cal.printID() == 0)
                                created = false;
                            id = 0;
                            cal.printspecCal(mon, yr, day, id);
                        }
                    }
                    else if( id < 0)
                    {
                        
                        cout << "Invalid input. ID is out of range!\n\n";
                        id = 0;
                        continue;
                    }
                    else
                    {
                        cout << "Try again!\n\n";
                        id = 0;
                        continue;
                    }
                }
                else
                    cout << "\nNo events to delete.\n"
                         << "Press [a] - to add an event\n\n";

                break;
            }

            case 'F':
            {
				if (cal.printID() == 0)
				{
					cout << "\nNo events to write to a file.\n"
						<< "Press [a] - to add an event\n\n";
					continue;
				}
                cout << "[ENTER] a filename to now copy all the current events to it: ";
                cin >> fName;
                cal.fileOperation(fName);
                cal.printMenu();
                break;
            }

            case 'I':
            {
                if (fName == "")
                {
                    cout << "No file name provided. Do you want to enter the filename(Y/N): ";
                    getline(cin, input);
                    choice = input.empty() ? '\0' : toupper(input[0]);
                    if (choice == 'Y')
                    {
                        cout << "[ENTER] a filename to read all the events from it: ";
                        cin >> fName;
                    }
					else if (choice == 'N')
					{
						cout << "Exiting Program...\n\n";
						break;
					}
					else
                    {
                        cout << "No file name provided. Exiting...\n\n";
                        break;
                    }
                }
                else
                {
                    cout << "\nDo you want to enter the filename or read the events stored in " << fName << " file? (Y/N)\n"
                        << "[ENTER] Y - to enter a new filename / N - to read events stored in " << fName << ": ";
                    getline(cin, input);
                    choice = input.empty() ? '\0' : toupper(input[0]);
                    if (choice == 'Y')
                    {
                        cout << "[ENTER] a filename to read all the events from it: ";
                        cin >> fName;
                    }
					else if (choice == 'N')
					{
                        cal.fileReading(fName); 
						break;
					}
					else
					{
						cout << "No file name provided. Exiting...\n\n";
						break;
					}
                }
				bool exists = fileExists(fName);
				if (exists)
				{
                    cout << "Outputing events stored in " << fName << " file...\n\n";
                    Sleep(cal.printID() * 500);
					cal.fileReading(fName);
                    cin.ignore();
				}
				else
				{
                    fName = cal.getfName();
					cout << "File not found.\n\n";
					continue;
				}
                break;
            }

            case 'G':
            {
                if (cal.printID() > 0)
                {
                    system("CLS");
                    cal.printEvents();
                    cout << "Pick an event, by it's id, and it's Calendar will be displayed: ";

                    id = typeValidation();
                    if (id)
                    {
                        if (id > cal.printID())
                        {
                            cout << "\nInvalid input. Value out of range. Try again!\n\n";
                        }

                        else
                        {
                            mon = cal.events[id - 1].getmonth();
                            yr = cal.events[id - 1].getyear();
                            day = cal.events[id - 1].getday();
                            cal.printspecCal(mon, yr, day, id);
                            id = 0;
                        }
                    }
                    else
                    {
                        cout << "\nNo events to display.\n"
                            << "Press [a] - to add an event\n\n";
                        continue;
                    }
                }
                else
				    cout << "\nNo events to display.\n"
                        << "Press [a] - to add an event\n\n";
                break;
            }
            case 'Q': // Quit
                cout << "Exiting the program.\n";
                break;

            default:
                cerr << "Invalid input. Please refer to the Program commands.\n\n";
                break;
        }

    } while (choice != 'Q');

    return 0;
}

//Error Handling
int typeValidation()
{
    int id = 0;
    string input;
    cin >> input;

    try
    {
        id = stoi(input); // This may throw
        if (id > 0)
            return id;
        else
            throw out_of_range("\nInvalid input. Value out of range.\n");
    }
    catch (const invalid_argument&)
    {
        cerr << "\nInvalid input. Please enter an integer number.\n";
    }
    catch (const out_of_range& e)
    {
        //cerr << e.what();
        return id;
	}
	catch (...)
	{
		cerr << "\nAn unexpected error occurred. Please try again. " << endl;
	}
    cin.clear();
    cin.ignore();
    return 0;
}
