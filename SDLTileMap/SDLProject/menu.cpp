#include "menu.h"
#include "Util.h"
#define menu_WIDTH 5
#define menu_HEIGHT 8
unsigned int menu_data[] =
{
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0,
 0, 1, 1, 1, 1,
 0, 2, 2, 2, 2
};


void menu::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(menu_WIDTH, menu_HEIGHT, menu_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(3, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.nextLevel = -1;
    fontTextureID = Util::LoadTexture("font1.png");
}
void menu::Update(float deltaTime) {
    state.player.Update(deltaTime, state.player, state.enemies, NULL, 0, state.map, ENEMY_COUNT);
    
}
void menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    Util::DrawText(program, fontTextureID, "Reach The Light! Press Enter", 0.0f, -0.5f, glm::vec3(3, -2, 0));
}
