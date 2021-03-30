#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Threads.hpp" //Contains thread stuff
using namespace std;

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

string seedString;
int maxLength = 50; //User can change this
unsigned long long customSeed = 0;
vector<string> args; //Store the cmd line args in a vector for ease of use

//If user specifies -v, print out stuff so they know what's happening under the hood
void verbosePrint()
{
    printf("\nPassword generation:\n");
    if (usingDigits == true)
        printf("Using digits\n");

    if (usingLower == true)
        printf("Using lowercase\n");

    if (usingUpper == true)
        printf("Using uppercase\n");

    if (usingSpecialChars == true)
        printf("Using special chars\n");

    if (customPwd == true)
        cout << "The custom password you entered is: " << correctPassword << endl;

    printf("\nSeed info:\n");
    if (noSeed == true)
        cout << "The default srand() seed will be used" << endl;

    if (timeSeed == true)
        cout << "time(0) [" << time(0) << "] is the seed" << endl;

    if (usingCustomSeed == true)
        cout << "The custom seed string you entered is: " << seedString << endl;

    if (nostore == true)
        printf("Guesses will not be stored\n");
    else
        printf("Guesses will be stored\n");

    if (showChars == true)
    {
        printf("Chars a password could contain:\n");
        for (int i = 0; i < usableChars.size(); i++)
            cout << usableChars.at(i) << ' ';
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    //GOOD WORKING STUFF ↓
    // srand(time(0));
    // usableCharsInit(true, false, false, false, usableChars);

    // for (int i = 0; i < usableChars.size(); i++)
    //     cout << usableChars[i];

    // string pass = "14";

    // thread test1(guessPwd, 1, true, pass);
    // thread test2(guessPwd, 2, true, pass);
    // thread test3(guessPwd, 3, true, pass);
    // thread test4(guessPwd, 4, true, pass);
    // test1.join();
    // test2.join();
    // test3.join();
    // test4.join();

    for (int i = 0; i < argc; i++) //Add args to vector
        args.push_back(argv[i]);

    for (int i = 0; i < argc; i++) //First determine if verbose or if --help was specified
    {
        if (args[i] == "-v")
            verbose = true;
        else if (args[i] == "--help")
        {
            help();
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < argc; i++) //Apply command line args
    {
        if ((args[i][0] == '-') && (args[i][1] == 'p'))
        {
            correctPassword.resize(args[i].length() - 2); //Make large enough to store user's password (-2 because of -p)
            customPwd = true;

            for (int j = 2; j < args[i].length(); j++) //Strip the -p and store the rest in password
                correctPassword[j - 2] = args[i][j];

            for (int j = 0; j < correctPassword.length(); j++) //Analyze user's password and determine what kind of chars it contains
            {
                if ((usingDigits == false) && (isdigit(correctPassword[j])))
                    usingDigits = true;

                if ((usingLower == false) && (islower(correctPassword[j])))
                    usingLower = true;

                if ((usingUpper == false) && (isupper(correctPassword[j])))
                    usingUpper = true;

                if ((usingSpecialChars == false) && (isSpecialChar(correctPassword[j], &usingSpecialChars)))
                    usingSpecialChars = true;
            }
        }

        else if ((customPwd == false) && (args[i] == "-d"))
            usingDigits = true;

        else if ((customPwd == false) && (args[i] == "-l"))
            usingLower = true;

        else if ((customPwd == false) && (args[i] == "-u"))
            usingUpper = true;

        else if ((customPwd == false) && (args[i] == "-s"))
            usingSpecialChars = true;

        else if (args[i][0] == '-' && args[i][1] == 'L')
        {
            string tmp;
            tmp.resize(10);
            for (int j = 2; j < args[i].length(); j++)
                tmp[j - 2] = args[i][j];

            passLen = stoi(tmp);

            if (verbose)
                cout << "Length specified by you as: " << passLen << endl;
        }

        else if (args[i][0] == '-' && args[i][1] == 'M')
        {
            string tmp;
            tmp.resize(10);
            for (int j = 2; j < args[i].length(); j++)
                tmp[j - 2] = args[i][j];

            maxLength = stoi(tmp);

            if (verbose)
                cout << "Max password length specified by you as: " << maxLength << endl;
        }

        else if (args[i] == "--nostore")
            nostore = true;

        else if (args[i] == "--showchars")
            showChars = true;

        else if (args[i] == "--noseed")
        {
            noSeed = true;
            timeSeed = false;
            usingCustomSeed = false;
        }

        else if (args[i] == "--time")
        {
            srand(time(0));
            timeSeed = true;
            noSeed = false;
            usingCustomSeed = false;
        }

        else if ((args[i][0] == '-') && (args[i][1] == 'S') && (args[i][2] != '\0'))
        {
            usingCustomSeed = true;
            noSeed = false;
            timeSeed = false;

            seedString.resize(args[i].length() - 2); //Make large enough to store the number (-2 because of -S)

            for (int j = 2; j < args[i].length(); j++) //Strip the -S and store the rest
                seedString[j - 2] = args[i][j];

            customSeed = stoull(seedString); //Make number and apply the custom seed
            std::srand(customSeed);
        }
    }
    if (verbose)
        verbosePrint();
}
