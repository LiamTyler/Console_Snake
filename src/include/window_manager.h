#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <ncurses.h>
#include <chrono>
#include <thread>

class WindowManager {
    public:
        // Initialization
        WindowManager();
        WindowManager(int height, int width, double fps);
        ~WindowManager();
        void InitColors();

        // Manipulating the Screen
        void PrintChar(char ch, int x, int y);
        void ClearChar(int x, int y);
        void PrintString(std::string s, int x, int y);
        char GetChar(int x, int y);
        void ClearScreen();
        int GetInput();  // returns the key code of a key pressed
        void StartFrame();
        void EndFrame();
        void Pause();
        void StartColor(unsigned color);
        void StopColor(unsigned color);

        WINDOW* GetWindow() { return window_; }
        int ScreenWidth() { return screen_w_; }
        int ScreenHeight() { return screen_h_; }
        // void Resize(int w, int h);
        void FPS(double FPS) { fps_ = FPS; }
        double FPS() { return fps_; }
        int LBorder() { return lborder_; }
        int RBorder() { return rborder_; }
        int TBorder() { return tborder_; }
        int BBorder() { return bborder_; }

    private:
        int screen_w_;
        int screen_h_;
        int lborder_;
        int rborder_;
        int tborder_;
        int bborder_;
        WINDOW* window_;
        double fps_;

        std::chrono::steady_clock::time_point start_;
};

#endif  // WINDOW_MANAGER_H_
