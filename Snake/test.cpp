#include <iostream>
#include <locale>
#include <codecvt>
#include<Windows.h>
#include "test.h"

using namespace std;

void printHPipe(){
    // Set the locale to the user's default locale to support wide characters
    std::locale::global(std::locale(""));

    // Print the vertical pipe character
    std::wcout << L'\u2502' << L'\u2502' << std::endl;

    // Print the horizontal pipe character
    std::wcout << L'\u2500' << std::endl;

}

void printBox() {
    std::cout << "+---+" << std::endl;
    std::cout << "|   |" << std::endl;
    std::cout << "|   |" << std::endl;
    std::cout << "+---+" << std::endl;
}

void keyboard() {
    HANDLE hIn;
    HANDLE hOut;
    COORD KeyWhere;
    COORD MouseWhere;
    COORD EndWhere;
    bool Continue = TRUE;
    int KeyEvents = 0;
    int MouseEvents = 0;
    INPUT_RECORD InRec;
    DWORD NumRead;

    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Key Events   : " << endl;
    cout << "Mouse Events : " ;

    KeyWhere.X = 15;
    KeyWhere.Y = 0;
    MouseWhere.X = 15;
    MouseWhere.Y = 1;
    EndWhere.X = 0;
    EndWhere.Y = 3;

    int Count = 1;

    while (Continue)
    {
        cout << "before ReadConsoleInput" << endl;
        ReadConsoleInput(hIn,
            &InRec,
            1,
            &NumRead);
        cout << "Count : "<<Count++ << endl;
        switch (InRec.EventType)
        {
        case KEY_EVENT:
            ++KeyEvents;
            SetConsoleCursorPosition(hOut,KeyWhere);
            cout << InRec.Event.KeyEvent.uChar.AsciiChar;
            if (InRec.Event.KeyEvent.uChar.AsciiChar == 'x')
            {
                SetConsoleCursorPosition(hOut,
                    EndWhere);
                cout << "Exiting..." << endl;
                Continue = FALSE;
            }
            break;

        case MOUSE_EVENT:
            ++MouseEvents;
            //SetConsoleCursorPosition(hOut,    MouseWhere);
            //cout << MouseEvents;
            break;
        }
    }
}
/*
Vector getScreenSize() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
        std::cerr << "Error getting console screen buffer information" << std::endl;
        return;
    }
       
    return 
}*/   