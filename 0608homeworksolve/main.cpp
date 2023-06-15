#include "stdafx.h"

#define COLUMN 6
#define ROW 29
#define CHECKLINE 3
#define DROPTIME 0.08f
#define SPAWNTIME 0.4f

void Start();
bool Update();
void CheckNote(int x);
void Render();

struct note
{
    int x;
    int y;
};

std::vector<note> gameNote;

Timer timer;
float noteDropCount = 0;
float noteSpawnCount = 0;
int score = 100;

int main()
{
    Start();

    while (Update())
    {
        Render();
    }

    return 0;
}

void Start()
{
    system("title RhythmGame");
    system("mode con:cols=80 lines=30");

    {
        HANDLE hConsole;
        CONSOLE_CURSOR_INFO ConsoleCursor;

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        ConsoleCursor.bVisible = 0;
        ConsoleCursor.dwSize = 1;

        SetConsoleCursorInfo(hConsole, &ConsoleCursor);
    }

    cout << "*****리듬 게임!!*****" << endl;

    system("pause");
    system("cls");
}

bool Update()
{
    timer.Update();

    noteDropCount += timer.GetDeltaTimeSEC();
    noteSpawnCount += timer.GetDeltaTimeSEC();

    if (GetAsyncKeyState('Q')) CheckNote(1); //키 눌림 체크
    if (GetAsyncKeyState('W')) CheckNote(2);
    if (GetAsyncKeyState('E')) CheckNote(3);
    if (GetAsyncKeyState('R')) CheckNote(4);

    if (noteSpawnCount >= SPAWNTIME)
    {
        note temp;

        temp.x = Math::Random(1, COLUMN - 2);
        temp.y = 0;

        gameNote.push_back(temp);

        noteSpawnCount = 0.0f;
    }

    if (noteDropCount >= DROPTIME)
    {
        for (auto& note : gameNote)
        {
            note.y++;
        }

        for (auto iter = gameNote.begin(); iter != gameNote.end();)
        {
            if (iter->y >= ROW - 1)
            {
                iter = gameNote.erase(iter);
                score -= 10;

                if (score == 0)
                    exit(1);
            }
            else
                iter++;
        }

        noteDropCount = 0.0f;
    }

    return true;
}

void CheckNote(int x)
{
    for (auto iter = gameNote.begin(); iter != gameNote.end();)
    {
        if (iter->x == x && iter->y >= ROW - CHECKLINE - 1)
        {
            iter = gameNote.erase(iter);
            score += 10;
        }
        else
            iter++;
    }
}

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x * 2;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Render()
{
    system("cls");

    for (int i = 0; i < ROW; i++)
    {
        gotoxy(0, i);
        cout << "※";
        gotoxy(COLUMN - 1, i);
        cout << "※";
    }

    for (int i = 0; i < COLUMN; i++)
    {
        gotoxy(i, ROW - 1);
        cout << "※";
    }

    for (int i = 0; i < CHECKLINE; i++)
    {
        gotoxy(0, ROW - i - 2);
        cout << "▶";
        gotoxy(COLUMN - 1, ROW - i - 2);
        cout << "◀";
    }

    {
        gotoxy(1, ROW);
        cout << " Q W E R";
    }

    {
        for (const auto& note : gameNote)
        {
            gotoxy(note.x, note.y);
            cout << "♪";
        }
    }

    {
        gotoxy(10, 5);
        cout << "score : " << score;
    }
}
