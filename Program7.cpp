#include <iostream>
using namespace std;

class CricketMatch {
private:
    string batsmanName[2];
    int batsmanRuns[2];
    int batsmanBalls[2];
    int batsmanOuts[2];
    string bowlerName[2];
    int runsConceded[2];
    int ballsBowled[2];
    int wickets[2];
    int wides[2];
    int batsmanOutCount;
    int currentStriker;
    int nonStriker;
    int currentBowler;

    static int totalMatches; 

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
        cout << "Enter name for Batsman 1: ";
        cin >> batsmanName[0];
        cout << "Enter name for Batsman 2: ";
        cin >> batsmanName[1];
        cout << "Enter name for Bowler 1: ";
        cin >> bowlerName[0];
        cout << "Enter name for Bowler 2: ";
        cin >> bowlerName[1];
        totalMatches++; 
    }

    CricketMatch(string b1, string b2, string bo1, string bo2) {
        batsmanOutCount = 0;
        currentStriker = 0;
        nonStriker = 1;
        currentBowler = 0;
        batsmanName[0] = b1;
        batsmanName[1] = b2;
        bowlerName[0] = bo1;
        bowlerName[1] = bo2;
        for (int i = 0; i < 2; i++) {
            batsmanRuns[i] = batsmanBalls[i] = batsmanOuts[i] = 0;
            runsConceded[i] = ballsBowled[i] = wickets[i] = wides[i] = 0;
        }
        totalMatches++;
    }

    static void showTotalMatches() {
        cout << "Total Matches Played: " << totalMatches << "\n";
    }

    void operator++() {
        wides[currentBowler]++;
        runsConceded[currentBowler]++;
        cout << "Wide ball by " << bowlerName[currentBowler] << ". Extra run added.\n";
    }

    void wicket() {
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

    void process_ball(int input) {
        switch (input) {
        case -2:
            ++(*this);
            break;
        case -1:
            if (batsmanOuts[0] < 1 || batsmanOuts[1] < 1)
                wicket();
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6:
            batsmanRuns[currentStriker] += input;
            batsmanBalls[currentStriker]++;
            runsConceded[currentBowler] += input;
            ballsBowled[currentBowler]++;
            if (input % 2 == 1 && (batsmanOuts[0] < 1 && batsmanOuts[1] < 1))
                swap(currentStriker, nonStriker);
            break;
        default:
            cout << "Invalid input.\n";
            break;
        }
    }

    void play_overs() {
        int totalBalls = 24;
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
            process_ball(input);
            if (input != -2)
                i++;
        }
    }

    void batsman_details() {
        cout << "\n BATTING SCORECARD \n";
        for (int i = 0; i < 2; i++) {
            float sr = batsmanBalls[i] ? (batsmanRuns[i] * 100.0f / batsmanBalls[i]) : 0;
            cout << batsmanName[i] << ": " << batsmanRuns[i] << " (" << batsmanBalls[i]
                 << ") - SR: " << sr << "\n";
            cout << "Outs: " << batsmanOuts[i] << "\n\n";
        }
        cout << "Total Wickets Lost: " << batsmanOutCount << "\n";
    }

    void bowler_details() {
        cout << "\n BOWLING SUMMARY \n";
        for (int i = 0; i < 2; i++) {
            float econ = (ballsBowled[i] / 6.0f) ? (runsConceded[i] / (ballsBowled[i] / 6.0f)) : 0;
            cout << bowlerName[i] << ": " << runsConceded[i] << " runs, " << wickets[i]
                 << " wickets, Econ: " << econ << "\n";
            cout << "Wides: " << wides[i] << "\n\n";
        }
    }
};

int CricketMatch::totalMatches = 0; 

int main() {
    CricketMatch match;
    cout << "\nEnter Ball-by-Ball Inputs:\n";
    match.play_overs();
    match.batsman_details();
    match.bowler_details();
    CricketMatch::showTotalMatches(); 
    return 0;
}


