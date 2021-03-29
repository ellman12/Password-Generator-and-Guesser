#include <iostream>
#include <string>
#include <vector>
#include "gthread.hpp" //Contains thread stuff
// #include "PGG Rewrite.hpp"
// using namespace std;

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    // help();
    //     printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
    //     exit(EXIT_FAILURE);
    // }

    //The way the 3 seed args should work is that the one entered last will be used over any others. E.g, -s1234 --time --noseed. --noseed would be picked.
    bool noSeed = false;
    bool timeSeed = true;
    bool usingCustomSeed = false;

    bool usingDigits = false;
    bool usingLower = false;
    bool usingUpper = false;
    bool usingSpecialChars = false;

    bool verbose = false;
    bool nostore = false;
    bool customPwd = false;
    bool showChars = false;

    gthread thr1(3, "yes", true);
}