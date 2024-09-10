#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

void GiveSeedToRandomNumberGenerator(void)
{
    srand(time(nullptr));
}

void ShuffleArray(int N, int arr[])
{
    for(int i = 0; i < N; ++i)
    {
        int j = rand() % N;
        swap(arr[i], arr[j]);
    }
}

void MakeNonRepeatingRandomNumber(int N, int r[])
{
    for(int i = 0; i < N; ++i)
    {
        r[i] = i;
    }

    ShuffleArray(N, r);
}

void PrintFlashcard(int num1, int num2)
{
    cout << "+-----+" << endl;
    cout << "|     |" << endl;
    cout << "|" << setw(2) << num1 << "x" << left << setw(2) << num2 << "|" << endl;
    cout << "|     |" << endl;
    cout << "+-----+" << endl;
}

int main(void)
{
    GiveSeedToRandomNumberGenerator();

    int numCards;
    do {
        cout << "How many flash cards do you want to work on? (1-144): ";
        cin >> numCards;
        if (numCards < 1 || numCards > 144) {
            cout << "The number of cards must be between 1 and 144." << endl;
        }
    } while (numCards < 1 || numCards > 144);

    int cards[144];
    MakeNonRepeatingRandomNumber(144, cards);

    int correctAnswers = 0;
    int startTime = time(nullptr);

    for (int i = 0; i < numCards; ++i) {
        int num1 = (cards[i] / 12) + 1;
        int num2 = (cards[i] % 12) + 1;
        int correctAnswer = num1 * num2;

        PrintFlashcard(num1, num2);

        int userAnswer;
        cout << "Enter Your Answer> ";
        cin >> userAnswer;

        if (userAnswer == correctAnswer) {
            cout << "Correct!" << endl;
            correctAnswers++;
        } else {
            cout << "Incorrect. The correct answer is " << correctAnswer << "." << endl;
        }
        cout << endl;
    }

    int endTime = time(nullptr);
    int duration = endTime - startTime;

    double percentage = (static_cast<double>(correctAnswers) / numCards) * 100;
    cout << "You answered " << numCards << " problems in " << duration << " seconds." << endl;
    cout << "You answered " << correctAnswers << " problems correctly (" 
              << fixed << setprecision(2) << percentage << "%)" << endl;

    return 0;
}