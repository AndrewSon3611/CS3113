#include "Menu.h"

void Menu::Initialize() {
    state.nextLevel = -1;
}
void Menu::Update(float deltaTime) {

    // Check for pressed/held keys below
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_RETURN])
    {
        state.nextLevel = 1;
    }
}
void Menu::Render(ShaderProgram* program) {
    GLuint fontTextureID;
    fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Tag!", 1.0f, -0.5f, glm::vec3(2, 1, -5));
    Util::DrawText(program, fontTextureID, "Press Enter to start", 0.9f, -0.5f, glm::vec3(-2, 0, -5));

}
