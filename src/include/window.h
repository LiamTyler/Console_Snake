#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <ncurses.h>
#include <chrono>
#include <thread>

class WindowManager {
    public:
        // Initialization
        WindowManager();
        WindowManager(int width, int height, double fps);
        ~WindowManager();

        // Manipulating the Screen
        void PrintChar(char ch, int x, int y);
        void ClearChar(int x, int y);
        void PrintString(std::string s, int x, int y);
        int GetChar(int x, int y);
        void ClearScreen();
        int GetInput();  // returns the key code of a key pressed
        void StartFrame();
        void EndFrame();

        int ScreenWidth() { return screen_w_; }
        int ScreenHeight() { return screen_h_; }
        // void Resize(int w, int h);
        void FPS(double FPS) { fps_ = FPS; }
        double FPS() { return fps_; }

    private:
        int screen_w_;
        int screen_h_;
        WINDOW* window_;
        double fps_;

        std::chrono::system_clock::time_point start_;
};

#endif  // WINDOW_MANAGER_H_
