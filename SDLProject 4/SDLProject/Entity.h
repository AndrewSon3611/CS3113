#pragma once
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


enum EntityType{PLAYER, PLATFORM, COIN, ENEMY };

class Entity {
public:
    
    EntityType entityType;
    bool isActive;
    bool isStatic;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    
    float width;
    float height;
    float speed;
    
    GLuint textureID;
    
    Entity();
    
    bool CheckCollision(Entity other);
    
    void Update(float deltaTime, Entity *objects, int objectCount);
    void Render(ShaderProgram *program);
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckCollisionsY(Entity *objects, int objectCount);
    
    void jump();
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
};


