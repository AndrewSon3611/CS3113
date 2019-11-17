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

#include "Map.h"

enum  EntityType { PLAYER, PLATFORM, COIN, ENEMY };

enum AIState{ IDLE, WALKING };

enum AIType { WALKER };

class Entity {
public:
    
    EntityType entityType;
    
    AIState aiState;
    AIType aiType;
    
    bool isStatic;
    bool isActive;
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    

    
    float width;
    float height;
    
    float speed;
    
    GLuint textureID;
    
    Entity();
    
    bool CheckCollision(Entity other);
    
    void CheckCollisionsX(Map *map);
    void CheckCollisionsY(Map *map);
    
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckCollisionsY(Entity *objects, int objectCount);
    
    
    void Update(float deltaTime, Entity player, Entity *objects, Entity *enemies, int objectCount, Map *map, int enemycount);
    
    void Render(ShaderProgram *program);
    
    void AIwalker(Entity player);
    void AIupdate(Entity player);
    
    
    void Jump();
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
    int lifecount;
};



