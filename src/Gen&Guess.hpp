#include "PGG Rewrite.hpp"

void guessPwdWStore()
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now(); //Start the timer

    while (guess != correctPassword)
    {
        guess = genPwd(passLen);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts << '\t' << "Without Dupes: " << actualAttempts << " ";

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
    printline(120);
    cout << "The password " << guess << " was guessed after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
    printline(120);

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

void guessPwdWStore(vector<char> usableChars)
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now(); //Start the timer

    while (guess != correctPassword)
    {
        guess = genPwd(passLen);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts << '\t' << "Without Dupes: " << actualAttempts << " ";

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
    printline(120);
    cout << "The password " << guess << " was guessed after " << --totalAttempts << " attempts with duplicates and " << --actualAttempts << " attempts without duplicates.\nThere were " << totalAttempts - actualAttempts << " duplicate guesses.\n";
    printline(120);

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

void guessPwdWoutStore()
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now();

    while (guess != correctPassword)
    {
        guess = genPwd(passLen);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << '\n';
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(120);
    cout << "The password " << guess << " was guessed after " << --totalAttempts << " attempts" << endl;
    printline(120);

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

void guessPwdWoutStore(vector<char> usableChars)
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now();

    while (guess != correctPassword)
    {
        guess = genPwd(passLen);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << '\n';
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    printline(120);
    cout << "The password " << guess << " was guessed after " << --totalAttempts << " attempts" << endl;
    printline(120);

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

void guessPwd()
{
    if (storePwds)
        guessPwdWoutStore();
    else
        guessPwdWStore();
}