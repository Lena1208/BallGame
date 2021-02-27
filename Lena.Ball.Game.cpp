#include "TXLib.h"
#include "math.h"

struct Box
{
    int x1;
    int y1;
    int x2;
    int y2;
    COLORREF color;
    void box()
    {
        txSetColor(color, 5);
        txRectangle(x1, y1, x2, y2);
    }
};

struct Ball
{
    int x;
    int y;
    int r;
    int Vx;
    int Vy;
    COLORREF ccolor;
    COLORREF bcolor;
    struct Ball move_ball(struct Box m)
    {
        x = x + Vx;
        y = y + Vy;
        if(y + r + Vy >= (m.y2 - 5))
        {
            y = m.y2 - r - 5;
            Vy *= -1;
        }
        if(x + r + Vx >= (m.x2 - 5))
        {
            x = m.x2 - r - 5;
            Vx *= -1;
        }
        if(y - r <= m.y1 + 5)
        {
            y = m.y1 + r + 5;
            Vy *= -1;
        }
        if(x - r <= m.x1 + 5)
        {
            x = m.x1 + r + 5;
            Vx *= -1;
        }
    }
    void draw()
    {
        txSetColor(ccolor, 5);
        txSetFillColor(bcolor);
        txCircle(x, y, r);
    }
};

void boom(struct Ball *a, struct Ball *b);
bool collision(struct Ball f, struct Ball e);
void boom_cor(struct Ball *a, int *x, int *y, int *r);
bool collision_cor(struct Ball f, int x, int y, int r);
void draw_corvet(int x, int y, int dir, COLORREF ccolor, COLORREF bcolor);

int main()
{
    int xmax = 1500;
    int ymax = 750;
    txCreateWindow(xmax, ymax);
    int x1 = 800;
    int y1 = 375;
    int r1 = 40;
    int x2 = 700;
    int y2 = 375;
    int r2 = 40;
    int dir1 = -1;
    int dir2 = 1;

    Ball a = {250, 20, 20, 0, 20, TX_LIGHTRED, TX_YELLOW};
    Ball b = {1480, 20, 20, 20, 20, TX_LIGHTRED, TX_YELLOW};
    Ball c = {400, 500, 20, 20, 0, TX_LIGHTRED, TX_YELLOW};
    Ball d = {750, 20, 20, 0, 20, TX_LIGHTRED, TX_YELLOW};
    Ball e = {1250, 700, 20, 0, 20, TX_LIGHTRED, TX_YELLOW};
    Ball f = {1000, 250, 20, 20, 0, TX_LIGHTRED, TX_YELLOW};
    Ball g = {200, 730, 20, 20, 20, TX_LIGHTRED, TX_YELLOW};

    Box one = {0, 0, xmax, ymax, TX_WHITE};

    while(!GetAsyncKeyState(32))
    {
        txSetColor(TX_MAGENTA, 3);
        txSelectFont ("Comic Sans MS", 50, 15, true, false, true, false, 0);
        txTextOut (660, 50, "Правила");
        txTextOut (640, 300, "Управление");
        txSetColor(TX_LIGHTGRAY, 3);
        txTextOut (480, 600, "Нажмите пробел чтобы продолжить");
        txSelectFont ("Comic Sans MS", 40, 10, false, true, false, false, 0);
        txTextOut (600, 150, "Избегайте комет, передвигаясь.");
        txTextOut (550, 200, "Тот кто первый столкнётся с кометой - проиграл.");
        txTextOut (680, 400, "Корабль с");
        txSetColor(TX_ORANGE, 3);
        txTextOut (600, 450, "Рыжим щитом - клавиши w,a,s,d");
        txSetColor(TX_CYAN, 3);
        txTextOut (600, 500, "Бирюзовым щитом - стрелочки");
        draw_corvet(600, 75, 1, TX_GRAY, TX_DARKGRAY);
        draw_corvet(880, 330, -1, TX_LIGHTGRAY, TX_GRAY);

    }

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txClear();
        txSetFillColor(TX_BLACK);
        one.box();

        a.move_ball(one);
        b.move_ball(one);
        c.move_ball(one);
        d.move_ball(one);
        e.move_ball(one);
        f.move_ball(one);
        g.move_ball(one);
        a.draw();
        b.draw();
        c.draw();
        d.draw();
        e.draw();
        f.draw();
        g.draw();
        boom(&a, &b);
        boom(&b, &c);
        boom(&c, &d);
        boom(&d, &a);
        boom(&a, &c);
        boom(&d, &b);

        txSetFillColor(TX_BLACK);
        txSetColor(TX_ORANGE, 3);
        txCircle(x1, y1, r1);
        draw_corvet(x1, y1, dir1, TX_LIGHTGRAY, TX_GRAY);

        if(GetAsyncKeyState(65))
        {
            x1 = x1 - 20;
            dir1 = -1;
        }
            if(GetAsyncKeyState(68))
        {
            x1 = x1 + 20;
            dir1 = 1;
        }
            if(GetAsyncKeyState(87))
        {
            y1 = y1 - 20;
        }
            if(GetAsyncKeyState(83))
        {
            y1 = y1 + 20;
        }

        txSetColor(TX_CYAN, 3);
        txSetFillColor(TX_BLACK);
        txCircle(x2, y2, r2);
        draw_corvet(x2, y2, dir2, TX_GRAY, TX_DARKGRAY);

        if(GetAsyncKeyState(VK_LEFT))
        {
            x2 = x2 - 20;
            dir2 = -1;
        }
            if(GetAsyncKeyState(VK_RIGHT))
        {
            x2 = x2 + 20;
            dir2 = 1;
        }
            if(GetAsyncKeyState(VK_UP))
        {
            y2 = y2 - 20;
        }
            if(GetAsyncKeyState(VK_DOWN))
        {
            y2 = y2 + 20;
        }

        if(((collision_cor(a, x1, y1, r1))||(collision_cor(b, x1, y1, r1))||(collision_cor(c, x1, y1, r1))||(collision_cor(d, x1, y1, r1))||
           (collision_cor(e, x1, y1, r1))||(collision_cor(f, x1, y1, r1))||(collision_cor(g, x1, y1, r1))) == 1)
        {
            txSetFillColor(TX_BLACK);
            txClear();
            txSetColor(TX_CYAN, 3);
            txSelectFont ("Comic Sans MS", 100, 30, true, true, false, false, 0);
            txTextOut (400, 250, "Корабль с  бирюзовым щитом победил");
            txSetColor(TX_WHITE, 3);
            txTextOut (650, 100, "Game Over");
            txTextOut (430, 600, "Нажмите ESC чтобы закончить");
            system("pause");
        }
        if(((collision_cor(a, x2, y2, r2))||(collision_cor(b, x2, y2, r2))||(collision_cor(c, x2, y2, r2))||(collision_cor(d, x2, y2, r2))||
           (collision_cor(e, x2, y2, r2))||(collision_cor(f, x2, y2, r2))||(collision_cor(g, x2, y2, r2))) == 1)
        {
            txSetFillColor(TX_BLACK);
            txClear();
            txSetColor(TX_ORANGE, 3);
            txSelectFont ("Comic Sans MS", 100, 30, true, true, false, false, 0);
            txTextOut (430, 250, "Корабль с рыжим щитом победил");
            txSetColor(TX_WHITE, 3);
            txTextOut (650, 100, "Game Over");
            txTextOut (430, 600, "Нажмите ESC чтобы закончить");
            txSleep(1000);
            system("pause");
        }

        txSleep(50);
    }

    return 0;
}

