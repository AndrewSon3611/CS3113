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

SDL_Window* displayWindow;
bool gameIsRunning = true;

//texture 1
ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

//texture 2
ShaderProgram program2;
glm::mat4 viewMatrix2, modelMatrix2, projectionMatrix2;

//texture 3
ShaderProgram program3;
glm::mat4 viewMatrix3, modelMatrix3, projectionMatrix3;
float player_x = 0;
float player_y = 0;
float player_a = 0;

GLuint playerTextureID;
GLuint playerTextureID2;
GLuint playerTextureID3;

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
    displayWindow = SDL_CreateWindow("Textured", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    //texture 1
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    playerTextureID = LoadTexture("Pixil1.png");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    //texture 2
    program2.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    playerTextureID2 = LoadTexture("Pixil1.png");
    
    viewMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::mat4(1.0f);
    projectionMatrix2 = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program2.SetProjectionMatrix(projectionMatrix2);
    program2.SetViewMatrix(viewMatrix2);
    program2.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program2.programID);
    
    //texture 3
    program3.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    playerTextureID3 = LoadTexture("Pixil1.png");
    
    viewMatrix3 = glm::mat4(1.0f);
    modelMatrix3 = glm::mat4(1.0f);
    projectionMatrix3 = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program3.SetProjectionMatrix(projectionMatrix3);
    program3.SetViewMatrix(viewMatrix3);
    program3.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program3.programID);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

float lastTicks = 0;
float rotate_z = 0;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    player_x += 1.0f * deltaTime;
    
    player_y += 1.0f * deltaTime;
    
    player_a += 1.0f * deltaTime;
    
    rotate_z += 45.0 * deltaTime;
    
    modelMatrix = glm::mat4(1.0f);
    //modelMatrix = glm::translate(modelMatrix, glm::vec3(player_x, 0.0f, 0.0f));
    
    //texture 1
    modelMatrix = glm::rotate(modelMatrix,
                              glm::radians(rotate_z),
                              glm::vec3(0.0f, 0.0f, 1.0f));
    
    //texture 2
    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(-player_y, 0.0f, 0.0f));
    
    //texture 3
    modelMatrix3 = glm::mat4(1.0f);
    modelMatrix3 = glm::translate(modelMatrix3, glm::vec3(player_a, 0.0f, 0.0f));
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //texture 1
    program.SetModelMatrix(modelMatrix);
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, playerTextureID);
    
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);
    
    //texture 2
    program2.SetModelMatrix(modelMatrix2);
    
    
    float vertices2[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords2[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, playerTextureID2);
    
    glVertexAttribPointer(program2.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
    glEnableVertexAttribArray(program2.positionAttribute);
    
    glVertexAttribPointer(program2.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords2);
    glEnableVertexAttribArray(program2.texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program2.positionAttribute);
    glDisableVertexAttribArray(program2.texCoordAttribute);
    //texture 3
    program3.SetModelMatrix(modelMatrix3);
    
    
    float vertices3[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords3[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    //glBindTexture(GL_TEXTURE_2D, playerTextureID3);
    
    glVertexAttribPointer(program3.positionAttribute, 2, GL_FLOAT, false, 0, vertices3);
    glEnableVertexAttribArray(program3.positionAttribute);
    
    glVertexAttribPointer(program3.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords3);
    glEnableVertexAttribArray(program3.texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program3.positionAttribute);
    glDisableVertexAttribArray(program3.texCoordAttribute);
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
