#include "include/window.h"

using namespace std;

WindowManager::WindowManager() : WindowManager(24, 100, 5) {}

WindowManager::WindowManager(int width, int height, double fps) {
    screen_w_ = width;
    screen_h_ = height;
    fps_ = fps;
    initscr();
    window_ = newwin(width, height, 0, 0);
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
    start_ = chrono::system_clock::now();
}

void WindowManager::EndFrame() {
    wrefresh(window_);
    fflush(stdout);
    chrono::duration<double> time_taken = chrono::system_clock::now() - start_;
    while (time_taken.count() < 1.0 / fps_) {
        time_taken = chrono::system_clock::now() - start_;
    }
}
