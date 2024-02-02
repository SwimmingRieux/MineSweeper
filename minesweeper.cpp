#include <bits/stdc++.h>
using namespace std;
#define deb(x) cout << #x << ":" << x << "\n"
#define deb2(x) cout << ":" << x << "\n"
#define in(x) cin >> x
#define pb push_back
#define pii pair<ll, ll>
#define piii pair<ll, pii>
#define f first
#define s second
#define ll int64_t
#define per(i, a, b) for (ll i = a; i <= b; i++)
#define rep(i, a, b) for (ll i = a; i >= b; i--)
#define outl(x) cout << x << endl;
#define outc(x) cout << x << " ";
const ll maxn = 1e6 + 15;
const ll maxr = 1e3 + 15;
const ll mod = 1e9 + 7;
const ll lg = 22;

struct Player
{
    string userName;
    int winsCount;
    int loosesCount;
};
struct PlayGround
{
    int rows;
    int columns;
    int mines;
};
Player players[maxn];
PlayGround pGround;
int playersCnt, scores, currentField[maxr][maxr], ultimateField[maxr][maxr], flg[maxr][maxr];

string printMenu()
{
    outl(" - Please choose an option from the MENU: -");
    outl("1- Start new game -");
    outl("2- Scoreboard -");
    outl("3- Exit");
    string inp;
    in(inp);
    if (inp != "1" && inp != "2" && inp != "3")
        return printMenu();
    return inp;
}

void setMines()
{
    int minesCount = pGround.mines;
    int n = pGround.rows;
    int m = pGround.columns;
    while (minesCount)
    {
        int randomColumn = rand() % m + 1;
        int randomRow = rand() % n + 1;
        if (ultimateField[randomRow][randomColumn] != -1)
        {
            ultimateField[randomRow][randomColumn] = -1;
            minesCount--;
        }
    }
}

void setNumbers()
{
    per(i, 1, pGround.rows) per(j, 1, pGround.columns) if (ultimateField[i][j] != -1)
    {
        per(k, i - 1, i + 1) per(l, j - 1, j + 1)
        {
            if (!(k == i && l == j) && ultimateField[k][l] == -1)
                ultimateField[i][j]++;
        }
    }
}

void selectGameMode()
{
    outl(" - Please choose the game mode -")
        outl("1- Easy -");
    outl("2- Medium -");
    outl("3- Hard -");
    string inp;
    in(inp);
    if (inp == "1")
    {
        pGround.rows = pGround.columns = 9;
        pGround.mines = 10;
        setMines();
        setNumbers();
    }
    else if (inp == "2")
    {
        pGround.rows = pGround.columns = 16;
        pGround.mines = 40;
        setMines();
        setNumbers();
    }
    else if (inp == "3")
    {
        pGround.rows = 16;
        pGround.columns = 30;
        pGround.mines = 99;
        setMines();
        setNumbers();
    }
    else
        selectGameMode();
}

string printInGameMenu()
{
    outl(" - Please choose an option from the game MENU: -")
        outl("1- Show a cell -");
    outl("2- Sign/UnSign a cell -");
    outl("3- Exit");
    string inp;
    in(inp);
    if (inp != "1" && inp != "2" && inp != "3")
        return printInGameMenu();
    return inp;
}

void unlockCells(int row, int col)
{
    currentField[row][col] = ultimateField[row][col];
    if(currentField[row][col] != 0) return;
    per(i, row - 1, row + 1)
    {
        per(j, col - 1, col + 1) if (!(i == row && j == col)) if (currentField[i][j] == -2 && (ultimateField[i][j] >= 0 && ultimateField[i][j] <= 8))
            unlockCells(i, j);
    }
}

int showCell(int row, int col)
{
    if (ultimateField[row][col] == -1)
        return -1;
    if (ultimateField[row][col] != 0)
    {
        currentField[row][col] = ultimateField[row][col];
        return 1;
    }
    unlockCells(row, col);
    return 1;
}

void printUltimate()
{
    system("CLS");
    outl("- Ultimate Field : ");
    rep(i, pGround.rows, 1)
    {
        per(j, 1, pGround.columns)
        {
            if (ultimateField[i][j] == -1)
            {
                outc("B");
            }
            else
            {
                outc(ultimateField[i][j]);
            }
        }
        cout << endl;
    }
}

void printCurrent()
{
    system("CLS");
    rep(i, pGround.rows, 1)
    {
        per(j, 1, pGround.columns)
        {
            if (flg[i][j] && currentField[i][j] == -2)
            {
                outc("^");
            }
            else if (currentField[i][j] == -2)
            {
                outc("*");
            }
            else
            {
                outc(currentField[i][j]);
            }
        }
        cout << endl;
    }
}

