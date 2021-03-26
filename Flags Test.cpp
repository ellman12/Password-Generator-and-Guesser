#include <iostream>
#include <vector>
#include <string>
#include <chrono> //Measuring time to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
using namespace std;

bool customPwd = false;
bool usingDigits = false;
bool usingLower = false;
bool usingUpper = false;
bool usingSpecialChars = false;
bool verbose = false;
bool nostore = false;
int totalAttempts = 0;  //Total attempts without counting duplicates
int actualAttempts = 0; //Total with duplicates counted
string password;

//If user specifies -v, print out stuff so they know what's happening under the hood
void verbosePrint()
{
    if (customPwd == true)
        cout << "The password you entered is: " << password << endl;

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
}

void printline(int length)
{
    for (int i = 0; i < length; i++)
        printf("-");
    printf("\n");
}

void help()
{
    const int length = 96;
    printline(length);
    printf("Password Generator and Guesser (PGG) Flags\n");
    printline(length);
    printf("\n");
    printf("Control Password Generation\n");
    printf("-p\tInput your own (p)assword after the -p. Causes d, l, u, and s to not have any effect\n");
    printf("-d\tUse (d)igits in the generated password\n");
    printf("-l\tUse (l)owercase a-z in the generated password\n");
    printf("-u\tUse (u)ppercase A-Z in the generated password\n");
    printf("-s\tUse (s)pecial characters in the generated password\n\n");
    printf("Control Password Guessing\n");
    printf("--store    Store guesses to avoid duplicating. This can also help make guessing faster (Default)\n");
    printf("--nostore  Don't store them. Can help avoid running out of memory if the password is long\n");
    printf("\nMisc\n");
    printf("-v\t(Verbose) Tell you what and when things happen under the hood\n");
    printf("--help\tShows this\n");
    printline(length);
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

// string generatePassword()
// {
// }

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
        printf("\nPassword Generator and Guesser is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    char input;                 //Used for the "press ENTER" thing later on
    vector<string> args;        //Cmd line args
    vector<string> usableChars; //The chars that could be in the password

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

        if ((customPwd == false) && (args[i] == "-d"))
            usingDigits = true;

        else if ((customPwd == false) && (args[i] == "-l"))
            usingLower = true;

        else if ((customPwd == false) && (args[i] == "-u"))
            usingUpper = true;

        else if ((customPwd == false) && (args[i] == "-s"))
            usingSpecialChars = true;

        else if (args[i] == "--nostore")
            nostore = true;
    }

    if (verbose)
        verbosePrint();

    printf("Hit ENTER to begin guessing\n");
    scanf("%c", &input);

    if (nostore)
        guessPwdWithoutStoring();
    else
        guessPwdWithStoring();
}