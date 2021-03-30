#ifndef GTHREAD_HPP_
#define GTHREAD_HPP_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <chrono> //Measuring time taken to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
#include "PGG Rewrite.hpp"
using namespace std;

//Password guesser thread. If there are multiple instances, they will work together with their static members to guess passwords.
// class gthread
// {
// public:
// static int totalAttempts;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
// static int actualAttempts; //Total with duplicates counted
// static int passLen;
// static string correctPassword;
// static bool storeGuesses;
// static vector<string> guesses;
// static vector<char> usableChars; //The chars that could be in the password

// gthread();
// gthread(int passLen, string correctPassword, bool storeGuesses);
// string genPwd(int len);
// void guessPwd(bool storePasswords);
// void guessPwdWoutStore(int len, string correctPassword); //TODO: Computer can be given length or not. If len <= 0 figure out on its own
// void guessPwdWStore(int len, string correctPassword);
// void usableCharsInit(bool usingDigits, bool usingLower, bool usingUpper, bool usingSpecialChars);
// };

//I haven't the slightest idea why these are necessary here but it gets rid of "undefined reference" errors for some reason ¯\_(ツ)_/¯
// int gthread::totalAttempts = 1;
// int gthread::actualAttempts = 1;
// int gthread::passLen;
// string gthread::correctPassword = correctPassword;
// bool gthread::storeGuesses = storeGuesses;
// vector<string> gthread::guesses;
// vector<char> gthread::usableChars;
// static void guessPwd(bool storePasswords);

//Constructors
// gthread::gthread()
// {
//     thread thr(&gthread::guessPwd, true);
// }

// gthread::gthread(int passLen, string correctPassword, bool storeGuesses)
// {
//     thread thr(&gthread::guessPwd, true);
//     gthread::passLen = passLen;
//     gthread::correctPassword = correctPassword;
//     gthread::storeGuesses = storeGuesses;
//     printf("gthread created\n");
// }

static int totalAttempts = 1;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
static int actualAttempts = 1; //Total with duplicates counted
int threadWinner = 0;          //Which thread gets it first
static int passLen;
static string correctPassword;
static bool storeGuesses;
static bool notGuessed = true;
static bool printOnce = true; //Used for printing duration
static vector<string> guesses;
static vector<char> usableChars; //The chars that could be in the password

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
void usableCharsInit(bool usingDigits, bool usingLower, bool usingUpper, bool usingSpecialChars, vector<char> &usableChars)
{
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
}

void guessPwdWStore(int len, string correctPassword, vector<char> usableChars)
{
    printf("begin guess\n");
    using namespace chrono;
    string guess;
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now(); //Start the timer

    while (guess != correctPassword)
    {
        guess = genPwd(len, usableChars);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts << '\t' << "Without Dupes: " << actualAttempts << '\t';

        if (find(guesses.begin(), guesses.end(), guess) != guesses.end()) //Check for duplicates
        {
            printf("Already in the vector");
            totalAttempts++;
        }
        else
        {
            guesses.push_back(guess);
            totalAttempts++;
            actualAttempts++;
        }
        printf("\n");
    }

    auto stop = high_resolution_clock::now(); //Stop the timer

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

void guessPwdWoutStore(int threadID, int len, string correctPassword, vector<char> usableChars)
{
    using namespace chrono;
    string guess = genPwd(len, usableChars);

    auto start = high_resolution_clock::now();

    while (notGuessed == true)
    {
        guess = genPwd(len, usableChars);
        cout << "Thread #" << threadID << "\tGuess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << "\tthreadWinner: #" << threadWinner << '\n';

        if (guess == correctPassword)
        {
            notGuessed = false;
            threadWinner = threadID;
            break;
        }
    }

    auto stop = high_resolution_clock::now();

    threadWinner = threadID;

    ::correctPassword = correctPassword;

    if (printOnce == true)
    {
        printOnce = false;
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
}

// void guessPwd(bool storePasswords, string correctPassword)
// {
//     int totalAttempts;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
//     int actualAttempts; //Total with duplicates counted
//     int passLen;
//     // string correctPassword;
//     // bool storeGuesses;
//     vector<string> guesses;
//     vector<char> usableChars; //The chars that could be in the password

//     if (storePasswords)
//         guessPwdWStore(passLen, correctPassword, usableChars);
//     else
//         guessPwdWoutStore(passLen, correctPassword, usableChars);
// }

#endif