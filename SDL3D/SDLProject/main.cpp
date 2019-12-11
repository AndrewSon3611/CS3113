#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Util.h"
#include "Entity.h"
#include <SDL_mixer.h>
#include "scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Lose.h"

Mix_Music* music;
//Mix_Chunk* touch;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

GLuint fontTextureID;

Scene* currentScene;
Scene* sceneList[3];

void SwitchToScene(Scene* scene) {
    currentScene = scene;
    currentScene->Initialize();
}


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Tag!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("edm.mp3");
    Mix_PlayMusic(music, -1);
    //touch = Mix_LoadWAV("touch.wav");

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 1280, 720);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    fontTextureID = Util::LoadTexture("font1.png");
    
        viewMatrix = glm::mat4(1.0f);
        modelMatrix = glm::mat4(1.0f);
        //projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
        projectionMatrix = glm::perspective(45.0f, 1.777f, 0.1f, 100.0f);

        program.SetProjectionMatrix(projectionMatrix);
        program.SetViewMatrix(viewMatrix);
        program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

        glUseProgram(program.programID);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    sceneList[0] = new Menu();
    sceneList[1] = new Level1();
    sceneList[2] = new Lose();
    SwitchToScene(sceneList[0]);
    }
void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        // Some sort of action
                        break;
                }
                break;
        }
    }
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_A]){
        currentScene->state.player.rotation.y += 1.0f;

    }
    else if(keys[SDL_SCANCODE_D]){
        currentScene->state.player.rotation.y -= 1.0f;
    }
    currentScene->state.player.velocity.x = 0;
    currentScene->state.player.velocity.z = 0;
    
    if(keys[SDL_SCANCODE_W]){
        currentScene->state.player.velocity.z = cos(glm::radians(currentScene->state.player.rotation.y)) * -2.0f;
        currentScene->state.player.velocity.x = sin(glm::radians(currentScene->state.player.rotation.y)) * -2.0f;
    }
    else if (keys[SDL_SCANCODE_S]){
        currentScene->state.player.velocity.z = cos(glm::radians(currentScene->state.player.rotation.y)) * 2.0f;
        currentScene->state.player.velocity.x = sin(glm::radians(currentScene->state.player.rotation.y)) * 2.0f;
    }
}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    deltaTime += accumulator;
    
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }
    
    while (deltaTime >= FIXED_TIMESTEP) {
        currentScene->Update(FIXED_TIMESTEP);
          
        deltaTime -= FIXED_TIMESTEP;
    }
    
    accumulator = deltaTime;
    
    viewMatrix = glm::mat4(1.0);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(currentScene->state.player.rotation.y), glm::vec3(0,-1.0f,0));
    viewMatrix = glm::translate(viewMatrix, -(currentScene->state.player.position));
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.SetViewMatrix(viewMatrix);
    
    currentScene->Render(&program);
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    Mix_FreeMusic(music);
    //Mix_FreeChunk(touch);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
        if (currentScene->state.nextLevel >= 0) SwitchToScene(sceneList[currentScene->state.nextLevel]);
    }
    
    Shutdown();
    return 0;
}

