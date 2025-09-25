#include <iostream>
using namespace std;

class Game {
protected:
    string batsmanName[2];
    string bowlerName[2];
public:
    void inputPlayers() {
        cout << "Enter name for Batsman 1: ";
        cin >> batsmanName[0];
        cout << "Enter name for Batsman 2: ";
        cin >> batsmanName[1];
        cout << "Enter name for Bowler 1: ";
        cin >> bowlerName[0];
        cout << "Enter name for Bowler 2: ";
        cin >> bowlerName[1];
    }
};

class CricketMatch : public Game {
protected:
    int batsmanRuns[2];
    int batsmanBalls[2];
    int batsmanOuts[2];
    int runsConceded[2];
    int ballsBowled[2];
    int wickets[2];
    int wides[2];
    int batsmanOutCount;
    int currentStriker;
    int nonStriker;
    int currentBowler;

public:
    CricketMatch() {
        batsmanOutCount = 0;
        currentStriker = 0;
        nonStriker = 1;
        currentBowler = 0;
        for (int i = 0; i < 2; i++) {
            batsmanRuns[i] = batsmanBalls[i] = batsmanOuts[i] = 0;
            runsConceded[i] = ballsBowled[i] = wickets[i] = wides[i] = 0;
        }
    }

    void wideBall(int runs) {
        wides[currentBowler]++;
        runsConceded[currentBowler] += runs;
        cout << "Wide ball by " << bowlerName[currentBowler]
             << ". " << runs << " extra run(s).\n";
    }

    void wicketFallen() {
        cout << batsmanName[currentStriker] << " is out!\n";
        batsmanBalls[currentStriker]++;
        batsmanOuts[currentStriker]++;
        ballsBowled[currentBowler]++;
        wickets[currentBowler]++;
        batsmanOutCount++;
        if (batsmanOuts[0] >= 1 && batsmanOuts[1] >= 1) {
            cout << "Both batsmen out. Innings ends.\n";
        } else {
            cout << "Next batsman comes to crease.\n";
            if (batsmanOuts[0] >= 1) {
                currentStriker = 1;
                nonStriker = 0;
            } else {
                currentStriker = 0;
                nonStriker = 1;
            }
        }
    }

    void runsScored(int runs) {
        batsmanRuns[currentStriker] += runs;
        batsmanBalls[currentStriker]++;
        runsConceded[currentBowler] += runs;
        ballsBowled[currentBowler]++;
        if (runs % 2 == 1 && (batsmanOuts[0] < 1 && batsmanOuts[1] < 1)) {
            swap(currentStriker, nonStriker);
        }
    }

    void showBatsmanDetails() {
        cout << "\n BATTING SCORECARD \n";
        for (int i = 0; i < 2; i++) {
            float sr = batsmanBalls[i] ? (batsmanRuns[i] * 100.0f / batsmanBalls[i]) : 0;
            cout << batsmanName[i] << ": "
                 << batsmanRuns[i] << " (" << batsmanBalls[i] << ") - SR: " << sr << "\n";
            cout << "Outs: " << batsmanOuts[i] << "\n\n";
        }
        cout << "Total Wickets Lost: " << batsmanOutCount << "\n";
    }

    void showBowlerDetails() {
        cout << "\n BOWLING SUMMARY \n";
        for (int i = 0; i < 2; i++) {
            float econ = (ballsBowled[i] / 6.0f) ? (runsConceded[i] / (ballsBowled[i] / 6.0f)) : 0;
            cout << bowlerName[i] << ": " << runsConceded[i]
                 << " runs, " << wickets[i] << " wickets, Econ: " << econ << "\n";
            cout << "Wides: " << wides[i] << "\n\n";
        }
    }
};

class Tournament : public CricketMatch {
public:
    Tournament() {
        inputPlayers();
    }

    void playMatch() {
        int totalBalls = 12;
        for (int i = 0; i < totalBalls;) {
            if (batsmanOuts[0] >= 1 && batsmanOuts[1] >= 1) {
                cout << "\nInnings ends.\n";
                break;
            }
            currentBowler = (i / 6) % 2;
            cout << "\nBall " << i + 1 << " - Bowled by " << bowlerName[currentBowler]
                 << ", Striker: " << batsmanName[currentStriker] << "\n";
            int input;
            cout << "Enter result (0-6, -1 out, -2 wide): ";
            cin >> input;
            if (input == -2) {
                wideBall(1);
            } else if (input == -1) {
                if (batsmanOuts[0] < 1 || batsmanOuts[1] < 1) wicketFallen();
            } else if (input >= 0 && input <= 6) {
                runsScored(input);
            } else {
                cout << "Invalid input.\n";
                continue;
            }
            if (input != -2) i++;
        }
        showBatsmanDetails();
        showBowlerDetails();
    }
};

int main() {
    Tournament match;
    match.playMatch();
    return 0;
}


