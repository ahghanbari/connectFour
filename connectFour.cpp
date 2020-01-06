/*
		*** Arash PH ***
*/

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

int arr[8][8];
HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);

void welcome();
void slide();
void menu();
void giveNameColor(string &p1, string &p2, int &kc1, int &kc2, string &kcb1, string &kcb2);
void display(string p1, string p2, int kc1, int kc2, int star, int kcStar); //kcstar for player color
int givemove(int c, int dp);                                                // c for column dp for definition player and fill arr
bool findwinner(int nm);                                                    //nm for number of player
void newgame();
string CodeMoveToBinary(int m); //m for move
bool stop(string F[]);          //F string for information move, color & ...
void savegame(string F[]);      //F string for information move, color & ...
void loadgame();                // load information from file
void BintoIntColor(char c2, char c3, int &kc, string &kcb);
int BintoIntMove(char m1, char m2, char m3);

int main() { welcome(); }

void welcome()
{
    cout << "\n\n\n\n\n\t\t\t\t\t  Please maximize window ...\n\n\t\t\t\t\t  By press super key & up\n\n\n\n\n"
         << "\t\t\t      Please set the resolution to 1366*768 or near it.\n\n\n\t\t\t\t\t\tIf you want:\n\n\n"
         << "\t\t\t\t\t  1.Close the program\n\n\t\t\t\t\t  2.Set resolution to 1366*768\n\n\t\t\t\t\t  3.Run program again :)\n\n\n\n\n\n";
    system("PAUSE");

    slide();
	
    menu();
}

void slide()
{
    int k[6] = {10, 9, 12, 13, 11, 14};
    for (int i = 0; i < 6; i++)
    {
        system("CLS");
        SetConsoleTextAttribute(hC, k[i]);
        cout << "\n\n\n\n\n\n\n\n\n"
             << "\t O     O     O        O                                                \n"
             << "\t  O   O O   O   OOOO  O                        OOOO         O          \n"
             << "\t  O   O O   O   O  O  O  OOOO   OOO   OOOOOOO  O  O        OOO   OOO   \n"
             << "\t   O O   O O    OOOO  O  O     O   O  O  O  O  OOOO         O   O   O  \n"
             << "\t   O O   O O    O     O  O     O   O  O  O  O  O            O   O   O  \n"
             << "\t    O     O     OOOO  O  OOOO   OOO   O  O  O  O000         OO   OOO   \n";

        SetConsoleTextAttribute(hC, k[i]);
        cout << "\n\n\n\n\n\n\n\n"
             << "\t\t\t\t"
             << "    O                                                         \n"
             << "\t\t\t\t"
             << "   O      OOOO0                                               \n"
             << "\t\t\t\t"
             << "  O      O         OOOO   OOOOOO  OOOOOO  OOOOO   OOOOO    O  \n"
             << "\t\t\t\t"
             << " O  O    O        O    O  O    O  O    O  O   O  O        OOO \n"
             << "\t\t\t\t"
             << "OOOOOO   O        O    O  O    O  O    O  OOOOO  O         O  \n"
             << "\t\t\t\t"
             << "    O    O        O    O  O    O  O    O  O      O         O  \n"
             << "\t\t\t\t"
             << "    O     OOOOO    OOOO   O    O  O    O  OOOOO   OOOOO    OO \n";

        SetConsoleTextAttribute(hC, 8);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\nArash_PH";
        Sleep(180);
    }
    system("CLS");
}

