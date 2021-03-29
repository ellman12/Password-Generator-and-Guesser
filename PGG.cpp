#include <iostream>
#include <vector>
#include <algorithm> //Used for finding guessed passwords in the vector
#include <string>
#include "PGG.hpp"
using namespace std;

// string password;?
?
?
?
?
?
?

string seedString;
int length = 0;
int maxLength = 50; //User can change this
unsigned long long customSeed = 0;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    char input;          //Used for the "press ENTER" thing later on
    vector<string> args; //Store the cmd line args in a vector for ease of use

    for (int i = 0; i < argc; i++) //Add to vector
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
            password.resize(args[i].length() - 2); //Make large enough to store user's password (-2 because of -p)
            length = password.length();
            customPwd = true;

            for (int j = 2; j < args[i].length(); j++) //Strip the -p and store the rest in password
                password[j - 2] = args[i][j];

            for (int j = 0; j < password.length(); j++) //Analyze user's password and determine what kind of chars it contains
            {
                if ((usingDigits == false) && (isdigit(password[j])))
                    usingDigits = true;

                if ((usingLower == false) && (islower(password[j])))
                    usingLower = true;

                if ((usingUpper == false) && (isupper(password[j])))
                    usingUpper = true;

                if ((usingSpecialChars == false) && (isSpecialChar(password[j], &usingSpecialChars)))
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

        else if ((args[i][0] == '-') && (args[i][1] == 'L'))
        {
            string tmp;
            tmp.resize(args[i].length() - 2);
            for (int j = 2; j < args[i].length(); j++)
                tmp[j - 2] = args[i][j];

            length = stoi(tmp);

            if (verbose)
                cout << "Length specified by you is: " << length << endl;
        }

        else if ((args[i][0] == '-') && (args[i][1] == 'M'))
        {
            string tmp;
            tmp.resize(args[i].length() - 2);
            for (int j = 2; j < args[i].length(); j++)
                tmp[j - 2] = args[i][j];

            password = stoi(tmp);

            if (verbose)
                cout << "Max password length specified by you is: " << maxLength << endl;
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

    usableCharsInit();

    if (length <= 0) //If user doesn't specify length
    {
        length = genRandNum(1, maxLength);
        if (verbose)
            cout << "No length specified as arg. Generating rand length of: " << length << endl;
    }

    if (customPwd == false)
    {
        if (verbose)
            printf("No password arg detected. Generating password\n");
        password.resize(length); //Resize to store how many chars we want
        password = generatePassword(length, usableChars);
    }

    if (verbose)
        verbosePrint();

    cout << "Hit ENTER and the computer will attempt to guess the " << password.length() << " character password " << password << endl;
    scanf("%c", &input);

    if (nostore)
        guessPwdWithoutStoring(password);
    else
        guessPwdWithStoring(password);
}