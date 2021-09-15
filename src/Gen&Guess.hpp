//Generation and guessing functions
#ifndef GEN_GUESS_HPP_
#define GEN_GUESS_HPP_

#include "PGG.hpp"

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

char randChar()
{
    return usableChars[rand() % usableChars.size()];
}

void guessPwdWStore(vector<char> usableChars) //Can specify either the global vector or another vector of usableChars.
{
    using namespace chrono;
    guess = genPwd(passLen);
    correctPassword.resize(passLen);

    auto start = high_resolution_clock::now(); //Start the timer

    if (noPrint == false)
    {
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
    }
    else
    {

        while (guess != correctPassword)
        {
            guess = genPwd(passLen);

            if (find(guesses.begin(), guesses.end(), guess) != guesses.end()) //Check for duplicates
            {
                totalAttempts++;
            }
            else
            {
                guesses.push_back(guess);
                totalAttempts++;
                actualAttempts++;
            }
        }
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

    if (noPrint == false)
    {
        while (guess != correctPassword)
        {
            guess = genPwd(passLen);
            cout << "Guess: " << guess << '\t' << "Total Attempts: " << totalAttempts++ << '\n';
        }
    }
    else
    {
        while (guess != correctPassword)
        {
            guess = genPwd(passLen);
            totalAttempts++;
        }
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

//Go through the password character by character
void seriesGuessV1(vector<char> usableChars)
{
    using namespace chrono;
    int cAttempts = 0; //How many times c has been guessed and checked
    auto start = high_resolution_clock::now();
    char c = randChar();

    if (noPrint == false)
    {
        for (int i = 0; i < passLen; i++)
        {
            while (c != correctPassword[i])
            {
                printf("Trying %c\n", c);
                c = randChar();
                cAttempts++;
            }
            printf("Corrrect char was %c\n", c);
        }
    }
    else
    {
        for (int i = 0; i < passLen; i++)
        {
            while (c != correctPassword[i])
            {
                c = randChar();
                cAttempts++;
            }
        }
    }

    auto stop = high_resolution_clock::now();

    printf("\n");
    string result;
    result = createLine(120);
    result += ('\n' + correctPassword + " was guessed after " + to_string(--cAttempts) + " single char attempts.\n");

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

//TODO:
//Same idea but do it like this:
//AAA
//AAB
//AAC, etc.
void seriesGuessV2(vector<char> usableChars)
{
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
void seriesGuessV1()
{
    seriesGuessV1(usableChars);
}
void seriesGuessV2()
{
    seriesGuessV2(usableChars);
}

void guessPwd()
{
    if (storePwds == true && useSeriesGuess == false)
        guessPwdWoutStore();
    else if (storePwds == false && useSeriesGuess == false)
        guessPwdWStore();
    else if (useSeriesGuess == true)
        seriesGuessV1();
    else
        printf("guessPwd() error lol");
}

#endif