void menu()
{
    int breaker = 0;
    while (true)
    {
        system("CLS");
        SetConsoleTextAttribute(hC, 14);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
             << "\t\t\t\t--------------------------------------------\n"
             << "\t\t\t\t|                                          |\n"
             << "\t\t\t\t|                1. New Game               |\n"
             << "\t\t\t\t|                                          |\n"
             << "\t\t\t\t|                2. Load Game              |\n"
             << "\t\t\t\t| (from file \"game.txt\" in this directory) |\n"
             << "\t\t\t\t|                                          |\n"
             << "\t\t\t\t|                3. about                  |\n"
             << "\t\t\t\t|                                          |\n"
             << "\t\t\t\t|                4. Goodbye :)             |\n"
             << "\t\t\t\t|                                          |\n"
             << "\t\t\t\t--------------------------------------------\n\n";

        SetConsoleTextAttribute(hC, 12);
        cout << "\t\t\t\t\t\tPlease choose: ";
        string menu;
        getline(cin, menu);

        if (menu.size() != 1)
        {
            cout << "\n\n\t\t\t\t\tThe input is invalid ...\n\n"
                 << "\t\t\t\t\t\tPlease Try again : ";
            Sleep(1800);
            continue;
        }

        switch (menu[0])
        {
        case '1':
            newgame();
            breaker = 1;
            break;

        case '2':
            loadgame();
            breaker = 1;
            break;

        case '3':
            slide();
            SetConsoleTextAttribute(hC, 15);
            cout << "\nConnect Four\n\n"
                 << "Connect Four (also known as Captain's Mistress, Four Up, Plot Four, Find Four, Four in a Row, Four in a Line,\n"
                 << "Drop Four, and Gravitrips (in Soviet Union)) is a two-player connection game in which the players first choose\n"
                 << "A color and then take turns dropping one colored disc from the top into a seven-column, six-row vertically\n"
                 << "suspended grid. The pieces fall straight down, occupying the lowest available space within the column.\n"
                 << "The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's\n"
                 << "own discs. Connect Four is a solved game. The first player can always win by playing the right moves.\n"
                 << "The game was first sold under the Connect Four trademark by Milton Bradley in February 1974.";
            SetConsoleTextAttribute(hC, 8);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nArash_PH\n\n";
            SetConsoleTextAttribute(hC, 15);
            system("PAUSE");
            break;

        case '4':
            system("CLS");
            SetConsoleTextAttribute(hC, 12);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                 << "\t\t\t\t\t    Goodbye my friend";
            SetConsoleTextAttribute(hC, 8);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nArash_PH";
            Sleep(1800);
            breaker = 1;
            break;

        default:
            cout << "\n\n\t\t\t\t\tThe input is invalid ...\n\n"
                 << "\t\t\t\t\t\tPlease Try again : ";
            Sleep(1300);
            continue;
        }
        if (breaker == 1)
            break;
    }
}