void gameWon()
{
    outl("- You Won! -");
    string tmp;
    in(tmp);
    bool exists = 0;
    per(i, 1, playersCnt) if (players[i].userName == tmp)
    {
        players[i].winsCount++;
        exists = 1;
        break;
    }
    if (!exists)
    {
        playersCnt++;
        players[playersCnt].userName = tmp;
        players[playersCnt].loosesCount = 0;
        players[playersCnt].winsCount = 1;
    }
}

void gameLoose()
{
    outl("- Game Over -");
    outl("- Please Enter your username");
    string tmp;
    in(tmp);
    bool exists = 0;
    per(i, 1, playersCnt) if (players[i].userName == tmp)
    {
        players[i].loosesCount++;
        exists = 1;
        break;
    }
    if (!exists)
    {
        playersCnt++;
        players[playersCnt].userName = tmp;
        players[playersCnt].loosesCount = 1;
        players[playersCnt].winsCount = 0;
    }
}

void playGame()
{
    while (1)
    {
        printCurrent();
        string inp = printInGameMenu();
        if (inp == "1")
        {
            int col, row;
            in(row);
            in(col);
            if (flg[row][col])
            {
                outl("Are you sure you want to show this cell?[Y/N]");
                string tmpInp;
                in(tmpInp);
                if (tmpInp == "N")
                    continue;
            }
            int result = showCell(row, col);
            if (result == -1)
            {
                gameLoose();
                break;
            }
            if (scores == pGround.rows * pGround.columns - pGround.mines)
            {
                gameWon();
                break;
            }
        }
        else if (inp == "2")
        {
            int col, row;
            in(row);
            in(col);
            if (currentField[row][col] == -2)
                flg[row][col] ^= 1; // xor
            else
            {
                outl("- you can't sign a cell already being shown, send any key to proceed...");
                string tmp;
                in(tmp);
            }
        }
        else
            break;
    }
}

void cleanCurrent()
{
    per(i, 1, pGround.rows) per(j, 1, pGround.columns) currentField[i][j] = -2;
}

void fixMargins()
{
    // fixing the margins
    per(i, 0, pGround.rows + 1) ultimateField[i][0] = -1000;
    per(i, 0, pGround.rows + 1) ultimateField[i][pGround.columns + 1] = -1000;
    per(i, 0, pGround.columns + 1) ultimateField[pGround.rows + 1][i] = -1000;
    per(i, 0, pGround.columns + 1) ultimateField[0][i] = -1000;
}

void sortPlayers()
{
    per(i, 1, playersCnt)
    {
        per(j, i + 1, playersCnt)
        {
            if (players[i].winsCount < players[j].winsCount || (players[i].winsCount == players[j].winsCount && players[i].loosesCount > players[j].loosesCount))
            {
                Player tmp = players[i];
                players[i] = players[j];
                players[j] = tmp;
            }
        }
    }
}

void cleanFlags()
{
    per(i, 1, pGround.rows) per(j, 1, pGround.columns) flg[i][j] = 0;
}

void cleanUltimate()
{
    per(i,0,maxr-1) per(j,0,maxr-1) ultimateField[i][j] = 0;
}

void readFromFile()
{
    ifstream inFile("players.txt");
    int i = 1;
    string tmp;
    while (getline(inFile, tmp))
    {
        players[i].userName = tmp;
        getline(inFile, tmp);
        players[i].winsCount = stoi(tmp);
        getline(inFile, tmp);
        players[i].loosesCount = stoi(tmp);
        i++;
    }
    playersCnt = --i;
    inFile.close();
}

void writeToFile()
{
    ofstream outFile("players.txt");
    per(i, 1, playersCnt)
    {
        outFile << players[i].userName << endl;
        outFile << players[i].winsCount << endl;
        outFile << players[i].loosesCount << endl;
    }
    outFile.close();
}

signed main()
{
    readFromFile();
    srand(time(0));
    string inp = printMenu();
    while (1)
    {
        if (inp == "1")
        {
            scores = 0;
            cleanUltimate();
            selectGameMode();
            cleanCurrent();
            cleanFlags();
            fixMargins();
            playGame();
            printUltimate();
            outl("- send any key to show the menu -");
            string tmpInp;
            in(tmpInp);
            inp = printMenu();
        }
        else if (inp == "2")
        {
            sortPlayers();
            outl("- RANKING : ");
            per(i, 1, playersCnt)
            {
                outc(i);
                outc(" - ");
                outl(players[i].userName);
            }
            outl("- send any key to show the menu -");
            string tmpInp;
            in(tmpInp);
            inp = printMenu();
        }
        else
        {
            writeToFile();
            break;
        }
    }
    return 0;
}
