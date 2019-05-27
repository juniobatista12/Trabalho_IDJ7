#include "InputManager.h"

InputManager& InputManager::GetInstance(){
    static InputManager tmp;
    return tmp;
}

InputManager::InputManager(){
    quitRequested = false;
    for(int i = 0; i < 6; i++){
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager(){

}

void InputManager::Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            quitRequested = true;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
        }
        else if(event.type == SDL_MOUSEBUTTONUP){
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
        }
        else if(event.type == SDL_KEYDOWN){
            if(event.key.repeat != 1){
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
        }
        else if(event.type == SDL_KEYUP){
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key){
    return (keyUpdate[key] == updateCounter)&&keyState[key];
}

bool InputManager::KeyRelease(int key){
    return (keyUpdate[key] == updateCounter)&&!keyState[key];
}

bool InputManager::IsKeyDown(int key){
    return keyState[key];
}

bool InputManager::MousePress(int key){
    return (mouseUpdate[key] == updateCounter)&&mouseState[key];
}

bool InputManager::MouseRelease(int key){
    return (mouseUpdate[key] == updateCounter)&&!mouseState[key];
}

bool InputManager::IsMouseDown(int key){
    return mouseState[key];
}

bool InputManager::QuitRequested(){
    return quitRequested;
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}