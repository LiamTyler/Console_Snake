#include "include/window.h"
#include <string>

using namespace std;

WindowManager::WindowManager() : WindowManager(24, 80, 8) {}

WindowManager::WindowManager(int height, int width, double fps) {
    screen_w_ = width;
    screen_h_ = height;
    lborder_ = 0;
    rborder_ = width;
    tborder_ = 2;
    bborder_ = height;
    fps_ = fps;
    initscr();
    window_ = newwin(height, width, 0, 0);
    box(window_, 0, 0);

    wrefresh(window_); // update the terminal screen
    noecho(); // disable echoing of characters on the screen
    keypad(window_, TRUE ); // enable keyboard input for the window.
    nodelay(window_, TRUE);
    curs_set(0); // hide the default screen cursor.
}

WindowManager::~WindowManager() {
    delwin(window_);
    endwin();
}

void WindowManager::PrintChar(char ch, int x, int y) {
    mvwaddch(window_, y, x, ch);
}

void WindowManager::ClearChar(int x, int y) {
    mvwaddch(window_, y, x, ' ');
}

void WindowManager::PrintString(string s, int x, int y) {
    wmove(window_, y, x);
    wprintw(window_, "%s", s.c_str());
}

int WindowManager::GetChar(int x, int y) {
    return mvwinch(window_, y, x) & A_CHARTEXT;
}

void WindowManager::ClearScreen() {
    wclear(window_);
}

int WindowManager::GetInput() {
    return wgetch(window_);
}

void WindowManager::StartFrame() {
    start_ = chrono::steady_clock::now();
}

void WindowManager::EndFrame() {
    wrefresh(window_);
    fflush(stdout);
    double time_taken = chrono::duration_cast<chrono::microseconds>
        (chrono::steady_clock::now() - start_).count() / 1000000.0;
    while (time_taken < 1.0 / fps_) {
        time_taken = chrono::duration_cast<chrono::microseconds>
            (chrono::steady_clock::now() - start_).count() / 1000000.0;
    }
}
