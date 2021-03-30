#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "gthread.hpp" //Contains thread stuff
#include "PGG Rewrite.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    //The way the 3 seed args should work is that the one entered last will be used over any others. E.g, -s1234 --time --noseed. --noseed would be picked.
    // bool noSeed = false;
    // bool timeSeed = true;
    // bool usingCustomSeed = false;

    // bool usingDigits = false;
    // bool usingLower = false;
    // bool usingUpper = false;
    // bool usingSpecialChars = false;

    // bool verbose = false;
    // bool nostore = false;
    // bool customPwd = false;
    // bool showChars = false;

    srand(time(0));
    usableCharsInit(true, false, false, false, usableChars);

    for (int i = 0; i < usableChars.size(); i++)
        cout << usableChars[i];

    string pass = "17409";
    int len = pass.length();

    thread test1(guessPwdWoutStore, 1, len, pass, usableChars);
    thread test2(guessPwdWoutStore, 2, len, pass, usableChars);
    thread test3(guessPwdWoutStore, 3, len, pass, usableChars);
    thread test4(guessPwdWoutStore, 4, len, pass, usableChars);
    test1.join();
    test2.join();
    test3.join();
    test4.join();

    printf("\n");
    printline(69);
    cout << correctPassword << " was guessed after " << --totalAttempts << " attempts by thread #" << threadWinner << endl;
    printline(69);

    printline(9);
    cout << "Duration:" << endl;
    printline(9);
}