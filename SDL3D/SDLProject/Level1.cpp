#include "Level1.h"

#define OBJECT_COUNT (84*4)+6
#define ENEMY_COUNT 5

float cubeVertices[] = {
   -0.5,  0.5, -0.5, -0.5,  0.5,  0.5,  0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,  0.5, -0.5,  0.5, -0.5, -0.5,  0.5,
     0.5, -0.5, -0.5, -0.5, -0.5,  0.5, -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,  0.5,
    -0.5,  0.5, -0.5, -0.5, -0.5,  0.5, -0.5,  0.5,  0.5,
     0.5,  0.5,  0.5,  0.5, -0.5,  0.5,  0.5, -0.5, -0.5,
     0.5,  0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
     0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5,  0.5, -0.5
};

float cubeTexCoords[] = {
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f
};


void Level1::Initialize() {

        state.nextLevel = -1;

        
        GLuint floorTextureID = Util::LoadTexture("100_1180_seamless.JPG");
        Mesh *floorMesh = new Mesh();
        floorMesh->LoadOBJ("cube.obj");
        
        GLuint crateTextureID = Util::LoadTexture("crate1_diffuse.png");
        Mesh *crateMesh = new Mesh();
        crateMesh->LoadOBJ("cube.obj");
        
    //    state.objects[0].position = glm::vec3(-2,0,-100);
    //    state.objects[0].acceleration = glm::vec3(0,0,1);
    //    state.objects[0].vertices = cubeVertices;
    //    state.objects[0].velocity = glm::vec3(0,0,10); //constant speed towards you
    //    state.objects[0].texCoords = cubeTexCoords;
    //    state.objects[0].numVertices = 36;
    //    state.objects[0].textureID = objectTexture;
    //
        
        state.objects[0].position = glm::vec3(0,0,0);
        state.objects[0].scale = glm::vec3(20,1,20);
        state.objects[0].rotation = glm::vec3(0,0,0);
        state.objects[0].acceleration = glm::vec3(0,0,0);
        //state.objects[0].vertices = cubeVertices;
        state.objects[0].velocity = glm::vec3(0,0,0); //constant speed towards you
        state.objects[0].entityType = FLOOR;
        state.objects[0].textureID = floorTextureID;
        state.objects[0].mesh = floorMesh;
        
        state.objects[1].position = glm::vec3(2, 1, -5);
        state.objects[1].scale = glm::vec3(1,1,1);
        state.objects[1].acceleration = glm::vec3(0, 0, 0);
        state.objects[1].rotation = glm::vec3(0, 0, 0);
        state.objects[1].textureID = crateTextureID;
        state.objects[1].mesh = crateMesh;
        state.objects[1].entityType = BOX;
        
        state.objects[2].position = glm::vec3(2, 1, -3);
        state.objects[2].scale = glm::vec3(1,1,1);
        state.objects[2].acceleration = glm::vec3(0, 0, 0);
        state.objects[2].rotation = glm::vec3(0, 0, 0);
        state.objects[2].textureID = crateTextureID;
        state.objects[2].mesh = crateMesh;
        state.objects[2].entityType = BOX;
        
        state.objects[3].position = glm::vec3(-7, 1, 5);
        state.objects[3].scale = glm::vec3(1,1,1);
        state.objects[3].acceleration = glm::vec3(0, 0, 0);
        state.objects[3].rotation = glm::vec3(0, 0, 0);
        state.objects[3].textureID = crateTextureID;
        state.objects[3].mesh = crateMesh;
        state.objects[3].entityType = BOX;
        
        state.objects[4].position = glm::vec3(-9, 1, -5);
        state.objects[4].scale = glm::vec3(1,1,1);
        state.objects[4].acceleration = glm::vec3(0, 0, 0);
        state.objects[4].rotation = glm::vec3(0, 0, 0);
        state.objects[4].textureID = crateTextureID;
        state.objects[4].mesh = crateMesh;
        state.objects[4].entityType = BOX;
        
        state.objects[5].position = glm::vec3(2, 2, -3);
        state.objects[5].scale = glm::vec3(1,1,1);
        state.objects[5].acceleration = glm::vec3(0, 0, 0);
        state.objects[5].rotation = glm::vec3(0, 0, 0);
        state.objects[5].textureID = crateTextureID;
        state.objects[5].mesh = crateMesh;
        state.objects[5].entityType = BOX;
        
        int count = 6;
        for (int i = -10; i <= 10; i++){
            for (int j = 0; j < 4; j++){
                state.objects[count].scale = glm::vec3(1,1,1);
                state.objects[count].position = glm::vec3(i,j+1,-10);
                state.objects[count].textureID = crateTextureID;
                state.objects[count].mesh = crateMesh;
                state.objects[count].entityType = BOX;
                count+=1;
            }
        }
        for (int i = -10; i <= 10; i++){
            for (int j = 0; j < 4; j++){
                state.objects[count].scale = glm::vec3(1,1,1);
                state.objects[count].position = glm::vec3(i,j+1,10);
                state.objects[count].textureID = crateTextureID;
                state.objects[count].mesh = crateMesh;
                state.objects[count].entityType = BOX;
                count+=1;
            }
        }
        for (int z = -10; z <= 10; z++){
            for (int j = 0; j < 4; j++){
                state.objects[count].scale = glm::vec3(1,1,1);
                state.objects[count].position = glm::vec3(-10,j+1,z);
                state.objects[count].textureID = crateTextureID;
                state.objects[count].mesh = crateMesh;
                state.objects[count].entityType = BOX;
                count+=1;
            }
        }
        for (int z = -10; z <= 10; z++){
            for (int j = 0; j < 4; j++){
                state.objects[count].scale = glm::vec3(1,1,1);
                state.objects[count].position = glm::vec3(10,j+1,z);
                state.objects[count].textureID = crateTextureID;
                state.objects[count].mesh = crateMesh;
                state.objects[count].entityType = BOX;
                count+=1;
            }
        }
        

        GLuint enemyTextureID = Util::LoadTexture("sans.png");
        for (int i = 0; i < ENEMY_COUNT; i++) {
             state.enemies[i].billboard = true;
             state.enemies[i].textureID = enemyTextureID;
             state.enemies[i].position = glm::vec3(rand() % 20 - 10, 1, rand() % 20 - 10);
            state.enemies[i].rotation = glm::vec3(0, 0, 0);
            state.enemies[i].entityType = ENEMY;
            state.enemies[i].acceleration = glm::vec3(0, 0, 0);
            state.enemies[i].aiState = IDLE;
            state.enemies[i].aiType = WALKER;
        }
    
}
void Level1::Update(float deltaTime) {
    state.player.Update(deltaTime, state.player, state.enemies, NULL, 0, 0);
    for (int i = 0; i < ENEMY_COUNT; i ++){
        state.objects[i].Update(deltaTime, state.player, state.enemies, state.objects, OBJECT_COUNT, ENEMY_COUNT);
    }
}

void Level1::Render(ShaderProgram* program) {
    //state.map->Render(program);
    state.player.Render(program);
    for (int i = 0; i < OBJECT_COUNT; i++) {
            state.objects[i].Render(program);
        
    }
    for (int i = 0; i < ENEMY_COUNT; i++) {
            state.enemies[i].Render(program);
        
    }

}

