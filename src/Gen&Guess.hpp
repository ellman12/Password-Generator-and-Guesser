//Generation and guessing functions
#ifndef GEN_GUESS_HPP_
#define GEN_GUESS_HPP_

#include "PGG.hpp"

void guessPwdWStore(vector<char> usableChars) //Can specify either the global vector or another vector of usableChars.
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now(); //Start the timer

    while (guess != correctPassword)
    {
        guess = genPwd(passLen);
        cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts << '\t' << "Without Dupes: " << actualAttempts << "\t# of Stored Guesses: " << guesses.size() << " ";

        if (find(guesses.begin(), guesses.end(), guess) != guesses.end()) //Check for duplicates
        {
            printf("\tAlready in the vector");
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

    string result;
    result = createLine(120);
    result += ('\n' + guess + " was guessed after " + to_string(--totalAttempts) + " attempts with duplicates and " + to_string(--actualAttempts) + " attempts without duplicates.\nThere were " + to_string(totalAttempts - actualAttempts) + " duplicate guesses.\n");
    result += createLine(120) + '\n';

    result += createLine(27);
    result += "\n\t Duration\n";
    result += createLine(27) + '\n';

    auto durationNano = duration_cast<nanoseconds>(stop - start);
    result += to_string((double)durationNano.count()) + "\tNanoseconds\n";

    double durationMicro = durationNano.count() / 1000;
    result += (to_string(durationMicro) + "\tMicroseconds\n");

    double durationMilli = durationMicro / 1000;
    result += (to_string(durationMilli) + "\tMilliseconds\n");

    double durationSec = durationMilli / 1000;
    result += (to_string(durationSec) + "\tSeconds\n");

    double durationMin = durationSec / 60;
    result += (to_string(durationMin) + "\tMinutes\n");

    double durationHour = durationMin / 60;
    result += (to_string(durationHour) + "\tHours\n\n");

    if (sendToFile == true)
    {
        fstream resultFile;
        resultFile.open(fileName, ios::out);
        resultFile << result;
        resultFile.close();
    }

    cout << result << endl;
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
    string result;
    result = createLine(120);
    result += ('\n' + guess + " was guessed after " + to_string(--totalAttempts) + " attempts.\n");

    result += createLine(120) + '\n';

    result += createLine(27);
    result += "\n\t Duration\n";
    result += createLine(27) + '\n';

    auto durationNano = duration_cast<nanoseconds>(stop - start);
    result += to_string((double)durationNano.count()) + "\tNanoseconds\n";

    double durationMicro = durationNano.count() / 1000;
    result += (to_string(durationMicro) + "\tMicroseconds\n");

    double durationMilli = durationMicro / 1000;
    result += (to_string(durationMilli) + "\tMilliseconds\n");

    double durationSec = durationMilli / 1000;
    result += (to_string(durationSec) + "\tSeconds\n");

    double durationMin = durationSec / 60;
    result += (to_string(durationMin) + "\tMinutes\n");

    double durationHour = durationMin / 60;
    result += (to_string(durationHour) + "\tHours\n\n");

    if (sendToFile == true)
    {
        fstream resultFile;
        resultFile.open(fileName, ios::out);
        resultFile << result;
        resultFile.close();
    }

    cout << result << endl;
}

//Default to using the global usableChars
void guessPwdWStore()
{
    guessPwdWStore(usableChars);
}
void guessPwdWoutStore()
{
    guessPwdWoutStore(usableChars);
}

void guessPwd()
{
    if (storePwds)
        guessPwdWoutStore();
    else
        guessPwdWStore();
}

#endif