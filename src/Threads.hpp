//Stuff used for the guesser threads
#ifndef THREADS_HPP_
#define THREADS_HPP_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <chrono> //Measuring time taken to guess passwords: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
#include "PGG Rewrite.hpp"
using namespace std;

//There all need to be shared between threads
int passLen = 0;
int totalAttempts = 1;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
int actualAttempts = 1; //Total with duplicates counted
int threadWinner = 0;   //Which thread gets it
string guess;
string correctPassword;
bool storeGuesses;
bool notGuessed = true;
// bool printOnce = true; //Used for printing duration
vector<string> guesses;
vector<char> usableChars; //The chars that could be in the password

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
vector<char> usableCharsInit(bool usingDigits, bool usingLower, bool usingUpper, bool usingSpecialChars)
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

void guessPwdWStore(int threadID, int len, string correctPassword, vector<char> usableChars)
{
    using namespace chrono;
    static bool printOnce = true; //Used for printing duration
    guess = genPwd(len, usableChars);
    correctPassword.resize(len);

    auto start = high_resolution_clock::now(); //Start the timer

    while (notGuessed == true)
    {
        guess = genPwd(len, usableChars);
        cout << "Thread #" << threadID << "\tGuess: " << guess << '\t' << "Total Attempts: " << totalAttempts << '\t' << "Without Dupes: " << actualAttempts << "\tthreadWinner: #" << threadWinner << " ";

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

        if (guess == correctPassword)
        {
            notGuessed = false;
            threadWinner = threadID;
            break;
        }
        printf("\n");
    }

    auto stop = high_resolution_clock::now(); //Stop the timer
    threadWinner = threadID;
    ::correctPassword = correctPassword;

    printf("\n");
    printline(120);
    cout << "The password " << guess << " was guessed by thread #" << threadWinner << " after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
    printline(120);

    if (printOnce == true)
    {
        printOnce = false;
        printline(27);
        cout << "\t Duration" << endl;
        printline(27);

        auto durationNano = duration_cast<nanoseconds>(stop - start);
        cout << (double)durationNano.count() << "\tNanoseconds" << endl;

        double durationMicro = durationNano.count() / 1000;
        cout << durationMicro << "\t\tMicroseconds" << endl;

        double durationMilli = durationMicro / 1000;
        cout << durationMilli << "\t\tMilliseconds" << endl;

        double durationSec = durationMilli / 1000;
        cout << durationSec << "\tSeconds" << endl;

        double durationMin = durationSec / 60;
        cout << durationMin << "\tMinutes" << endl;

        double durationHour = durationSec / 60;
        cout << durationHour << "\tHours" << endl;
        printf("\n");
    }
}

void guessPwdWoutStore(int threadID, int len, string correctPassword, vector<char> usableChars)
{
    using namespace chrono;
    static bool printOnce = true; //Used for printing duration
    guess = genPwd(len, usableChars);
    correctPassword.resize(len);

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

    printf("\n");
    printline(120);
    cout << "The password " << guess << " was guessed by Thread #" << threadWinner << " after " << --totalAttempts << " attempts" << endl;
    printline(120);

    if (printOnce == true)
    {
        printOnce = false;
        printline(27);
        cout << "\t Duration" << endl;
        printline(27);

        auto durationNano = duration_cast<nanoseconds>(stop - start);
        cout << (double)durationNano.count() << "\tNanoseconds" << endl;

        double durationMicro = durationNano.count() / 1000;
        cout << durationMicro << "\t\tMicroseconds" << endl;

        double durationMilli = durationMicro / 1000;
        cout << durationMilli << "\t\tMilliseconds" << endl;

        double durationSec = durationMilli / 1000;
        cout << durationSec << "\tSeconds" << endl;

        double durationMin = durationSec / 60;
        cout << durationMin << "\tMinutes" << endl;

        double durationHour = durationSec / 60;
        cout << durationHour << "\tHours" << endl;
        printf("\n");
    }
}

void guessPwd(int threadID, bool nostore, string correctPassword)
{
    int passLen = correctPassword.size();
    // static bool printOnce = true;

    if (nostore)
        guessPwdWoutStore(threadID, passLen, correctPassword, usableChars);
    else
        guessPwdWStore(threadID, passLen, correctPassword, usableChars);

    // if (printOnce == true)
    // {
    // printOnce = false;
    // if (nostore)
    // {
    // printf("\n");
    // printline(120);
    // cout << "Password " << guess << " was guessed by Thread #" << threadWinner << " after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
    // printline(120);

    // printline(9);
    // cout << "Duration:" << endl;
    // printline(9);
    // }
    // else
    // {
    // printf("\n");
    // printline(120);
    // cout << "Password " << guess << " was guessed by Thread #" << threadWinner << " after " << --totalAttempts << " attempts" << endl;
    // printline(120);

    // printline(9);
    // cout << "Duration:" << endl;
    // printline(9);
    // }
    // }
}

#endif