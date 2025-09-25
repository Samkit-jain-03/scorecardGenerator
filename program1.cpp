#include <iostream>
using namespace std;
class CricketMatch
{
private:
    int batsmanRuns;
    int batsmanBalls;
    int batsmanOuts;
    int bowlerRuns;
    int bowlerBalls;
    int bowlerWickets;
    int wideBalls;
public:
    void init();
    void extras(int input);
    void wicket(int input);
    void process_ball(int input);
    void play_overs();
    friend void scorecard(CricketMatch match);
};
void CricketMatch::init()
{
    batsmanRuns = 0;
    batsmanBalls = 0;
    batsmanOuts = 0;
    bowlerRuns = 0;
    bowlerBalls = 0;
    bowlerWickets = 0;
    wideBalls = 0;
}
void CricketMatch::extras(int input) 
{
    if (input == -2) 
    {
        wideBalls++;
        bowlerRuns++;
        cout << "Wide ball. Extra run added.\n";
    }
}
void CricketMatch::wicket(int input)
{
    if (input == -1) 
    {
        batsmanOuts++;
        bowlerWickets++;
    }
}
void CricketMatch::process_ball(int input)
{
    if (input == -2)
    {
        extras(input);
    } 
    else if (input == -1) 
    {
        wicket(input);
        batsmanBalls++;
        bowlerBalls++;
    }
    else if (input >= 0 && input <= 6) 
    {
        batsmanRuns += input;
        bowlerRuns += input;
        batsmanBalls++;
        bowlerBalls++;
    }
    else 
    {
        cout << "Invalid input.\n";
    }
}
void CricketMatch::play_overs() {
    for (int i = 0; i < 12; ) 
    {
        int input;
        cout << "Ball " << i + 1 << " (0-6, -1 out, -2 wide): ";
        cin >> input;
        if (input == -2)
        {
            process_ball(input);
            continue;
        }
        else
        {
            process_ball(input);
            i++;
        }
    }
}
void scorecard(CricketMatch match)
{
    cout << "\n--- Scorecard ---\n";
    cout << "Batsman:\n";
    cout << "Runs: " << match.batsmanRuns << "\n";
    cout << "Balls Faced: " << match.batsmanBalls << "\n";
    float sr = match.batsmanBalls ? (match.batsmanRuns * 100.0f / match.batsmanBalls) : 0;
    cout << "Strike Rate: " << sr << "\n";
    cout << "Wickets Lost: " << match.batsmanOuts << "\n\n";
    cout << "Bowler:\n";
    cout << "Runs Conceded: " << match.bowlerRuns << "\n";
    cout << "Balls Bowled: " << match.bowlerBalls << "\n";
    cout << "Wickets Taken: " << match.bowlerWickets << "\n";
    cout << "Wides: " << match.wideBalls << "\n";
}
int main()
{
    CricketMatch match;
    match.init();
    cout << "Enter Ball-by-Ball Inputs:\n";
    match.play_overs();
    scorecard(match);
    return 0;
}