void giveNameColor(string &p1, string &p2, int &kc1, int &kc2, string &kcb1, string &kcb2)
{
    string c1, c2;

    while (true)
    {
        system("CLS");
        SetConsoleTextAttribute(hC, 15);
        cout << "\nPlease enter name of first player: ";
        getline(cin, p1);
        if (p1 == "")
        {
            SetConsoleTextAttribute(hC, 12);
            cout << "\nYou have not entered anything ...\n\ntry again...";
            SetConsoleTextAttribute(hC, 15);
            Sleep(2200);
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "\nPlease choose color of " << p1 << "  (pink=1 yellow=2 green=3 blue=4): ";
        getline(cin, c1);

        if (c1 == "1" || c1 == "2" || c1 == "3" || c1 == "4")
            break;
        else
            cout << "\nThe entered number is invalid ...\n\n"
                 << "Please Try again : \n";
    }

    switch (c1[0])
    {
    case '1':
        kc1 = 221;
        kcb1 = "BBB";
        break;

    case '2':
        kc1 = 238;
        kcb1 = "BBA";
        break;

    case '3':
        kc1 = 170;
        kcb1 = "BAB";
        break;

    case '4':
        kc1 = 153;
        kcb1 = "BAA";
        break;
    }

    while (true)
    {
        system("CLS");
        SetConsoleTextAttribute(hC, 15);
        cout << "\nPlease enter name of second player: ";
        getline(cin, p2);
        if (p1 == p2)
        {
            SetConsoleTextAttribute(hC, 12);
            cout << "\nThis name used by player one...";
            SetConsoleTextAttribute(hC, 15);
            Sleep(1800);
            continue;
        }
        if (p2 == "")
        {
            SetConsoleTextAttribute(hC, 12);
            cout << "\nYou have not entered anything ...\n\ntry again...";
            SetConsoleTextAttribute(hC, 15);
            Sleep(2200);
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "\nPlease choose color of " << p2 << "  (";
        if (c1[0] != '1')
            cout << "pink=1 ";
        if (c1[0] != '2')
            cout << "yellow=2 ";
        if (c1[0] != '3')
            cout << "green=3 ";
        if (c1[0] != '4')
            cout << "blue=4";
        cout << "): ";
        getline(cin, c2);

        if ((c2 == "1" || c2 == "2" || c2 == "3" || c2 == "4") && (c1[0] != c2[0]))
            break;
        else
        {
            if (c1[0] == c2[0])
                cout << "\nThe entered number used by first player : " << p1 << endl
                     << endl;

            else
                cout << "\nThe entered number is invalid ...\n\n"
                     << "Please Try again : \n";
        }
    }

    switch (c2[0])
    {
    case '1':
        kc2 = 221;
        kcb2 = "BBB";
        break;

    case '2':
        kc2 = 238;
        kcb2 = "BBA";
        break;

    case '3':
        kc2 = 170;
        kcb2 = "BAB";
        break;

    case '4':
        kc2 = 153;
        kcb2 = "BAA";
        break;
    }
}

void display(string p1, string p2, int kc1, int kc2, int star, int kcStar) //kcstar for player color
{
    system("CLS");
    SetConsoleTextAttribute(hC, 15);
    cout << "\n\t\t\tPlayer 1 : " << p1 << "  ";
    SetConsoleTextAttribute(hC, kc1);
    cout << "xx";

    SetConsoleTextAttribute(hC, 15);
    cout << "\t\t\t    Player 2 : " << p2 << "  ";
    SetConsoleTextAttribute(hC, kc2);
    cout << "xx\n\n\n\n\n\n\n";

    SetConsoleTextAttribute(hC, 15);

    for (int i = 7; i > -1; i--)
    {
        cout << "\t\t\t\t    -----------------------------------------\n";
        for (int big = 0; big < 2; big++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (j == 0)
                    cout << "\t\t\t\t    ";
                cout << "|";
                if (arr[i][j] == 0)
                    cout << "    ";
                else if (arr[i][j] == 1)
                {
                    SetConsoleTextAttribute(hC, kc1);
                    cout << "xxxx";
                    SetConsoleTextAttribute(hC, 15);
                }
                else if (arr[i][j] == 2)
                {
                    SetConsoleTextAttribute(hC, kc2);
                    cout << "xxxx";
                    SetConsoleTextAttribute(hC, 15);
                }
            }
            cout << "|\n";
        }
    }
    cout << "\t\t\t\t    -----------------------------------------\n"
         << "\t\t\t\t    ";
    for (int i = 1; i < 9; i++)
    {
        cout << "| " << i << " ";
        if (star == i)
        {
            SetConsoleTextAttribute(hC, kcStar);
            cout << "*";
            SetConsoleTextAttribute(hC, 15);
        }
        else
            cout << " ";
    }
    cout << "|";
}

int givemove(int c, int dp) // c for column dp for definition player and fill arr
{
    int r; // for row
    c--;
    for (r = 0; r < 8; r++)
        if (arr[r][c] == 0)
        {
            arr[r][c] = dp;
            break;
        }
    return r;
}

bool findwinner(int nm) //nm for number of player
{
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            if (arr[x][y] == nm)
            {
                if (x < 5)
                    if ((arr[x + 1][y] == nm) && (arr[x + 2][y] == nm) && (arr[x + 3][y] == nm))
                        return true;

                if (y < 5)
                    if ((arr[x][y + 1] == nm) && (arr[x][y + 2] == nm) && (arr[x][y + 3] == nm))
                        return true;

                if ((x < 5) && (y < 5))
                    if ((arr[x + 1][y + 1] == nm) && (arr[x + 2][y + 2] == nm) && (arr[x + 3][y + 3] == nm))
                        return true;

                if ((x > 2) && (y < 5))
                    if ((arr[x - 1][y + 1] == nm) && (arr[x - 2][y + 2] == nm) && (arr[x - 3][y + 3] == nm))
                        return true;
            }
    return false;
}

void newgame()
{
    string p1, p2;   // p for name
    int kc1, kc2;    //code of color 1 and 2
    int m1, m2;      // for move of player
    string sm1, sm2; // string of move of player
    string F[66], kcb1, kcb2, s;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            arr[i][j] = 0;

    giveNameColor(p1, p2, kc1, kc2, kcb1, kcb2);
    F[0] = p1;
    F[1] = p2;

    int i; //for verify equal
    for (i = 0; i < 64; i += 2)
    {
        while (true) // while for if one player want to stop, do not lose his movement
        {
            while (true) // while for give correct number
            {
                system("CLS");
                display(p1, p2, kc1, kc2, m2, kc2);
                cout << "\n\n\n\n\t\t\t\t\t   play " << p1 << "( 0 to stop ): ";
                getline(cin, sm1);
                if (sm1.size() != 1)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                    Sleep(1000);
                    continue;
                }
                m1 = (int)sm1[0] - '0';
                if (m1 < 0 || m1 > 8)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                    Sleep(1000);
                    continue;
                }
                break; // means number is correct and need to break while
            }

            if (m1 == 0)
                if (stop(F) == 0)
                    return;
                else
                    continue;
            if (givemove(m1, 1) == 8)
            {
                SetConsoleTextAttribute(hC, 12);
                cout << "\n\n\t\t\t\t\t    This column is full";
                Sleep(1000);
                continue;
            }
            break;
        }

        if (findwinner(1) == true)
        {
            while (true)
            {
                display(p1, p2, kc1, kc2, 0, 15);
                cout << "\n\n\t\t\t\t\t\t " << p1 << " Wins ...\n";
                SetConsoleTextAttribute(hC, 11);
                cout << "\n\t*****\t\t\t\t\t congratulate :)\t\t\t\t*****\n\n\t\t\t\t\t  ";
                SetConsoleTextAttribute(hC, 15);
                system("PAUSE");
                menu();
                return;
            }
        }

        F[i + 2] = "BBA" + CodeMoveToBinary(m1) + kcb1;

        while (true) // while for if one player want to stop, do not lose her movement
        {
            while (true) // while for give correct number
            {
                system("CLS");
                display(p1, p2, kc1, kc2, m1, kc1);
                cout << "\n\n\n\n\t\t\t\t\t   play " << p2 << "( 0 to stop ): ";
                getline(cin, sm2);
                if (sm2.size() != 1)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                    Sleep(1000);
                    continue;
                }
                m2 = (int)sm2[0] - '0';
                if (m2 < 0 || m2 > 8)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                    Sleep(1000);
                    continue;
                }
                break; // means number is correct and need to break while
            }

            if (m2 == 0)
                if (stop(F) == 0)
                    return;
                else
                    continue;
            if (givemove(m2, 2) == 8)
            {
                SetConsoleTextAttribute(hC, 12);
                cout << "\n\n\t\t\t\t\t    This column is full";
                Sleep(1000);
                continue;
            }
            break;
        }

        if (findwinner(2) == true)
        {
            display(p1, p2, kc1, kc2, 0, 15);
            cout << "\n\n\t\t\t\t\t\t " << p2 << " Wins ...\n";
            SetConsoleTextAttribute(hC, 11);
            cout << "\n\t*****\t\t\t\t\t congratulate :)\t\t\t\t*****\n\n\t\t\t\t\t  ";
            SetConsoleTextAttribute(hC, 15);
            system("PAUSE");
            menu();
            return;
        }

        F[i + 3] = "BAB" + CodeMoveToBinary(m2) + kcb2;
    }

    if (i = 64)
    {
        display(p1, p2, kc1, kc2, 0, 15);
        cout << "\n\n\t\t\t\t\t    no winner no loser ...\n\n\t\t\t\t\t  ";
        system("PAUSE");
        menu();
        return;
    }
}

