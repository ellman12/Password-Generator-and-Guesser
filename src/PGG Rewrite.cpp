#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Gen&Guess.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    char input; //Used for the "press ENTER" thing later on

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
        if ((args[i][0] == '-') && (args[i][1] == 'p') && (args[i][2] != '\0'))
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
            storePwds = true;

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

        else if ((!args[i].empty()) && !verbose) //This somehow works
        {
            help();
            cout << "Unknown flag \"" << args[i] << "\" at index " << i << endl;
            exit(EXIT_FAILURE);
        }
    }

    usableChars = usableCharsInit();

    if (passLen <= 0 && customPwd == false)
    {
        passLen = genRandNum(1, maxLength);
        cout << "No user-specified password length. Generating rand length of: " << passLen << endl;
    }

    if (customPwd == false && justGenerating == false)
    {
        correctPassword = genPwd(passLen);
        cout << "No user-specified password. Generating random one: " << correctPassword << endl;
    }

    if (justGenerating == true && customPwd == false)
    {
        printf("Here is your newly generated password:\n");
        correctPassword = genPwd(passLen);
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

    guessPwd();
}
