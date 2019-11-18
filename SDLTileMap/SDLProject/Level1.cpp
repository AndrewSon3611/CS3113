#include "Level1.h"
#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 8
unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void Level1::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(5, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.nextLevel = -1;
    
    
}
void Level1::Update(float deltaTime) {
    state.player.Update(deltaTime, state.player, state.enemies, NULL, 0, state.map, ENEMY_COUNT);
    
    
    if (state.player.life == 0){
        state.nextLevel = 4;
    }
    
    if (state.player.position.y < -10) {
        state.player.life -= 1;
        state.nextLevel = 1;
    }
    if (state.player.position.x > 18){
        state.nextLevel = 2;
    }
    

}
void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    GLuint fontTextureID;
    fontTextureID = Util::LoadTexture("font1.png");
    //Util::DrawText(program, fontTextureID, "Reach the Light!", 1.0f, -0.5f, glm::vec3(1.5, -3, 0));
    Util::DrawText(program, fontTextureID, "Level 1", 0.9f, -0.5f, glm::vec3(1.0, -3, 0));
}
