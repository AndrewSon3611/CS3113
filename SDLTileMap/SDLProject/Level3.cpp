#include "Level3.h"
#define LEVEL3_WIDTH 20
#define LEVEL3_HEIGHT 8
unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 2, 2,
 3, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2
};

void Level3::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(5, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.nextLevel = -1;
    
    GLuint evilTextureID = Util::LoadTexture("evil.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID=evilTextureID;
    state.enemies[0].isStatic = false;
    state.enemies[0].position = glm::vec3(18, -3.5f, 0);
    state.enemies[0].acceleration = glm::vec3(0,-9.81f, 0);
    state.enemies[0].aiState = IDLE;
    state.enemies[0].aiType = WALKER;
    
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID=evilTextureID;
    state.enemies[1].isStatic = false;
    state.enemies[1].position = glm::vec3(10, -3.5f, 0);
    state.enemies[1].acceleration = glm::vec3(0, -9.81f, 0);
    state.enemies[1].aiState = IDLE;
    state.enemies[1].aiType = WALKER;
    
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID=evilTextureID;
    state.enemies[2].isStatic = false;
    state.enemies[2].position = glm::vec3(6, -3.5f, 0);
    state.enemies[2].position = glm::vec3(0, -9.81f, 0);
    state.enemies[2].aiState = IDLE;
    state.enemies[2].aiType = WALKER;
    
}
void Level3::Update(float deltaTime) {
    state.player.Update(deltaTime, state.player, state.enemies, NULL, 0, state.map, ENEMY_COUNT);
    
    for (int i = 0; i < ENEMY_COUNT; i++){
        state.enemies[i].Update(deltaTime, state.player, state.enemies, NULL, 0, state.map, ENEMY_COUNT);
        }
        
    if (state.player.position.x > 19){
        
        state.player.isStatic = true;
    }

}
void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        state.enemies[i].Render(program);
    }
    
}

