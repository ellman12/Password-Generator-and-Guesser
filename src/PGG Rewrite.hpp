#ifndef PGG_REWRITE_HPP_
#define PGG_REWRITE_HPP_

//Misc funcs for main file
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono> //Measuring time taken to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
using namespace std;

//The way the 3 seed args should work is that the one entered last will be used over any others. E.g, -s1234 --time --noseed. --noseed would be picked.
//Configuration bools
bool noSeed = false;
bool timeSeed = true;
bool usingCustomSeed = false;

bool usingDigits = false;
bool usingLower = false;
bool usingUpper = false;
bool usingSpecialChars = false;

bool verbose = false;
bool storePwds = false;
bool storeGuesses;
bool customPwd = false;
bool showChars = false;
bool justGenerating = false; //If the user just wants to generate a password

string seedString;
unsigned long long customSeed = 0;
vector<string> args; //Store the cmd line args in a vector for ease of use

int passLen = 0;
int maxLength = 50;     //User can change this. It's how long an auto-generated password can be
int totalAttempts = 1;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
int actualAttempts = 1; //Total with duplicates counted
string guess;
string correctPassword;
vector<string> guesses;
vector<char> usableChars; //The chars that could be in the password

int genRandNum(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

//Print a big divider line
void printline(const int LENGTH)
{
    for (int i = 0; i < LENGTH; i++)
        printf("-");
    printf("\n");
}

void help() //Shows the different flags, what they do, and how to use them
{
    const int LENGTH = 111;
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
    printf("--help\t\tShows this\n");
    printf("--genpwd\tJust generates a password; no guessing, etc. Use normal flags like -d, -L, etc. for generation\n");
    printf("-v\t\t(Verbose) Tells you what things happen under the hood and when\n");
    printf("--showchars\tPrint out what chars a generated password could contain\n");
    printline(LENGTH);
    printf("\n");
}

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
        cout << "The custom seed you entered is: " << seedString << endl;

    printf("\nOther:\n");
    if (storePwds == true)
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

string genPwd(int len)
{
    string newPassword = "";
    newPassword.resize(len);

    for (int i = 0; i < len; i++) //Fill the new password string with random chars
    {
        newPassword[i] = usableChars[rand() % usableChars.size()];
    }
    return newPassword;
}

string genPwd(int len, vector<char> usableChars)
{
    string newPassword = "";
    newPassword.resize(len);

    for (int i = 0; i < len; i++) //Fill the new password string with random chars
    {
        newPassword[i] = usableChars[rand() % usableChars.size()];
    }
    return newPassword;
}

//Determine which chars a password could contain
vector<char> usableCharsInit()
{
    vector<char> usableChars;

    if (usingDigits)
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

    return usableChars;
}

//Used for -p flag to determine if the user's specified password at an index has any special chars
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

#endif