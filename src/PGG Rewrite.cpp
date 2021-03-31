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
bool justGenerating = false; //If the user just wants to generate a password

string seedString;
int maxLength = 50; //User can change this
unsigned long long customSeed = 0;
vector<string> args; //Store the cmd line args in a vector for ease of use

//If user specifies -v, print out stuff so they know what's happening under the hood
void verbosePrint()
{
    printf("\n");
    int lineLength = 49 + correctPassword.length() + 2; //Guarantee some nice line formatting :)
    printline(lineLength);
    printf("-v (verbose) print\n");
    printf("\nPassword generation:\n");
    if (usingDigits == true)
        printf("Using digits\n");

    if (usingLower == true)
        printf("Using lowercase\n");

    if (usingUpper == true)
        printf("Using uppercase\n");

    if (usingSpecialChars == true)
        printf("Using special chars\n");

    printf("\n");

    if (customPwd == true)
        cout << "The custom " << passLen << " character password you entered is: " << correctPassword << endl;

    printf("\nSeed info:\n");
    if (noSeed == true)
        cout << "The default srand() seed will be used" << endl;

    if (timeSeed == true)
        cout << "time(0) [" << time(0) << "] is the seed (default)" << endl;

    if (usingCustomSeed == true)
        cout << "The custom seed string you entered is: " << seedString << endl;

    printf("\nOther:\n");
    if (nostore == true)
        printf("Guesses will not be stored\n");
    else
        printf("Guesses will be stored (default)\n");

    if (showChars == true)
    {
        printf("Chars a password could contain:\n");
        for (int i = 0; i < usableChars.size(); i++)
            cout << usableChars.at(i) << ' ';
    }
    printline(lineLength);
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

    char input; //Used for the "press ENTER" thing later on
    int numThreads;

    for (int i = 0; i < argc; i++) //Add args to vector
        args.push_back(argv[i]);
    args.erase(args.begin()); //Remove the useless first arg (name of the executable)

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

        else if (noSeed == false && args[i] == "--noseed")
        {
            noSeed = true;
            timeSeed = false;
            usingCustomSeed = false;
        }

        else if (timeSeed == false && args[i] == "--time")
        {
            srand(time(0));
            timeSeed = true;
            noSeed = false;
            usingCustomSeed = false;
        }

        else if ((usingCustomSeed == false) && ((args[i][0] == '-') && (args[i][1] == 'S') && (args[i][2] != '\0'))) //Custom seed (-S)
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

        else if (args[i] == "--genpwd")
        {
            justGenerating = true;
        }
    }

    if (timeSeed == true)
        std::srand(time(0));

    usableChars = usableCharsInit(usingDigits, usingLower, usingUpper, usingSpecialChars);

    if (passLen <= 0)
    {
        passLen = genRandNum(1, maxLength);
        cout << "No user-specified password length. Generating rand length of: " << passLen << endl;
    }

    if (customPwd == false && justGenerating == false)
    {
        correctPassword = genPwd(passLen, usableChars);
        cout << "No user-specified password. Generating random one: " << correctPassword << endl;
    }

    if (justGenerating == true && customPwd == false)
    {
        printf("Here is your newly generated password:\n");
        correctPassword = genPwd(passLen, usableChars);
        cout << correctPassword << endl;
        exit(EXIT_SUCCESS);
    }

    //Just to verify we have the correct length
    //Mostly for helping to idiot-proof it in case the user uses both -L and -p
    passLen = correctPassword.length();

    if (verbose)
        verbosePrint();

    cout << "Hit ENTER and the computer will attempt to guess the " << passLen << " character password " << correctPassword << endl;
    scanf("%c", &input);

    //TODO: begin guessing
}
