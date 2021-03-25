//Program used for generating random passwords, and then testing how long it takes for the PC to guess said password.
//Programmer: Elliott DuCharme
//Environment: VSCode on Windows with the g++ compiler
//This is a program where the computer tries to guess a "password(?)", and records how many attempts it took.
//It can also use a vector to track duplicate guesses so it doesn't re-guess something it already guessed. This can be disabled.
//WARNING: fairly intensive on your CPU!
#include <iostream>
#include <vector>
#include <algorithm> //Used for finding guessed passwords in the vector
#include <time.h>
using namespace std;

//Sources:
//http://www.cplusplus.com/forum/general/130902/
//https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c

int genRandNum(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

//Generates "random(?)" passwords. User can control how it's generated. If any of the parameters (except for the last one) are -1, random value is used.
string generatePassword(int length, int useNumbers, int useLowerCase, int useUpperCase, int useSpecialChars, int printUsableChars)
{
    if (useNumbers == false && useLowerCase == false && useUpperCase == false && useSpecialChars == false)
    {
        printf("generatePassword() ERROR. At least one of parameters 2, 3, 4, and/or 5 needs to be true :/\n");
        exit(EXIT_FAILURE);
    }

    if (length == -1)
        printf("Length specified as -1. Generating random length of %d\n", length = rand());

    if (useNumbers == -1)
        printf("useNumbers specified as -1. Generating randomly if using or not (0 or 1): %d\n", useNumbers = rand() % 2);

    if (useLowerCase == -1)
        printf("useLowerCase specified as -1. Generating randomly if using or not (0 or 1): %d\n", useLowerCase = rand() % 2);

    if (useUpperCase == -1)
        printf("useUpperCase specified as -1. Generating randomly if using or not (0 or 1): %d\n", useUpperCase = rand() % 2);

    if (useSpecialChars == -1)
        printf("useSpecialChars specified as -1. Generating randomly if using or not (0 or 1): %d\n", useSpecialChars = rand() % 2);

    vector<char> usableChars; //What chars can be in the password. Use vector for ease of use.
    string password;

    if (useNumbers)
    {
        for (int i = 0; i < 10; i++)
            usableChars.push_back(i + '0');
    }

    if (useLowerCase)
    {
        for (int i = 0; i < 26; i++)
            usableChars.push_back('a' + i);
    }

    if (useUpperCase)
    {
        for (int i = 0; i < 26; i++)
            usableChars.push_back('A' + i);
    }

    if (useSpecialChars)
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
        usableChars.push_back('%');
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
        usableChars.push_back('\'');
        usableChars.push_back('"');
    }

    if (printUsableChars)
    {
        printf("Usable chars for the password: ");
        for (int i = 0; i < usableChars.size(); i++)
            std::cout << usableChars.at(i) << ' ';
    }

    for (int i = 0; i < length; i++) //Fill the password string with chars
        password += usableChars[rand() % usableChars.size()];

    return password;
}

//TODO:
//guesser function can be given the length or not
//enable/disable things like PC knowing password length, which bools are true, etc.
//make vector optional
//Make the vector less thing a whole different function or something. In Main have an if to determine which to call

//Computer tries to guess a password.
void guessPassword(string correctPassword, int length, int useNumbers, int useLowerCase, int useUpperCase, int useSpecialChars, int printUsableChars)
{
    vector<string> guessesdPasswords;
    string passwordGuess;
    int guessAttempts = 1;

    do
    {
        passwordGuess = generatePassword(length, useNumbers, useLowerCase, useUpperCase, useSpecialChars, printUsableChars);
        cout << "Guessing password: " << passwordGuess << "\t" << "Attempts: " << guessAttempts << "\t";

        if (find(guessesdPasswords.begin(), guessesdPasswords.end(), passwordGuess) != guessesdPasswords.end())
            cout << "\tPassword " << passwordGuess << " is already in the vector" << endl;
        else
        {
            guessesdPasswords.push_back(passwordGuess);
            guessAttempts++;
            printf("\n");
        }

    } while (passwordGuess != correctPassword);

    cout << "\nThe computer guessed the password " << passwordGuess << " after " << --guessAttempts << " attempts!\n" << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 7)
    {
        printf("Please enter these 7 command line args:\nint length, int useNumbers, int useLowerCase, int useUpperCase, int useSpecialChars, int printUsableChars, (optional) string yourOwnPassword (instead of the program creating its own)");
        return -1;
    }

    if (atoi(argv[2]))
        cout << "Using numbers" << endl;
    if (atoi(argv[3]))
        cout << "Using lower case" << endl;
    if (atoi(argv[4]))
        cout << "Using UPPER CASE" << endl;
    if (atoi(argv[5]))
        cout << "Using special chars" << endl;

    srand(time(0)); //Yes, I know rand is bad, especially for something like this.

    char input; //Just used for the hit enter thing
    int length = atoi(argv[1]);
    string password;

    if (argv[7] == NULL) //User can choose their own password. It's the last (and also optional) command line arg. If it's blank, generate random password.
        password = generatePassword(length, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6])); //Command line args make for easier testing
    else
        password = argv[7];

    cout << "\nPassword of length " << password.size() << " is: " << password << "\n\n";

    printf("Hit enter to begin the guessing\n>");
    scanf("%c", &input);

    guessPassword(password, length, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), false);
}