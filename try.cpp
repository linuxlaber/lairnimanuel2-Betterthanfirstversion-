#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Modified to handle both URLs and file paths
void openLink(const string& command) {
#ifdef _WIN32
    string systemCommand = "start " + command;
#elif __APPLE__
    string systemCommand = "open " + command;
#else
    string systemCommand = "xdg-open " + command;
#endif
    system(systemCommand.c_str());
}

int main() {
    cout << "\n\n\n--------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "xx             xxxxxxx         xxxxxxx         xxxxxxxxxx \n";
    cout << "xx            xxxx  xxxx         xx           xxxx     xxxx \n";
    cout << "xx           xxxx xx xxxx        xx          xxxx      xxxx \n";
    cout << "xx          xxxx      xxxx       xx         xxxxxxxxxxxxxxx \n";
    cout << "xxxxxxx    xxxx        xxxx      xx        xxxx         xxxx \n";
    cout << "xxxxxxx   xxxx          xxxx   xxxxxxx    xxxx           xxxx \n";
    cout << "\n You are on Manuel's Lair. You are trying to enter a top secret information. Beware of the owner-I mean, the code. \n\n";
    cout << "-------------------------------------------------------------------------------------------------------------------\n";

    string a = "https://docs.google.com/document/d/1cZdqC3fa5QEGwDkpeJ2ridIfFPdXk173P1XqMMmjMqE/edit?usp=sharing";
    string b = "https://docs.google.com/document/d/10DWOCD1VhYaQApmNAA7YtkIJHoR_f3jxx-BXl3Oe5w0/edit?usp=sharing";
    string c = "https://docs.google.com/document/d/1hxez_PXEoNnuQVyn1wZCgT90wxiuxHkLY0eWcUcnLFA/edit?usp=sharing";
    string d = "https://docs.google.com/document/d/1sF1Y_gmho-S0_t0XzfTxxxXP-Tr6klPCUzL2VIydIbI/edit?usp=sharing";
    string e = "https://www.youtube.com/channel/UCK3PXYE21t2EN37sX0DKE0w";
    string f = "C:\\Users\\ElectronicsMan\\OneDrive\\Documents\\Kalendaryo\\Kalendaryo.exe"; // GUYS CHANGE THE FILE PATH 
    //MY FILE PATH IS LOCATED HERE. I'LL INSTEAD MAKE A TUTORIAL
    cout << "Enter the letter of your choice:\n";
    cout << "a for Scientific Ideas\n";
    cout << "b for Thoughts\n";
    cout << "c for Data Science Projects\n";
    cout << "d for Programming Projects\n";
    cout << "e for YouTube Tutorials by me\n";
    cout << "f to Open Calendar App and Assign Events\n";
    cout << "q to Quit\n";

    char x;
    bool running = true;

    while (running) {
        cout << "Input your choice: ";
        cin >> x;

        switch (x) {
            case 'a':
                openLink(a);
                break;
            case 'b':
                openLink(b);
                break;
            case 'c':
                openLink(c);
                break;
            case 'd':
                openLink(d);
                break;
            case 'e':
                openLink(e);
                break;
            case 'f':
                openLink(f); 
                break;
            case 'q':
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        cout << "\n";
    }

    return 0;
}

