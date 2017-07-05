#include "include/window.h"
#include "include/snake.h"
#include "include/fruit.h"
#include <vector>

using namespace std;


int main() {
    WindowManager w;
    Snake s;
    Fruit* fruit = nullptr;
    bool gameover = false;
    int score = 0;
    int x, y;
    do {
        x = rand() % w.ScreenWidth();
        y = rand() % w.ScreenHeight();
    } while (w.GetChar(x, y) != ' ');

    fruit = new Fruit('F', 10, x, y, 0, 0);
    fruit->Draw(w);

    while(!gameover) { 
        w.StartFrame();

        fruit->Update(w);
        gameover = s.Update(w);
        if (fruit->X() == s.X() && fruit->Y() == s.Y()) {
            score += fruit->GetValue();
            // fruit->Destroy(w);
            delete fruit;

            int x, y;
            do {
                x = rand() % w.ScreenWidth();
                y = rand() % w.ScreenHeight();
            } while (w.GetChar(x, y) != ' ');

            fruit = new Fruit('F', 10, x, y, 0, 0);
            fruit->Draw(w);
            s.Draw(w);
        }

        w.EndFrame();
    }

    return 0;
}

