#include "Level2.h"
#define LEVEL2_WIDTH 20
#define LEVEL2_HEIGHT 8

unsigned int level2_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 2, 2, 2, 2,
 3, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
 3, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0
};

void Level2::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(5, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.nextLevel = -1;
}
void Level2::Update(float deltaTime) {
    state.player.Update(deltaTime, state.player, state.enemies, NULL, 0, state.map, ENEMY_COUNT);
    
    if (state.player.life == 0){
        state.nextLevel = 4;
    }
    if (state.player.position.y < -10) {
        state.player.life -= 1;
        state.nextLevel = 1;
    }
    if (state.player.position.x > 19){
        state.nextLevel = 3;
    }
    
    

}
void Level2::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    
    GLuint fontTextureID;
    fontTextureID = Util::LoadTexture("font1.png");
    //Util::DrawText(program, fontTextureID, "Reach the Light!", 1.0f, -0.5f, glm::vec3(1.5, -3, 0));
    Util::DrawText(program, fontTextureID, "Level 2", 0.9f, -0.5f, glm::vec3(1.0, -3, 0));
    
}