void boom(struct Ball *a, struct Ball *b)
{
    if (collision(*a, *b) == 0)
    {
        return;
    }
    double V1 = (*a).Vx;
    double V2 = a -> Vy;
    (*a).Vx = (*b).Vx;
    a -> Vy = b -> Vy;
    (*b).Vx = V1;
    b -> Vy = V2;
}

bool collision(struct Ball f, struct Ball e)
{
   double r = sqrt((f.x - e.x)*(f.x - e.x) + (f.y - e.y)*(f.y - e.y));

    if(r < f.r + e.r)
    {
         return 1;
    }
    else
    {
        return 0;
    }
}

void boom_cor(struct Ball *a, int *x, int *y, int *r)
{
    if (collision_cor(*a, *x, *y, *r) == 0)
    {
        return;
    }
}

bool collision_cor(struct Ball f, int x, int y, int r)
{
   double rt = sqrt((f.x - x)*(f.x - x) + (f.y - y)*(f.y - y));

    if(rt < f.r + r)
    {
         return 1;
    }
    else
    {
        return 0;
    }
}

void draw_corvet(int x, int y, int dir, COLORREF bcolor, COLORREF ccolor)
{
    txSetColor(ccolor, 3);
    txSetFillColor(bcolor);
    POINT corvet[17] = {{x - int(30*dir), y - 20}, {x - int(30*dir), y - 10}, {x - int(20*dir), y - 10}, {x - int(20*dir), y - 5},
                        {x - int(25*dir), y - 5},  {x - int(25*dir), y + 5},  {x - int(20*dir), y + 5},  {x - int(20*dir), y + 10},
                        {x - int(30*dir), y + 10}, {x - int(30*dir), y + 20}, {x, y + 20},      {x + int(10*dir), y + 10},
                        {x + int(20*dir), y + 10}, {x + int(30*dir), y}, {x + int(20*dir), y - 10}, {x + int(10*dir), y - 10}, {x, y - 20}};

    txPolygon (corvet, 17);
}
