#include "include/window.h"
#include "include/snake.h"

using namespace std;

int main() {
    WindowManager w;
    Snake s;

    bool gameover = false;
    // get the input
    while(!gameover) { 
        w.StartFrame();
        gameover = s.Update(w);
        w.EndFrame();
    }

    return 0;
}