string CodeMoveToBinary(int m) //m for move and mb for move binary
{
    switch (m)
    {
    case 1:
        return "BBB";

    case 2:
        return "BBA";

    case 3:
        return "BAB";

    case 4:
        return "BAA";

    case 5:
        return "ABB";

    case 6:
        return "ABA";

    case 7:
        return "AAB";

    case 8:
        return "AAA";
    }
}

bool stop(string F[])
{
    string m; // for choose menu and switch

    system("CLS");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\t\t\t\t    --------------------------------------\n"
         << "\t\t\t\t    |        1. resume game              |\n"
         << "\t\t\t\t    |        2. save game and resume     |\n"
         << "\t\t\t\t    |        3. save game and exit       |\n"
         << "\t\t\t\t    |        4. go to menu               |\n"
         << "\t\t\t\t    |        5. exit                     |\n"
         << "\t\t\t\t    --------------------------------------\n"
         << "\t\t\t\t              choose menu: ";

    getline(cin, m);

    switch (m[0])
    {
    case '1':
        return 1;

    case '2':
        if (F[3] == "")
        {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tYou must play at least two moves...";
            cout << "\n\n\n\t\t\t\tPlease play at least two moves and try again...\n\n\n\t\t\t\t";
            system("PAUSE");
            return 1;
        }
        savegame(F);
        return 1;

    case '3':
        if (F[3] == "")
        {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tYou must play at least two moves...";
            cout << "\n\n\n\t\t\t\tPlease play at least two moves and try again...\n\n\n\t\t\t\t";
            system("PAUSE");
            return 1;
        }
        savegame(F);
        menu();
        return 0;

    case '4':
        menu();
        return 0;

    case '5':
        system("CLS");
        SetConsoleTextAttribute(hC, 12);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
             << "\t\t\t\t\t    Goodbye my friend";
        SetConsoleTextAttribute(hC, 8);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nArash_PH";
        Sleep(1300);
        return 0;
    }
}

