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

class gthread //Guesser thread
{
public:
    //TODO: it doesn't like these static things
    static int totalAttempts;  //Total guess attempts without counting duplicates (i.e., guessing a password more than once)
    static int actualAttempts; //Total with duplicates counted
    static int passLen;
    static string correctPassword;
    static bool storeGuesses;
    static vector<string> guesses;
    static vector<char> usableChars; //The chars that could be in the password

    gthread(int passLen, string correctPassword, bool storeGuesses); //Constructor; creates actual thread object
    string genPwd(int len);
    void guessPwd(bool storePasswords);
    void guessPwdWoutStore(int len, string correctPassword); //TODO: Computer can be given length or not
    void guessPwdWStore(int len, string correctPassword);
    void usableCharsInit(bool usingDigits, bool usingLower, bool usingUpper, bool usingSpecialChars);
};

//Constructor
gthread::gthread(int passLen, string correctPassword, bool storeGuesses)
{
    gthread::totalAttempts = 1;
    gthread::actualAttempts = 1;
    gthread::passLen = passLen;
    gthread::correctPassword = correctPassword;
    gthread::storeGuesses = storeGuesses;
    printf("Thread created\n");
}

string gthread::genPwd(int len)
{
    string newPassword = "";
    newPassword.resize(len);

    for (int i = 0; i < len; i++) //Fill the new password string with random chars
    {
        newPassword[i] = gthread::usableChars[rand() % gthread::usableChars.size()];
    }
    return newPassword;
}

//Determine which chars a password could contain
void gthread::usableCharsInit(bool usingDigits, bool usingLower, bool usingUpper, bool usingSpecialChars)
{
    if (usingDigits)
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

void gthread::guessPwd(bool storePasswords)
{
    if (storePasswords)
        gthread::guessPwdWStore(passLen, correctPassword);
    else
        gthread::guessPwdWoutStore(passLen, correctPassword);
}

void gthread::guessPwdWStore(int len, string correctPassword)
{
    using namespace chrono;
    string guess;

    auto start = high_resolution_clock::now(); //Start the timer

    while (guess != correctPassword)
    {
        guess = genPwd(len);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << gthread::totalAttempts << '\t' << "Without Dupes: " << actualAttempts << '\t';

        if (find(gthread::guesses.begin(), gthread::guesses.end(), guess) != gthread::guesses.end()) //Check for duplicates
        {
            printf("Already in the vector");
            gthread::totalAttempts++;
        }
        else
        {
            gthread::guesses.push_back(guess);
            gthread::totalAttempts++;
            gthread::actualAttempts++;
        }
        printf("\n");
    }

    auto stop = high_resolution_clock::now(); //Stop the timer

    printf("\n");
    printline(97);
    cout << guess << " was guessed after " << --gthread::totalAttempts << " attempts with duplicates and " << --gthread::actualAttempts << " attempts without duplicates.\nThere were " << gthread::totalAttempts - gthread::actualAttempts << " duplicate guesses.\n";
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

void gthread::guessPwdWoutStore(int len, string correctPassword)
{
    using namespace chrono;
    string guess;

    auto start = high_resolution_clock::now();

    while (guess != correctPassword)
    {
        guess = genPwd(len);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << gthread::totalAttempts++ << '\n';
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(69);
    cout << guess << " was guessed after " << --gthread::totalAttempts << " attempts\n";
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

#endif