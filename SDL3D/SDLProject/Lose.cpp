#include "Lose.h"

void Lose::Initialize() {
    state.nextLevel = -1;
}
void Lose::Update(float deltaTime) {

    // Check for pressed/held keys below
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_RETURN])
    {
        state.nextLevel = 0;
    }
}
void Lose::Render(ShaderProgram* program) {
    GLuint fontTextureID;
    fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Tag!", 1.0f, -0.5f, glm::vec3(2, 1, -5));
    Util::DrawText(program, fontTextureID, "Press Enter to Restart", 0.9f, -0.5f, glm::vec3(-2, 0, -5));

}
