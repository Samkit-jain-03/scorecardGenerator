#include <iostream>
using namespace std;
class CricketMatch
{
private:
    int batsmanRuns[2];
    int batsmanBalls[2];
    int batsmanOuts;
    int batsmanOutCount[2];
    int currentBatsman; 
    int bowlerRuns;
    int bowlerBalls;
    int bowlerWickets;
    int wideBalls;
public:
    CricketMatch(int initialRuns = 0, int initialWickets = 0, int wides = 0);
    void extras(int runs = 1);
    void wicket();
    void process_ball(int input = 0);
    void play_overs();
    friend void scorecard(CricketMatch match);
};
CricketMatch::CricketMatch(int initialRuns, int initialWickets, int wides)
{
    batsmanRuns[0] = batsmanRuns[1] = 0;
    batsmanBalls[0] = batsmanBalls[1] = 0;
    batsmanOuts = initialWickets;
    batsmanOutCount[0] = batsmanOutCount[1] = 0;
    currentBatsman = 0;
    bowlerRuns = initialRuns;
    bowlerBalls = 0;
    bowlerWickets = initialWickets;
    wideBalls = wides;
}
void CricketMatch::extras(int runs)
{
    wideBalls++;
    bowlerRuns += runs;
    cout << "Wide ball. Extra run added.\n";
}
void CricketMatch::wicket()
{
    cout << "Batsman " << currentBatsman + 1 << " is out!\n";
    batsmanOuts++;
    bowlerWickets++;
    batsmanBalls[currentBatsman]++;
    batsmanOutCount[currentBatsman]++;
    cout << "Wicket fallen!\n";

    if (batsmanOuts < 2)
    {
        currentBatsman = 1 - currentBatsman;
        cout << "Next batsman comes to crease.\n";
    }
    else
    {
        cout << "Both batsmen out. Innings ends.\n";
    }
    bowlerBalls++;
}
void CricketMatch::process_ball(int input)
{
    switch (input)
    {
    case -2:
        extras();
        break;
    case -1:
        if (batsmanOuts < 2)
            wicket();
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        batsmanRuns[currentBatsman] += input;
        batsmanBalls[currentBatsman]++;
        bowlerRuns += input;
        bowlerBalls++;
        if (input % 2 == 1 && batsmanOuts < 2)
            currentBatsman = 1 - currentBatsman;
        break;
    default:
        cout << "Invalid input.\n";
        break;
    }
}
void CricketMatch::play_overs()
{
    for (int i = 0; i < 12;)
    {
        if (batsmanOuts >= 2)
        {
            cout << "No more batsmen. Ending over early.\n";
            break;
        }
        int input;
        cout << "Ball " << i + 1 << " (0-6, -1 out, -2 wide): ";
        cin >> input;
        process_ball(input);
        if (input != -2)
            i++;
    }
}
void scorecard(CricketMatch match)
{
    cout << "\n    Scorecard    \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "Batsman " << i + 1 << ":\n";
        cout << "Runs: " << match.batsmanRuns[i] << "\n";
        cout << "Balls Faced: " << match.batsmanBalls[i] << "\n";
        float sr = match.batsmanBalls[i] ? (match.batsmanRuns[i] * 100.0f / match.batsmanBalls[i]) : 0;
        cout << "Strike Rate: " << sr << "\n";
        cout << "Times Out: " << match.batsmanOutCount[i] << "\n\n";
    }
    cout << "Total Wickets Lost: " << match.batsmanOuts << "\n";
    cout << "\nBowler:\n";
    cout << "Runs Conceded: " << match.bowlerRuns << "\n";
    cout << "Balls Bowled: " << match.bowlerBalls << "\n";
    cout << "Wickets Taken: " << match.bowlerWickets << "\n";
    cout << "Wides: " << match.wideBalls << "\n";
}
int main()
{
    CricketMatch match;
    cout << "Enter Ball-by-Ball Inputs:\n";
    match.play_overs();
    scorecard(match);
    return 0;
}


