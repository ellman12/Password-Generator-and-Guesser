/*Programmer: Elliott DuCharme
* Purpose: None really. Made for gaining C++ experience and command line argument (flag) experience.
* Function: Computer tries to guess a "password" (just random/user-specified characters).
* Required extra files: PGG.hpp & Gen&Guess.hpp
* Compile: g++ -o "PGG" PGG.cpp
* Run: PGG <flags>
* Comments: It's quite satisfying watching the output.
* Obviously, this will probably strain your CPU. Please keep this in mind.
* Also, if you allow it to store guesses and the length is over like 7 characters, it will eat up memory, and possibly crash. It can easily reach hundreds of thousands of guesses.
* Storing guesses is best used for short passwords (probably like <6 characters), because there is a lot of repetition.
* When there are more possible characters and a longer string, there is more variety and thus less repetition.
* Lastly, I recommend using the -v (verbose) flag every time you run this thing. Nice to be able to double check to see what the program is about to do.
* Known issue: the Duration section's printing/formatting (specifically with the tabs) can be quite funky. Not sure why ¯\_(ツ)_/¯ */
#include <fstream>
#include "Gen&Guess.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser (PGG) is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc; i++) //Add args to vector
        args.push_back(argv[i]);
    args.erase(args.begin()); //Remove the useless first arg (name of the executable)

    for (int i = 0; i < argc; i++) //First determine if verbose or if --help was specified
    {
        if (args[i] == "-v")
        {
            verbose = true;
            printline(54);
        }
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
        {
            storePwds = false;
            useSeriesGuess = false;
        }

        else if (args[i] == "--series")
        {
            storePwds = false;
            useSeriesGuess = true;
            useIncrementGuess = false;
        }

        else if (args[i] == "--increment")
        {
            storePwds = false;
            useSeriesGuess = false;
            useIncrementGuess = true;
        }

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

        else if (((args[i][0] == '-') && (args[i][1] == 'O') && (args[i][2] != '\0')))
        {
            sendToFile = true;

            fileName.resize(args[i].length() - 2); //Use this later

            for (int j = 2; j < args[i].length(); j++)
                fileName[j - 2] = args[i][j];
            fileName += ".txt";
        }

        else if (args[i] == "--noenter")
        {
            noEnter = true;
        }

        else if (args[i] == "--noprint")
        {
            noPrint = true;
        }

        else if ((!args[i].empty()) && !verbose) //This somehow works
        {
            help();
            cout << "Unknown flag \"" << args[i] << "\"" << endl;
            exit(EXIT_FAILURE);
        }
    }

    //Used to fix crash if "--series" specified but none of these flags are.
    if (!usingDigits && !usingLower && !usingUpper && !usingSpecialChars && !customPwd)
    {
        cout << "Please specify either your own password you want PGG to guess with the -p flag,\nor specify at least one of these flags to have PGG automatically create a random password: -d -l -u -s." << endl;
        exit(EXIT_FAILURE);
    }

    usableChars = usableCharsInit();

    if (timeSeed == true)
        std::srand(time(0));

    if (passLen <= 0 && customPwd == false)
    {
        passLen = genRandNum(1, maxLength);
        if (verbose)
            cout << "No user-specified password length. Generating rand length of: " << passLen << endl;
    }

    if (customPwd == false)
    {
        correctPassword = genPwd(passLen);
        if (verbose)
            cout << "No user-specified password. Generating random one: " << correctPassword << endl;
    }

    //Just to verify we have the correct length
    //Mostly for helping to idiot-proof it in case the user uses both -L and -p
    passLen = correctPassword.length();

    if (verbose)
        verbosePrint();

    if (noEnter == false)
    {
        cout << "Hit ENTER and the computer will attempt to guess the " << passLen << " character password " << correctPassword;
        if (useSeriesGuess)
            cout << " using the series method";
        else if (useIncrementGuess)
            cout << " using the incrementing method";

        cout << endl;
        char input;
        scanf("%c", &input);
    }

    guessPwd();
}