void savegame(string F[])
{
    int n = 0; // n for number of movement
    ofstream out;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (F[i][j] != 0)
                n++;

    out.open("game.txt");
    out << F[0] << endl
        << endl
        << F[1] << endl
        << endl;

    for (int i = 0; i < n; i++)
        out << F[i + 2] << endl
            << endl;

    out.close();

    system("CLS");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tThe game saved ( in \"game.txt\" ) ...";
    Sleep(1800);
}

void loadgame()
{
    string p1, p2;   // p for name
    int kc1, kc2;    //code of color 1 and 2
    string in;       // for input from file
    int m1, m2;      // for move of player
    string sm1, sm2; //string of move of player
    string F[66], kcb1, kcb2;
    ifstream inf; // input file

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            arr[i][j] = 0;

    inf.open("game.txt");

    //if ( inf.fail() )
    {
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t     The file does not exist ...\n\n"
             << "\n\n\t\t\t\t\tPlease play first, then load game ... ";
        Sleep(2200);
        menu();
        return;
    }

    inf >> p1 >> p2;

    F[0] = p1;
    F[1] = p2;

    inf >> in;
    BintoIntColor(in[7], in[8], kc1, kcb1);
    m1 = BintoIntMove(in[3], in[4], in[5]);
    givemove(m1, 1);
    F[2] = "BBA" + CodeMoveToBinary(m1) + kcb1;

    inf >> in;
    BintoIntColor(in[7], in[8], kc2, kcb2);
    m2 = BintoIntMove(in[3], in[4], in[5]);
    givemove(m2, 2);
    F[3] = "BAB" + CodeMoveToBinary(m2) + kcb2;

    int i = 2; // for while initial 2 because nth movement
    while (true)
    {
        inf >> in;
        i++;

        if (inf.eof() == 1)
            break;

        if (in[2] == 'A')
        {
            m1 = BintoIntMove(in[3], in[4], in[5]);
            givemove(m1, 1);
            F[i + 1] = "BBA" + CodeMoveToBinary(m1) + kcb1;
        }

        else
        {
            m2 = BintoIntMove(in[3], in[4], in[5]);
            givemove(m2, 2);
            F[i + 1] = "BAB" + CodeMoveToBinary(m2) + kcb2;
        }
    }

    inf.close();

    for (i; i <= 64; i++)
    {
        if (i % 2 == 1)
        {
            while (true) // while for if one player want to stop, do not lose her movement
            {
                while (true) // while for give correct number
                {
                    system("CLS");
                    display(p1, p2, kc1, kc2, m2, kc2);
                    cout << "\n\n\n\n\t\t\t\t\t  " << p1 << " play "
                         << "( 0 to stop ): ";
                    getline(cin, sm1);
                    if (sm1.size() != 1)
                    {
                        SetConsoleTextAttribute(hC, 12);
                        cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                        Sleep(1000);
                        continue;
                    }
                    m1 = (int)sm1[0] - '0';
                    if (m1 < 0 || m1 > 8)
                    {
                        SetConsoleTextAttribute(hC, 12);
                        cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                        Sleep(1000);
                        continue;
                    }
                    break; // means number is correct and need to break while
                }

                if (m1 == 0)
                    if (stop(F) == 0)
                        return;
                    else
                        continue;
                if (givemove(m1, 1) == 8)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t    This column is full";
                    Sleep(1000);
                    continue;
                }
                break;
            }

            if (findwinner(1) == true)
            {
                system("CLS");
                display(p1, p2, kc1, kc2, 0, 15);
                cout << "\n\n\t\t\t\t\t\t " << p1 << " Wins ...\n";
                SetConsoleTextAttribute(hC, 11);
                cout << "\n\t*****\t\t\t\t\t congratulate :)\t\t\t\t*****\n\n\t\t\t\t\t  ";
                SetConsoleTextAttribute(hC, 15);
                system("PAUSE");
                menu();
                return;
            }

            F[i + 1] = "BBA" + CodeMoveToBinary(m1) + kcb1;
        }

        if (i % 2 == 0)
        {
            while (true) // while for if one player want to stop, do not lose her movement
            {
                while (true) // while for give correct number
                {
                    system("CLS");
                    display(p1, p2, kc1, kc2, m1, kc1);
                    cout << "\n\n\n\n\t\t\t\t\t  " << p2 << " play "
                         << "( 0 to stop ): ";
                    getline(cin, sm2);
                    if (sm2.size() != 1)
                    {
                        SetConsoleTextAttribute(hC, 12);
                        cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                        Sleep(1000);
                        continue;
                    }
                    m2 = (int)sm2[0] - '0';
                    if (m2 < 0 || m2 > 8)
                    {
                        SetConsoleTextAttribute(hC, 12);
                        cout << "\n\n\t\t\t\t\t\tInvalid number ...";
                        Sleep(1000);
                        continue;
                    }
                    break; // means number is correct and need to break while
                }

                if (m2 == 0)
                    if (stop(F) == 0)
                        return;
                    else
                        continue;
                if (givemove(m2, 2) == 8)
                {
                    SetConsoleTextAttribute(hC, 12);
                    cout << "\n\n\t\t\t\t\t    This column is full";
                    Sleep(1000);
                    continue;
                }
                break;
            }

            if (findwinner(2) == true)
            {
                system("CLS");
                display(p1, p2, kc1, kc2, 0, 15);
                cout << "\n\n\t\t\t\t\t\t " << p2 << " Wins ...\n";
                SetConsoleTextAttribute(hC, 11);
                cout << "\n\t*****\t\t\t\t\t congratulate :)\t\t\t\t*****\n\n\t\t\t\t\t  ";
                SetConsoleTextAttribute(hC, 15);
                system("PAUSE");
                menu();
                return;
            }

            F[i + 1] = "BAB" + CodeMoveToBinary(m2) + kcb2;
        }
    }

    if (i = 65)
    {
        display(p1, p2, kc1, kc2, 0, 15);
        cout << "\n\n\t\t\t\t\t    no winner no loser ...\n\n\t\t\t\t\t  ";
        system("PAUSE");
        menu();
        return;
    }
}

void BintoIntColor(char c1, char c2, int &kc, string &kcb)
{
    if (c1 == 'B')
        if (c2 == 'B')
        {
            kc = 221;
            kcb = "BBB";
        }
        else
        {
            kc = 238;
            kcb = "BBA";
        }

    else if (c2 == 'B')
    {
        kc = 170;
        kcb = "BAB";
    }
    else
    {
        kc = 153;
        kcb = "BAA";
    }
}

int BintoIntMove(char m1, char m2, char m3)
{
    if (m1 == 'B')
        if (m2 == 'B')
            if (m3 == 'B')
                return 1;
            else
                return 2;
        else if (m3 == 'B')
            return 3;
        else
            return 4;

    else if (m2 == 'B')
        if (m3 == 'B')
            return 5;
        else
            return 6;
    else if (m3 == 'B')
        return 7;
    else
        return 8;
}

// Good bye my friend... @_@
// The end of code :0 (:
