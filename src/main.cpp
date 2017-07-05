#include "include/window.h"
#include "include/snake.h"

using namespace std;

int main() {
    WindowManager w;
    Snake s;

    int ch;
    int vx, vy;

    // get the input
    while(( ch = w.GetInput()) != 'q'){ 
        w.StartFrame();

        w.PrintChar(' ', s.X(), s.Y());
        // right pad with spaces to make the items appear with even width.
        if (ch != ERR) {
            w.GetVelocities(ch, vx, vy);
            s.VX(vx);
            s.VY(vy);
        }
        s.Update();
        w.PrintChar(s.GetSymbol(), s.X(), s.Y());
        w.EndFrame();
    }

    return 0;
}

