#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;
bool fail = false;
bool success = false;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

#define PLATFORM_COUNT 28

struct GameState {
    Entity player;
    Entity platform[PLATFORM_COUNT];
    Entity platform2[PLATFORM_COUNT];
};

GameState state;

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_image_free(image);
    return textureID;
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Physics!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    state.player.width = 0.95f;
    state.player.position = glm::vec3(0, 4, 0);
    state.player.acceleration = glm::vec3(0, -0.81f, 0);
    state.player.textureID = LoadTexture("playerShip1_blue.png");
    
    GLuint tileTextureID = LoadTexture("platformPack_tile041.png");
    GLuint tileTextureID2 = LoadTexture("platformPack_tile036.png");
    
    state.platform[0].textureID = tileTextureID;
    state.platform[0].position = glm::vec3(0, -3.25f, 0);
    
    state.platform[1].textureID = tileTextureID;
    state.platform[1].position = glm::vec3(-1, -3.25f, 0);
    
    state.platform[2].textureID = tileTextureID;
    state.platform[2].position = glm::vec3(1, -3.25f, 0);
    
    state.platform2[0].textureID = tileTextureID2;
    state.platform2[0].position = glm::vec3(3, -3.25f, 0);
    
    state.platform[4].textureID = tileTextureID;
    state.platform[4].position = glm::vec3(1, -2.25f, 0);
    
    state.platform2[1].textureID = tileTextureID2;
    state.platform2[1].position = glm::vec3(4, -3.25f, 0);
    
    state.platform[6].textureID = tileTextureID;
    state.platform[6].position = glm::vec3(2, -3.25f, 0);
    
    state.platform[7].textureID = tileTextureID;
    state.platform[7].position = glm::vec3(5, -3.25f, 0);
    
    state.platform[8].textureID = tileTextureID;
    state.platform[8].position = glm::vec3(5, -2.25f, 0);
    
    state.platform[9].textureID = tileTextureID;
    state.platform[9].position = glm::vec3(5, -1.25f, 0);
    
    state.platform[10].textureID = tileTextureID;
    state.platform[10].position = glm::vec3(5, -.25f, 0);
    
    state.platform[11].textureID = tileTextureID;
    state.platform[11].position = glm::vec3(5, 0.75f, 0);
    
    state.platform[12].textureID = tileTextureID;
    state.platform[12].position = glm::vec3(5, 1.75f, 0);
    
    state.platform[13].textureID = tileTextureID;
    state.platform[13].position = glm::vec3(5, 2.75f, 0);
    
    state.platform[14].textureID = tileTextureID;
    state.platform[14].position = glm::vec3(5, 3.75f, 0);
    
    state.platform[15].textureID = tileTextureID;
    state.platform[15].position = glm::vec3(-2, -3.25f, 0);
    
    state.platform[16].textureID = tileTextureID;
    state.platform[16].position = glm::vec3(-3, -3.25f, 0);
    
    state.platform[17].textureID = tileTextureID;
    state.platform[17].position = glm::vec3(-4, -3.25f, 0);
    
    state.platform[18].textureID = tileTextureID;
    state.platform[18].position = glm::vec3(-5, -3.25f, 0);
    
    state.platform[19].textureID = tileTextureID;
    state.platform[19].position = glm::vec3(-5, -2.25f, 0);
    
    state.platform[20].textureID = tileTextureID;
    state.platform[20].position = glm::vec3(-5,-1.25f, 0);
    
    state.platform[21].textureID = tileTextureID;
    state.platform[21].position = glm::vec3(-5, -.25f, 0);
    
    state.platform[22].textureID = tileTextureID;
    state.platform[22].position = glm::vec3(-5, .75f, 0);
    
    state.platform[23].textureID = tileTextureID;
    state.platform[23].position = glm::vec3(-5, 1.75f, 0);
    
    state.platform[24].textureID = tileTextureID;
    state.platform[24].position = glm::vec3(-5, 2.75f, 0);
    
    state.platform[25].textureID = tileTextureID;
    state.platform[25].position = glm::vec3(-5, 3.75f, 0);
    
    state.platform[26].textureID = tileTextureID;
    state.platform[26].position = glm::vec3(4, 0.75f, 0);
    
    state.platform[27].textureID = tileTextureID;
    state.platform[27].position = glm::vec3(3, 0.75f, 0);
    

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
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                

        }
    }
    
    state.player.velocity.x = 0;
    // Check for pressed/held keys below
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_A])
    {
        state.player.velocity.x = -3.0f;
    }
    else if  (keys[SDL_SCANCODE_D])
    {
        state.player.velocity.x = 3.0f;
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
        // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
        state.player.Update(FIXED_TIMESTEP, state.platform, PLATFORM_COUNT);
        
        deltaTime -= FIXED_TIMESTEP;
    }
    
    
    accumulator = deltaTime;
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    state.player.Render(&program);
    
    for (int i = 0; i < PLATFORM_COUNT; i++){
        state.platform[i].Render(&program);
        state.platform2[i].Render(&program);
    }
    
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
