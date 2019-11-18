//
//  gameover.cpp
//  SDLProject
//
//  Created by Andrew Son on 11/17/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "gameover.h"


void gameover::Initialize() {
    state.nextLevel = -1;
}

void gameover::Update(float deltaTime) {

    // Check for pressed/held keys below
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_RETURN])
    {
        state.nextLevel = 0;
    }

}
void gameover::Render(ShaderProgram* program) {
    GLuint fontTextureID;
    fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Game Over!", 1.0f, -0.5f, glm::vec3(1.5, -3, 0));
    Util::DrawText(program, fontTextureID, "Press Enter to return", 0.9f, -0.5f, glm::vec3(1.0, -5, 0));
    Util::DrawText(program, fontTextureID, "to main menu", 1.0f, -0.5f, glm::vec3(1.0, -6, 0));

}
