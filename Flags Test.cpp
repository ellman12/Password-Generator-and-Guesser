#include <iostream>
#include <vector>
#include <string>
using namespace std;

void help()
{
    printf("----------------------------------------------------\n");
    printf("Password Generator and Guesser\n");
    printf("----------------------------------------------------\n");
    printf("Password Generation Flags\n");
    printf("----------------------------------------------------\n");
    printf("-p\tInput your own (p)assword after the -p. Causes d, l, u, and s to not have any effect.\n");
    printf("-d\tUse (d)igits in the generated password\n");
    printf("-l\tUse (l)owercase a-z in the generated password\n");
    printf("-u\tUse (u)ppercase A-Z in the generated password\n");
    printf("-s\tUse (s)pecial characters in the generated password\n");
    printf("-v\t(Verbose) Tell you which of these are toggled (if any)\n");
    printf("----------------------------------------------------\n");
    printf("--help\tShows this\n");
    printf("----------------------------------------------------\n");
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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        exit(EXIT_SUCCESS);
    }

    bool customPwd = false;
    bool usingDigits = false;
    bool usingLower = false;
    bool usingUpper = false;
    bool usingSpecialChars = false;
    bool verbose = false;

    string password;
    vector<string> args;
    vector<string> usableChars;

    for (int i = 0; i < argc; i++) //Add to vector for ease of use
        args.push_back(argv[i]);

    for (int i = 0; i < argc; i++) //First determine if verbose
    {
        if (args[i] == "-v")
        {
            verbose = true;
            break;
        }
    }

    for (int i = 0; i < argc; i++) //Apply command line args
    {
        if (args[i] == "--help")
        {
            help();
            exit(EXIT_SUCCESS);
        }

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

        if ((customPwd == false) && (args[i] == "-l"))
        {
            usingLower = true;
            if (verbose)
                printf("Using lower case\n");
        }

        if ((customPwd == false) && (args[i] == "-u"))
        {
            usingUpper = true;
            if (verbose)
                printf("Using UPPER CASE\n");
        }

        if ((customPwd == false) && (args[i] == "-s"))
        {
            usingSpecialChars = true;
            if (verbose)
                printf("Using special characters\n");
        }
    }
}