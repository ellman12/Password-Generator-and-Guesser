#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Threads.hpp" //Contains thread stuff
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

    string pass = "14";

    thread test1(guessPwd, 1, true, pass);
    thread test2(guessPwd, 2, true, pass);
    thread test3(guessPwd, 3, true, pass);
    thread test4(guessPwd, 4, true, pass);
    test1.join();
    test2.join();
    test3.join();
    test4.join();
}