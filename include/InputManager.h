#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d

#if defined (_WIN64) || defined (_WIN32)
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <unordered_map>

using namespace std;

class InputManager{
public:
    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();
    static InputManager& GetInstance();
private:
    InputManager();
    ~InputManager();
    bool mouseState[6];
    int mouseUpdate[6];
    unordered_map <int, bool> keyState;
    unordered_map <int, int> keyUpdate;
    bool quitRequested;
    int updateCounter, mouseX, mouseY;
};

#endif