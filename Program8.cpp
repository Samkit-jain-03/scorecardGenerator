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
    CricketMatch(bool takeInput) {
        batsmanOutCount = 0;
        currentStriker = 0;
        nonStriker = 1;
        currentBowler = 0;
        for (int i = 0; i < 2; i++) {
            batsmanRuns[i] = batsmanBalls[i] = batsmanOuts[i] = 0;
            runsConceded[i] = ballsBowled[i] = wickets[i] = wides[i] = 0;
        }
        if (takeInput) {
            cout << "Enter name for Batsman 1: ";
            cin >> batsmanName[0];
            cout << "Enter name for Batsman 2: ";
            cin >> batsmanName[1];
            cout << "Enter name for Bowler 1: ";
            cin >> bowlerName[0];
            cout << "Enter name for Bowler 2: ";
            cin >> bowlerName[1];
        }
        totalMatches++;
    }

    static void showTotalMatches() {
        cout << "\nTotal Matches Played So Far: " << totalMatches << "\n";
    }

    void action(int runs) {
        wides[currentBowler]++;
        runsConceded[currentBowler] += runs;
        cout << "Wide ball by " << bowlerName[currentBowler] 
             << ". " << runs << " extra run(s) added.\n";
    }

    void action(bool isWicket) {
        if (isWicket) {
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
    }

    void action(int runs, bool isRun) {
        batsmanRuns[currentStriker] += runs;
        batsmanBalls[currentStriker]++;
        runsConceded[currentBowler] += runs;
        ballsBowled[currentBowler]++;
        if (runs % 2 == 1 && (batsmanOuts[0] < 1 && batsmanOuts[1] < 1))
            swap(currentStriker, nonStriker);
    }

    void action() {
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
                action(1);
            } 
            else if (input == -1) {
                if (batsmanOuts[0] < 1 || batsmanOuts[1] < 1)
                    action(true);
            } 
            else if (input >= 0 && input <= 6) {
                action(input, true);
            } 
            else {
                cout << "Invalid input.\n";
                continue;
            }

            if (input != -2) i++;
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

    CricketMatch operator+(const CricketMatch &other) {
        CricketMatch result(false);
        for (int i = 0; i < 2; i++) {
            result.batsmanName[i] = batsmanName[i];
            result.bowlerName[i] = bowlerName[i];
            result.batsmanRuns[i] = batsmanRuns[i] + other.batsmanRuns[i];
            result.batsmanBalls[i] = batsmanBalls[i] + other.batsmanBalls[i];
            result.batsmanOuts[i] = batsmanOuts[i] + other.batsmanOuts[i];
            result.runsConceded[i] = runsConceded[i] + other.runsConceded[i];
            result.ballsBowled[i] = ballsBowled[i] + other.ballsBowled[i];
            result.wickets[i] = wickets[i] + other.wickets[i];
            result.wides[i] = wides[i] + other.wides[i];
        }
        result.batsmanOutCount = batsmanOutCount + other.batsmanOutCount;
        return result;
    }
};

int CricketMatch::totalMatches = 0; 

int main() {
    cout << "    MATCH 1    \n";
    CricketMatch match1(true);
    cout << "\nEnter Ball-by-Ball Inputs:\n";
    match1.action();
    match1.batsman_details();
    match1.bowler_details();
    CricketMatch::showTotalMatches();

    cout << "\n    MATCH 2    \n";
    CricketMatch match2(true);
    cout << "\nEnter Ball-by-Ball Inputs:\n";
    match2.action();
    match2.batsman_details();
    match2.bowler_details();
    CricketMatch::showTotalMatches();

    cout << "\n    COMBINED MATCH SUMMARY (Match1 + Match2)      \n";
    CricketMatch combined = match1 + match2;
    combined.batsman_details();
    combined.bowler_details();

    return 0;
}


