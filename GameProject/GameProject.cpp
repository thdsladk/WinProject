
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef unsigned int UINT;
using namespace std;

// 전역변수 
bool GameEnd = 1;

const UINT MaxLines = 100;

//클래스 선언
class Manager {};  
class Canvas {}; 
class Card {};
class PlayerFactory {};

//구조체 
struct POST
{
    UINT post_x = 0;
    UINT post_Y = 0;
};

enum class CardName
{
    Jester = 0,
    Dalmuti,
    Archbishop,
    EarlMarshal,
    Baroness,
    Abbess,
    Knight,
    Seamstress,
    Mason,
    Cook,
    Shepherdess,
    Flush,
    Peasant
};



int main()
{
    Manager A; 
    string B;
    vector<int> C;
    sort(B.begin(),B.end());


    while (1)
    {
    
        if (GameEnd== 0) { break; }
    }


}


class Canvas
{
public:
    Canvas(UINT MaxW , UINT MaxH):Max_x(MaxW),Max_y(MaxH) {}
    ~Canvas() {}
    Canvas(const Canvas&) {}


    void Draw(UINT x, UINT y,string val ) {}
    void Clear(string val = "  ") {}
    void Print(const char* title =  "<MY Canvas>" ) {}


private:
    string line[MaxLines];
    UINT mPost_x=0;
    UINT mPost_Y=0;
    UINT Max_x=0;
    UINT Max_y=0;

};
//Width , Height
Canvas::Canvas(UINT MaxW, UINT MaxH)
{
    for (UINT y; y < MaxH; y++)
    {
        if (y == 0||y==29)
        {
            for (UINT x; x < 70; x++)
            {
                
            }
        }
        else if(y==12)
            for (UINT x; x < 70; x++)
            {

            }
        
    }
}

void Canvas::Draw(UINT x, UINT y, string val)
{
    if (x < Max_x && y < Max_y) line[y].replace(x * 2, 2, val);

}

void Canvas::Clear(string val = "  ")
{
    for (int y = 0; y < Max_y; y++)
    {
        for (int x = 0; x < Max_x; x++)
        {
            Canvas::Draw(x, y, val);
        }
    }
    
}

void Canvas::Print(const char* title = "<My Canvas>")
{
    system("cls");
    cout << title << endl;
    for (int y = 0; y < Max_y; y++)
    {
        cout << line[y] << endl;
        cout << endl;
    }
}




class Manager
{
public:

    Manager() {}

    void Paint() {}
    void Init() {}
    void Restart() {}
    void GameEnd() {}

    ~Manager() {}
    Manager(const Manager&) {}


private:

    Card* pUser[8] = { nullptr ,}; 
    Canvas* pPaint = nullptr;
    PlayerFactory* pFactory = nullptr;
};

void Manager::Paint()
{

}

void Manager::Init()
{

}

void Manager::Restart()
{

}

void Manager::GameEnd()
{

}





class Card                          // Center Card Pack 입니다 .
{
public:
    Card() {}



    virtual ~Card() {}
    Card(const Card&) {}

private:
    UINT mMainCard[13] = { 2,1,2,3,4,5,6,7,8,9,10,11,12 };
    UINT mTrashCard[13] = { 0, };
    

};

class PlayerCard :public Card     //Player hand card pack 입니다 .
{
public:
    PlayerCard() {}

    ~PlayerCard() {}
    PlayerCard(const PlayerCard&) {}

private:
    UINT mHandCard[12] = { 0, };
};






/*
0000000001111111111222222222233333333334444444444555555555566666666667777777777888888888899999999999-
01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓      00
┃                                                                                                  ┃      01
┃                                                                                                  ┃      02
┃                                                                                                  ┃      03
┃                                                                                                  ┃      04
┃                                     ┏━━━━┓  ┏━━━━┓                                               ┃      05
┃                                     ┃ 12 ┃  ┃ CA ┃                                               ┃      06
┃                                     ┃  1 ┃  ┃ RD ┃                                               ┃      07
┃                                     ┗━━━━┛  ┗━━━━┛                                               ┃      08
┃                                                                                                  ┃      09
┃                                                                                                  ┃      10
┃                                                                                                  ┃      11
┃     ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓          ┃      12
┃     ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃          ┃      13
┃     ┃  D ┃ ┃  2 ┃ ┃  3 ┃ ┃  4 ┃ ┃  5 ┃ ┃  6 ┃ ┃  7 ┃ ┃  8 ┃ ┃  9 ┃ ┃ 10 ┃ ┃ 11 ┃ ┃ 12 ┃          ┃      14
┃     ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛          ┃      15
┃     ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓          ┃      16
┃     ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃ ┃ 12 ┃          ┃      17
┃     ┃  D ┃ ┃  2 ┃ ┃  3 ┃ ┃  4 ┃ ┃  5 ┃ ┃  6 ┃ ┃  7 ┃ ┃  8 ┃ ┃  9 ┃ ┃ 10 ┃ ┃ 11 ┃ ┃ 12 ┃          ┃      18
┃     ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛          ┃      19
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛      20

*/

//  ─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼ ━ ┃            ┏ ┓ ┛ ┗ ┣ ┳ ┫ ┻ ╋ ┠ ┯ ┨ ┷ ┿
// ┝ ┰ ┥ ┸ ╂ ┒      ┑ ┚ ┙ ┖ ┕ ┎ ┍ ┞ ┟ ┡ ┢ ┦ ┧ ┩ ┪ ┭ ┮ ┱ ┲ ┵ ┶ ┹ ┺ ┽ ┾ ╀ ╁ ╃ ╄ ╅ ╆ ╇ ╈ ╉ ╊
//ⓐ ⓑ ⓒ ⓓ ⓔ ⓕ ⓖ ⓗ ⓘ ⓙ ⓚ ⓛ ⓜ ⓝ ⓞ ⓟ ⓠ ⓡ ⓢ ⓣ ⓤ ⓥ ⓦ ⓧ ⓨ ⓩ