#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <array>

#ifdef _WIN32
    #include <windows.h>
#endif

struct Date {
    int dd;
    int mm;
    int yy;
};

struct Remainder {
    int dd;
    int mm;
    int yy;
    std::string note;
};

#ifdef _WIN32
    COORD xy = {0, 0};

    void gotoxy(int x, int y) {
        xy.X = x; xy.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
    }

    void SetColor(int ForgC) {
        WORD wColor;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
    }

    void ClearColor() {
        SetColor(15);
    }

    void ClearConsoleToColors(int ForgC, int BackC) {
        WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        DWORD count;
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        SetConsoleTextAttribute(hStdOut, wColor);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
            FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
            FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
            SetConsoleCursorPosition(hStdOut, coord);
        }
    }

    void SetColorAndBackground(int ForgC, int BackC) {
        WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    }
#endif

bool check_leapYear(int year) {
    if (year % 400 == 0 || (year % 100!= 0 && year % 4 == 0))
        return true;
    return false;
}

void increase_month(int *mm, int *yy) {
    ++*mm;
    if (*mm > 12) {
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int *mm, int *yy) {
    --*mm;
    if (*mm < 1) {
        --*yy;
        if (*yy < 1600) {
            std::cout << "No record available";
            return;
        }
        *mm = *mm + 12;
    }
}

int getNumberOfDays(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2: if (check_leapYear(year))
                   return 29;
               else
                   return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}

int getDayNumber(int dayOfMonth, int month, int year) {
    int t = (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400;
    t -= 2;
    return (t + dayOfMonth) % 7;
}

std::string getName(int day) {
    static const std::array<std::string, 7> daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    if (day >= 0 && day < 7) {
        return daysOfWeek[day];
    } else {
        return "Invalid day number";
    }
}

void print_date(int mm, int yy) {
    std::cout << "---------------------------\n";
    gotoxy(25, 6);
    switch (mm) {
        case 1: std::cout << "January"; break;
        case 2: std::cout << "February"; break;
        case 3: std::cout << "March"; break;
        case 4: std::cout << "April"; break;
        case 5: std::cout << "May"; break;
        case 6: std::cout << "June"; break;
        case 7: std::cout << "July"; break;
        case 8: std::cout << "August"; break;
        case 9: std::cout << "September"; break;
        case 10: std::cout << "October"; break;
        case 11: std::cout << "November"; break;
        case 12: std::cout << "December"; break;
    }
    std::cout << ", " << yy;
    gotoxy(20, 7);
    std::cout << "---------------------------";
}

void printMonthCalendar(int month, int year, const std::vector<Remainder>& events) {
    int daysInMonth = getNumberOfDays(month, year);
    std::cout << "Sun Mon Tue Wed Thu Fri Sat\n";
    int dayNumber = getDayNumber(1, month, year);
    for (int i = 0; i < dayNumber; ++i) {
        std::cout << "    ";
    }
    for (int day = 1; day <= daysInMonth; ++day) {
        std::cout << std::setw(3) << day << " ";
        bool hasEvent = false;
        for (const auto& event : events) {
            if (event.dd == day && event.mm == month && event.yy == year) {
                hasEvent = true;
                break;
            }
        }
        if (hasEvent) {
            SetColor(4); // Red text on black background
        } else {
            ClearColor(); // White text on black background
        }
        if (++dayNumber > 6) {
            dayNumber = 0;
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

void addEvent(std::vector<Remainder>& events, int dd, int mm, int yy, const std::string& note) {
    Remainder newEvent = { dd, mm, yy, note };
    events.push_back(newEvent);
}

void saveEventsToFile(const std::vector<Remainder>& events, const std::string& filename) {
    std::ofstream outFile(filename, std::ios_base::app); // Open in append mode
    if (outFile.is_open()) {
        for (const auto& event : events) {
            outFile << event.dd << "-" << event.mm << "-" << event.yy << ": " << event.note << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Unable to open file to save events.\n";
    }
}

void openLink(const std::string& command) {
#ifdef _WIN32
    std::string systemCommand = "start " + command;
#elif __APPLE__
    std::string systemCommand = "open " + command;
#else
    std::string systemCommand = "xdg-open " + command;
#endif
    system(systemCommand.c_str());
}

int main() {
    int month, year;
    std::vector<Remainder> events;
    std::cout << "Enter month and year: ";
    std::cin >> month >> year;

    print_date(month, year);
    std::cout << "\n";

    printMonthCalendar(month, year, events);

    char addMoreEvents = 'Y';
    while (addMoreEvents == 'Y' || addMoreEvents == 'y') {
        int day;
        std::string note;
        std::cout << "Enter day to add event: ";
        std::cin >> day;
        std::cin.ignore();
        std::cout << "Enter event: ";
        getline(std::cin, note);
        addEvent(events, day, month, year, note);
        std::cout << "Do you want to add another event? (Y/N): ";
        std::cin >> addMoreEvents;
        std::cin.ignore();
    }

    saveEventsToFile(events, "events.txt");

    // Feature: Opening a specific C++ code file by pressing 'f'
    char action;
    std::cout << "\nPress 'f' to open the C++ code file or any other key to quit: ";
    std::cin >> action;
    if (action == 'f') {
        std::string filePath = "C:\\Users\\ElectronicsMan\\OneDrive\\Documents\\lairnimanuel\\try.exe"; // Replace 'your_cpp_file_name_here.cpp' with the actual name of your C++ file
        openLink(filePath);
    }

    return 0;
}

