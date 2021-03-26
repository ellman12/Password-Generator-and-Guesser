#include <iostream>
#include <vector>
#include <string>
using namespace std;

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
}

void guessPwdWithoutStoring()
{
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        printf("\nPassword Generator and Guesser is going to need at least 1 parameter\n\n");
        exit(EXIT_FAILURE);
    }

    bool customPwd = false;
    bool usingDigits = false;
    bool usingLower = false;
    bool usingUpper = false;
    bool usingSpecialChars = false;
    bool verbose = false;
    bool nostore = false;
    char input;
    string password;
    vector<string> args;
    vector<string> usableChars;

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
                {
                    usingDigits = true;
                    if (verbose)
                        printf("Using digits\n");
                }

                if ((usingLower == false) && (islower(password[j])))
                {
                    usingLower = true;
                    if (verbose)
                        printf("Using lower case\n");
                }

                if ((usingUpper == false) && (isupper(password[j])))
                {
                    usingUpper = true;
                    if (verbose)
                        printf("Using UPPER CASE\n");
                }

                if ((usingSpecialChars == false) && (isSpecialChar(password[j], &usingSpecialChars)))
                {
                    usingSpecialChars = true;
                    if (verbose)
                        printf("Using special characters\n");
                }
            }
        }

        if ((customPwd == false) && (args[i] == "-d"))
        {
            usingDigits = true;
            if (verbose)
                printf("Using digits\n");
        }

        else if ((customPwd == false) && (args[i] == "-l"))
        {
            usingLower = true;
            if (verbose)
                printf("Using lower case\n");
        }

        else if ((customPwd == false) && (args[i] == "-u"))
        {
            usingUpper = true;
            if (verbose)
                printf("Using UPPER CASE\n");
        }

        else if ((customPwd == false) && (args[i] == "-s"))
        {
            usingSpecialChars = true;
            if (verbose)
                printf("Using special characters\n");
        }

        else if (args[i] == "--nostore")
        {
            nostore = true;
            if (verbose)
                printf("Guesses will not be stored\n");
        }
    }

    printf("Hit ENTER to begin guessing\n");
    scanf("%c", &input);

    if (nostore)
        guessPwdWithoutStoring();
    else
        guessPwdWithStoring();
}