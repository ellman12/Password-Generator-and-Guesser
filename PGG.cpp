#include <iostream>
#include <vector>
#include <algorithm> //Used for finding guessed passwords in the vector
#include <string>
#include <chrono> //Measuring time to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
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

int totalAttempts = 1;  //Total attempts without counting duplicates (i.e., guessing a password more than once)
int actualAttempts = 1; //Total with duplicates counted

string password;
string seedString;
int length = 0;
int maxLength = 50; //User can change this
unsigned long long customSeed = 0;

vector<char> usableChars; //The chars that could be in the password

int genRandNum(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

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
        cout << "The custom password you entered is: " << password << endl;

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

void printline(const int LENGTH)
{
    for (int i = 0; i < LENGTH; i++)
        printf("-");
    printf("\n");
}

void help() //Shows the different flags, what they do, and how to use them
{
    const int LENGTH = 97;
    printline(LENGTH);
    printf("Password Generator and Guesser (PGG) Flags\n");
    printf("The order of these should not affect anything\n\n");

    printf("Control Password Generation\n");
    printf("-d  Use digits in the generated password\n");
    printf("-l  Use lowercase a-z in the generated password\n");
    printf("-u  Use uppercase A-Z in the generated password\n");
    printf("-s  Use special characters in the generated password\n");
    printf("-p  Input your own password after the -p. Causes d, l, u, and s to be set automatically\n");
    printf("-L  Force the generated password to be a certain length\n");
    printf("-M  If no length given, generate random length between 1 and M\n\n");

    printf("Control rand() Seed\n");
    printf("--noseed    Default srand value (same numbers generated every time)\n");
    printf("--time      Use time(0) as the seed (default if neither specified)\n");
    printf("-S<digits>  Custom seed value\n\n");

    printf("Control Password Guessing\n");
    printf("--store    Store guesses to avoid duplicating. This can also help make guessing faster (Default)\n");
    printf("--nostore  Don't store them. Can help avoid running out of memory if the password is long\n");

    printf("\nMisc\n");
    printf("-v\t(Verbose) Tells you what things happen under the hood and when\n");
    printf("--help\tShows this\n");
    printf("--showchars\tPrint out what chars a generated password could contain\n");
    printline(LENGTH);
    printf("\n");
}

bool isSpecialChar(char c, bool *usingSpecialChars)
{
    switch (c)
    {
    case '`':
        *usingSpecialChars = true;
        return true;

    case '~':
        *usingSpecialChars = true;
        return true;

    case '!':
        *usingSpecialChars = true;
        return true;

    case '@':
        *usingSpecialChars = true;
        return true;

    case '#':
        *usingSpecialChars = true;
        return true;

    case '$':
        *usingSpecialChars = true;
        return true;

    case '%':
        *usingSpecialChars = true;
        return true;

    case '^':
        *usingSpecialChars = true;
        return true;

    case '&':
        *usingSpecialChars = true;
        return true;

    case '*':
        *usingSpecialChars = true;
        return true;

    case '(':
        *usingSpecialChars = true;
        return true;

    case ')':
        *usingSpecialChars = true;
        return true;

    case '-':
        *usingSpecialChars = true;
        return true;

    case '_':
        *usingSpecialChars = true;
        return true;
    case '=':
        *usingSpecialChars = true;
        return true;

    case '+':
        *usingSpecialChars = true;
        return true;

    case '?':
        *usingSpecialChars = true;
        return true;

    case '[':
        *usingSpecialChars = true;
        return true;

    case ']':
        *usingSpecialChars = true;
        return true;

    case '{':
        *usingSpecialChars = true;
        return true;

    case '}':
        *usingSpecialChars = true;
        return true;

    case '/':
        *usingSpecialChars = true;
        return true;

    case '|':
        *usingSpecialChars = true;
        return true;

    case '<':
        *usingSpecialChars = true;
        return true;

    case '>':
        *usingSpecialChars = true;
        return true;

    case ',':
        *usingSpecialChars = true;
        return true;

    case '.':
        *usingSpecialChars = true;
        return true;

    case '"':
        *usingSpecialChars = true;
        return true;
    }

    return false;
}

//Initialize this thing. Original version had to redo this EVERY time a password needed to be generated. No need for that
void usableCharsInit()
{
    if (usingDigits == true)
    {
        for (int i = 0; i < 10; i++)
            usableChars.push_back(i + '0');
    }

    if (usingLower)
    {
        for (int i = 0; i < 26; i++)
            usableChars.push_back('a' + i);
    }

    if (usingUpper)
    {
        for (int i = 0; i < 26; i++)
            usableChars.push_back('A' + i);
    }

    if (usingSpecialChars)
    {
        //I couldn't think of a better way to do this :(
        usableChars.push_back('`');
        usableChars.push_back('~');
        usableChars.push_back('!');
        usableChars.push_back('@');
        usableChars.push_back('#');
        usableChars.push_back('$');
        usableChars.push_back('%');
        usableChars.push_back('^');
        usableChars.push_back('&');
        usableChars.push_back('*');
        usableChars.push_back('(');
        usableChars.push_back(')');
        usableChars.push_back('-');
        usableChars.push_back('_');
        usableChars.push_back('=');
        usableChars.push_back('+');
        usableChars.push_back('?');
        usableChars.push_back('[');
        usableChars.push_back(']');
        usableChars.push_back('{');
        usableChars.push_back('}');
        usableChars.push_back('/');
        usableChars.push_back('|');
        usableChars.push_back('<');
        usableChars.push_back('>');
        usableChars.push_back(',');
        usableChars.push_back('.');
        usableChars.push_back('"');
    }
}

string generatePassword()
{
    string newPassword = "";
    newPassword.resize(length);

    for (int i = 0; i < length; i++) //Fill the new password string with random chars
    {
        newPassword[i] = usableChars[rand() % usableChars.size()];
    }
    return newPassword;
}

void guessPwdWithStoring(string correctPassword)
{
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    vector<string> guessesdPasswords;
    string guess;

    while (guess != correctPassword)
    {
        guess = generatePassword();
        cout << "Guess: " << guess << '\t'
             << "Total Attempts: " << totalAttempts << '\t'
             << "Without Dupes: " << actualAttempts << '\t';

        if (find(guessesdPasswords.begin(), guessesdPasswords.end(), guess) != guessesdPasswords.end())
        {
            printf("Already in the vector");
            totalAttempts++;
        }
        else
        {
            guessesdPasswords.push_back(guess);
            totalAttempts++;
            actualAttempts++;
        }
        printf("\n");
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(97);
    cout << password << " was guessed after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
    printline(97);

    printline(9);
    cout << "Duration:" << endl;
    printline(9);

    auto durationNano = duration_cast<nanoseconds>(stop - start);
    cout << (double)durationNano.count() << "\tNanoseconds" << endl;

    double durationMicro = durationNano.count() / 1000;
    cout << durationMicro << "\tMicroseconds" << endl;

    double durationMilli = durationMicro / 1000;
    cout << durationMilli << "\tMilliseconds" << endl;

    double durationSec = durationMilli / 1000;
    cout << durationSec << "\tSeconds" << endl;

    double durationMin = durationSec / 60;
    cout << durationMin << "\tMinutes" << endl;

    double durationHour = durationSec / 60;
    cout << durationHour << "\tHours" << endl;
}

void guessPwdWithoutStoring(string correctPassword)
{
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    string guess;

    while (guess != correctPassword)
    {
        guess = generatePassword();
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << '\n';
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(69);
    cout << password << " was guessed after " << --totalAttempts << " attempts\n";
    printline(69);

    printline(9);
    cout << "Duration:" << endl;
    printline(9);

    auto durationNano = duration_cast<nanoseconds>(stop - start);
    cout << (double)durationNano.count() << "\tNanoseconds" << endl;

    double durationMicro = durationNano.count() / 1000;
    cout << durationMicro << "\tMicroseconds" << endl;

    double durationMilli = durationMicro / 1000;
    cout << durationMilli << "\tMilliseconds" << endl;

    double durationSec = durationMilli / 1000;
    cout << durationSec << "\tSeconds" << endl;

    double durationMin = durationSec / 60;
    cout << durationMin << "\tMinutes" << endl;

    double durationHour = durationSec / 60;
    cout << durationHour << "\tHours" << endl;
}

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
        password = generatePassword();
    }

    usableCharsInit();

    if (verbose)
        verbosePrint();

    cout << "Hit ENTER and the computer will attempt to guess the " << password.length() << " character password " << password << endl;
    scanf("%c", &input);

    if (nostore)
        guessPwdWithoutStoring(password);
    else
        guessPwdWithStoring(password);
}