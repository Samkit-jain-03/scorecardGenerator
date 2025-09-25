#include <iostream>
using namespace std;
struct Batsman {
    string name;
    int runs = 0;
    int balls = 0;
    int outs = 0;
    float strike_rate() const
    {
        return balls ? (runs * 100.0f / balls) : 0;
    }
    void display() const 
    {
        cout << name << ": " << runs << " (" << balls << ") - SR: " << strike_rate() << "\n";
        }
};
struct Bowler {
    string name;
    int runs_conceded = 0;
    int balls_bowled = 0;
    int wickets = 0;
    int wides = 0;
    float economy() const
    {
        float overs = balls_bowled / 6.0f;
        return overs ? (runs_conceded / overs) : 0;
    }
    void display() const 
    {
        cout << name << ": " << runs_conceded << " runs, " << wickets
             << " wickets, Econ: " << economy() << "\n";
    }
};
class CricketMatch
{
private:
    Batsman batsmen[2];
    Bowler bowlers[2];
    int batsmanOutCount = 0;
    int currentStriker = 0;
    int nonStriker = 1;
    int currentBowler = 0;
public:
    CricketMatch();
    void extras(int runs = 1);
    void wicket();
    void process_ball(int input);
    void play_overs();
    friend void batsman_details(CricketMatch match);
    friend void bowler_details(CricketMatch match);
};
CricketMatch::CricketMatch()
{
    cout << "Enter name for Batsman 1: ";
    cin >> batsmen[0].name;
    cout << "Enter name for Batsman 2: ";
    cin >> batsmen[1].name;
    cout << "Enter name for Bowler 1: ";
    cin >> bowlers[0].name;
    cout << "Enter name for Bowler 2: ";
    cin >> bowlers[1].name;
}
void CricketMatch::extras(int runs)
{
    bowlers[currentBowler].wides++;
    bowlers[currentBowler].runs_conceded += runs;
    cout << "Wide ball by " << bowlers[currentBowler].name << ". Extra run added.\n";
}
void CricketMatch::wicket()
{
    cout << batsmen[currentStriker].name << " is out!\n";
    batsmen[currentStriker].balls++;
    batsmen[currentStriker].outs++;
    bowlers[currentBowler].balls_bowled++;
    bowlers[currentBowler].wickets++;
    batsmanOutCount++;
    if (batsmen[0].outs >= 1 && batsmen[1].outs >= 1)
    {
        cout << "Both batsmen out. Innings ends.\n";
    } 
    else
    {
        cout << "Next batsman comes to crease.\n";
        if (batsmen[0].outs >= 1)
        {
            currentStriker = 1;
            nonStriker = 0;
        } else 
        {
            currentStriker = 0;
            nonStriker = 1;
        }
    }
}
void CricketMatch::process_ball(int input)
{
    switch (input)
    {
    case -2:
        extras();
        break;
    case -1:
        if (batsmen[0].outs < 1 || batsmen[1].outs < 1)
            wicket();
        break;
    case 0: case 1: case 2: case 3: case 4: case 5: case 6:
        batsmen[currentStriker].runs += input;
        batsmen[currentStriker].balls++;
        bowlers[currentBowler].runs_conceded += input;
        bowlers[currentBowler].balls_bowled++;
        if (input % 2 == 1 && (batsmen[0].outs < 1 && batsmen[1].outs < 1))
            swap(currentStriker, nonStriker);
        break;
    default:
        cout << "Invalid input.\n";
        break;
    }
}
void CricketMatch::play_overs()
{
    int totalBalls = 24;
    for (int i = 0; i < totalBalls;) {
        if (batsmen[0].outs >= 1 && batsmen[1].outs >= 1) 
        {
            cout << "\nInnings ends.\n";
            break;
        }
        currentBowler = (i / 6) % 2;
        cout << "\nBall " << i + 1 << " - Bowled by " << bowlers[currentBowler].name
             << ", Striker: " << batsmen[currentStriker].name << "\n";
        int input;
        cout << "Enter result (0-6, -1 out, -2 wide): ";
        cin >> input;
        process_ball(input);

        if (input != -2)
            i++;
    }
}
void batsman_details(CricketMatch match) 
{
    cout << "\n       BATTING SCORECARD       \n";
    for (int i = 0; i < 2; i++)
    {
        match.batsmen[i].display();
        cout << "Outs: " << match.batsmen[i].outs << "\n\n";
    }
    cout << "Total Wickets Lost: " << match.batsmanOutCount << "\n";
}

void bowler_details(CricketMatch match)
{
    cout << "\n       BOWLING SUMMARY       \n";
    for (int i = 0; i < 2; i++) 
    {
        match.bowlers[i].display();
        cout << "Wides: " << match.bowlers[i].wides << "\n\n";
    }
}
int main() 
{
    CricketMatch match;
    cout << "\nEnter Ball-by-Ball Inputs:\n";
    match.play_overs();
    batsman_details(match);
    bowler_details(match);
    return 0;
}



