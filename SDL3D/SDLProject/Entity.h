#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Mesh.h"
enum EntityType { NONE, FLOOR, BOX, ENEMY, PLAYER };
enum AIState{ IDLE, WALKING };
enum AIType { WALKER };

class Entity {
public:
    AIState aiState;
    AIType aiType;
    EntityType entityType;
    bool billboard;
    float width;
    float height;
    float depth;
    bool CheckCollision(Entity *other);
    
    bool isActive;
    bool isStatic;
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    Mesh* mesh;
    
    float *vertices;
    float *texCoords;
    int numVertices;
    
    void AIwalker(Entity player);
    void AIupdate(Entity player);
    
    GLuint textureID;
    
    Entity();
    void Update(float deltaTime, Entity *player, Entity *objects, Entity *enemies, int enemyCount, int objectCount);
    //void Update(float deltaTime);
    void Render(ShaderProgram *program);
    void DrawBillboard(ShaderProgram *program);
};


