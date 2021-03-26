#include <iostream>
#include <vector>
#include <string>
#include <chrono> //Measuring time to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
using namespace std;

//The way the 3 seed args should work is that the one entered last will be used over any others. E.g, -s1234 --time --noseed. --noseed would be picked.
bool noSeed = false;
bool timeSeed = true;
bool customSeed = false;

bool usingDigits = false;
bool usingLower = false;
bool usingUpper = false;
bool usingSpecialChars = false;

bool verbose = false;
bool nostore = false;
bool customPwd = false;
bool showChars = false;

int totalAttempts = 0;  //Total attempts without counting duplicates
int actualAttempts = 0; //Total with duplicates counted

string password;
string seedString;
unsigned long long seedULL = 0;

vector<char> usableChars; //The chars that could be in the password

//If user specifies -v, print out stuff so they know what's happening under the hood
void verbosePrint()
{
    if (customPwd == true)
        cout << "The password you entered is: " << password << endl;

    if (noSeed == true)
        cout << "The default srand() seed will be used" << endl;

    if (timeSeed == true)
        cout << "time(0) [" << time(0) << "] is the seed" << endl;

    if (customSeed == true)
        cout << "The seed string you entered is: " << seedString << "\nConverted to an unsigned long long: " << seedULL << "\n";

    if (usingDigits == true)
        printf("Using digits\n");

    if (usingLower == true)
        printf("Using lower\n");

    if (usingUpper == true)
        printf("Using upper\n");

    if (usingSpecialChars == true)
        printf("Using special chars\n");

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
    printf("Password Generator and Guesser (PGG) Flags\n\n");

    printf("Control Password Generation\n");
    printf("-d  Use digits in the generated password\n");
    printf("-l  Use lowercase a-z in the generated password\n");
    printf("-u  Use uppercase A-Z in the generated password\n");
    printf("-s  Use special characters in the generated password\n");
    printf("-p  Input your own password after the -p. Causes d, l, u, and s to be set automatically\n\n");

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

    case '\\':
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

//TODO
// string generatePassword()
// {}

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
        usableChars.push_back('\\');
        usableChars.push_back('|');
        usableChars.push_back('<');
        usableChars.push_back('>');
        usableChars.push_back(',');
        usableChars.push_back('.');
        usableChars.push_back('"');
    }
}

void guessPwdWithStoring()
{
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    //TODO: password generation

    auto stop = high_resolution_clock::now();

    cout << "Duration:" << endl;
    auto durationNano = duration_cast<nanoseconds>(stop - start);
    cout << "Nanoseconds: " << durationNano.count() << endl;

    auto durationMicro = duration_cast<microseconds>(stop - start);
    cout << "Microseconds: " << durationMicro.count() << endl;

    auto durationMilli = duration_cast<milliseconds>(stop - start);
    cout << "Milliseconds: " << durationMilli.count() << endl;

    auto durationSec = duration_cast<seconds>(stop - start);
    cout << "Seconds: " << durationSec.count() << endl;

    auto durationMin = duration_cast<minutes>(stop - start);
    cout << "Minutes: " << durationMin.count() << endl;

    auto durationHour = duration_cast<hours>(stop - start);
    cout << "Hours: " << durationHour.count() << endl;
}

void guessPwdWithoutStoring()
{
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    //TODO: password generation

    auto stop = high_resolution_clock::now();

    cout << "Duration:" << endl;
    auto durationNano = duration_cast<nanoseconds>(stop - start);
    cout << "Nanoseconds: " << durationNano.count() << endl;

    auto durationMicro = duration_cast<microseconds>(stop - start);
    cout << "Microseconds: " << durationMicro.count() << endl;

    auto durationMilli = duration_cast<milliseconds>(stop - start);
    cout << "Milliseconds: " << durationMilli.count() << endl;

    auto durationSec = duration_cast<seconds>(stop - start);
    cout << "Seconds: " << durationSec.count() << endl;

    auto durationMin = duration_cast<minutes>(stop - start);
    cout << "Minutes: " << durationMin.count() << endl;

    auto durationHour = duration_cast<hours>(stop - start);
    cout << "Hours: " << durationHour.count() << endl;
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
    vector<string> args; //Cmd line args

    for (int i = 0; i < argc; i++) //Add to vector for ease of use
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

        else if (args[i] == "--nostore")
            nostore = true;

        else if (args[i] == "--showchars")
            showChars = true;

        else if (args[i] == "--noseed")
        {
            noSeed = true;
            timeSeed = false;
            customSeed = false;
        }

        else if (args[i] == "--time")
        {
            srand(time(0));
            timeSeed = true;
            noSeed = false;
            customSeed = false;
        }

        else if ((args[i][0] == '-') && (args[i][1] == 'S') && (args[i][2] != '\0'))
        {
            customSeed = true;
            noSeed = false;
            timeSeed = false;

            seedString.resize(args[i].length() - 2); //Make large enough to store the number (-2 because of -S)

            for (int j = 2; j < args[i].length(); j++) //Strip the -S and store the rest
                seedString[j - 2] = args[i][j];

            seedULL = stoull(seedString); //Make number and apply the custom seed
            std::srand(seedULL);
        }
    }

    if (usingDigits == false && usingLower == false && usingUpper == false && usingSpecialChars == false)
    {
        cout << "-d -l -u and -" << endl;
    }

        usableCharsInit();

    if (verbose)
        verbosePrint();

    printf("Hit ENTER to begin guessing\n");
    scanf("%c", &input);

    if (nostore)
        guessPwdWithoutStoring();
    else
        guessPwdWithStoring();
}