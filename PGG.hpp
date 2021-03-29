#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono> //Measuring time taken to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
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

class gthread //Guesser thread
{
public:
    int ID;
    thread gthr;
    static int totalAttempts;        //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
    int actualAttempts;              //Total with duplicates counted
    static vector<char> usableChars; //The chars that could be in the password
    static int numThreads;
    static int passLen;
    static string correctPassword;
    static vector<string> guesses;
    static vector<gthread> threads;

    gthread();
    gthread(int passLen, string correctPassword);
    string generatePassword(int len);
    void guessPwdWithoutStoring(int len, string correctPassword);
    void guessPwdWithStoring(int len, string correctPassword);
};

gthread::gthread()
{
    totalAttempts = 1;
    actualAttempts = 1;
}

void gthread::guessPwdWithStoring(int len, string correctPassword)
{
    using namespace chrono;

    auto start = high_resolution_clock::now();

    vector<string> guessesdPasswords;
    string guess;

    while (guess != correctPassword)
    {
        guess = generatePassword(len, usableChars);
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
    cout << guess << " was guessed after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
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

void gthread::guessPwdWithoutStoring(int len, string correctPassword)
{
    using namespace chrono;

    auto start = high_resolution_clock::now();

    string guess;

    while (guess != correctPassword)
    {
        guess = generatePassword(len);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << '\n';
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(69);
    cout << guess << " was guessed after " << --totalAttempts << " attempts\n";
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

int genRandNum(int min, int max)
{
    return rand() % (max + 1 - min) + min;
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

//Used for -p flag
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

void usableCharsInit()
{
    if (usingDigits == true)
    {
        for (int i = 0; i < 10; i++)
            gthread::usableChars.push_back(i + '0');
    }

    if (usingLower)
    {
        for (int i = 0; i < 26; i++)
            gthread::usableChars.push_back('a' + i);
    }

    if (usingUpper)
    {
        for (int i = 0; i < 26; i++)
            gthread::usableChars.push_back('A' + i);
    }

    if (usingSpecialChars)
    {
        //I couldn't think of a better way to do this :(
        gthread::usableChars.push_back('`');
        gthread::usableChars.push_back('~');
        gthread::usableChars.push_back('!');
        gthread::usableChars.push_back('@');
        gthread::usableChars.push_back('#');
        gthread::usableChars.push_back('$');
        gthread::usableChars.push_back('%');
        gthread::usableChars.push_back('^');
        gthread::usableChars.push_back('&');
        gthread::usableChars.push_back('*');
        gthread::usableChars.push_back('(');
        gthread::usableChars.push_back(')');
        gthread::usableChars.push_back('-');
        gthread::usableChars.push_back('_');
        gthread::usableChars.push_back('=');
        gthread::usableChars.push_back('+');
        gthread::usableChars.push_back('?');
        gthread::usableChars.push_back('[');
        gthread::usableChars.push_back(']');
        gthread::usableChars.push_back('{');
        gthread::usableChars.push_back('}');
        gthread::usableChars.push_back('/');
        gthread::usableChars.push_back('|');
        gthread::usableChars.push_back('<');
        gthread::usableChars.push_back('>');
        gthread::usableChars.push_back(',');
        gthread::usableChars.push_back('.');
        gthread::usableChars.push_back('"');
    }
}