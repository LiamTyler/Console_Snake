#include "include/window_manager.h"
#include <string>

using namespace std;

WindowManager::WindowManager() : WindowManager(24, 100, 12) {}

WindowManager::WindowManager(int height, int width, double fps) {
    screen_w_ = width;
    screen_h_ = height;
    lborder_ = 0;
    rborder_ = width;
    tborder_ = 2;  // Leave room for the header
    bborder_ = height;
    fps_ = fps;
    initscr();
    window_ = newwin(height, width, 0, 0);
    InitColors();
    box(window_, 0, 0);  // Make the outline

    wrefresh(window_); // update the terminal screen
    noecho(); // disable echoing of characters on the screen
    keypad(window_, TRUE ); // enable keyboard input for the window.
    nodelay(window_, TRUE);
    curs_set(0); // hide the default screen cursor.

    mvwhline(window_, 2, 1, ACS_S9, screen_w_ - 2); // Make header box
}

WindowManager::~WindowManager() {
    delwin(window_);
    endwin();
}

/* I didn't like the default colors, how they weren't pure.
 * So, i redefined all the colors to be pure.
 */
void WindowManager::InitColors() {
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 1000, 0);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    for (int i = 0; i < 8; i++) {
        // init_pair(i, i, COLOR_BLACK);
    }
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Make the default background black, and foreground green
    wbkgd(window_, COLOR_PAIR(2));
}

// Pause the game until the user presses 'p'
void WindowManager::Pause() {
    while (wgetch(window_) != 'p');
}

// Change the color of whatever you print until 'StopColor' is called.
void WindowManager::StartColor(unsigned color) {
    // use given color as foreground color,
    // and use black as background
    init_pair(color, color, COLOR_BLACK);
    wattron(window_, COLOR_PAIR(color) | A_BOLD);
}

// Stops whatever color you started earlier
void WindowManager::StopColor(unsigned color) {
    wattroff(window_, COLOR_PAIR(color) | A_BOLD);
}

// Display a single character on the screen at column X, row Y
void WindowManager::PrintChar(char ch, int x, int y) {
    mvwaddch(window_, y, x, ch);
}

// Overwrite the character on the screen at column X, row Y with a space
void WindowManager::ClearChar(int x, int y) {
    mvwaddch(window_, y, x, ' ');
}

// Display a single character on the screen at column X, row Y
void WindowManager::PrintString(string s, int x, int y) {
    wmove(window_, y, x);
    wprintw(window_, "%s", s.c_str());
}

// Return whatever character is on the screen at row Y, col X
char WindowManager::GetChar(int x, int y) {
    return mvwinch(window_, y, x) & A_CHARTEXT;
}

void WindowManager::ClearScreen() {
    wclear(window_);
}

// Get the key code of a key pressed (if any)
int WindowManager::GetInput() {
    return wgetch(window_);
}

// Start the frame timer
void WindowManager::StartFrame() {
    start_ = chrono::steady_clock::now();
}

// Given that the timer was started with 'StartFrame', this is sort of 'pause'
// a frame until it reaches however much time was supposed to pass
// I.e., if a game runs at 10 frames per second (fps), it will pause it until
// the current frame has been running for 1/10th of a second.
// Note: This isn't actually a super accurate/good way to do this
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
