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
#include <SDL_mixer.h>
#include "Util.h"
#include "Entity.h"
#include "Map.h"
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "menu.h"
#include "gameover.h"
#include "win.h"

Mix_Music* music;
Mix_Chunk* bounce;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;


Scene *currentScene;
Scene *sceneList[6];

void SwitchToScene(Scene *scene) {
 currentScene = scene;
 currentScene->Initialize();
}


GLuint fontTextureID;


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Platformer!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("amazingplan.mp3");
    Mix_PlayMusic(music, -1);
    
    bounce = Mix_LoadWAV("bounce.wav");
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    //glViewport(0, 0, 1280, 960);
    
    program.Load("shaders/vertex_lit.glsl", "shaders/fragment_lit.glsl");
        
    fontTextureID = Util::LoadTexture("font1.png");

    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    sceneList[0] = new menu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
    sceneList[4] = new gameover();
    sceneList[5] = new win();
    
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
                        currentScene-> state.player.Jump();
                        Mix_PlayChannel(-1, bounce, 0);
                    
                }
                break;
        }
    }
    
    currentScene-> state.player.velocity.x = 0;
    
    // Check for pressed/held keys below
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_A])
    {
        currentScene->state.player.velocity.x = -3.0f;
    }
    else if  (keys[SDL_SCANCODE_D])
    {
       currentScene-> state.player.velocity.x = 3.0f;
    }
}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void Update() {
    
    currentScene->Update(FIXED_TIMESTEP);
    
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }
    
    while (deltaTime >= FIXED_TIMESTEP) {
        
        
        deltaTime -= FIXED_TIMESTEP;
    }
    
    
    accumulator = deltaTime;
    
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1.0f);
    if (currentScene-> state.player.position.x > 5){
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene-> state.player.position.x, 3.75, 0));
    } else {
     viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
    }
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    program.SetViewMatrix(viewMatrix);
    
    
    
    currentScene->Render(&program);
    
    program.SetLightPosition(currentScene->state.player.position);
    program.SetLightPosition2(glm::vec3(19,-5,0));
    
    //Util::DrawText(&program, fontTextureID, "Reach The Light!", 1.0f, -0.5f, glm::vec3(3, -2, 0));
    
    
    
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(bounce);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        if (currentScene->state.nextLevel >= 0) SwitchToScene(sceneList[currentScene->state.nextLevel]);
        
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
