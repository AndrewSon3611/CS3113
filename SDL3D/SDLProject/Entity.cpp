#include "Entity.h"
Entity::Entity()
{
    position = glm::vec3(0);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    acceleration = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    width = 1.0f;
    height = 1.0f;
    depth = 1.0f;
    isStatic = true;
    isActive = true;
}
bool Entity::CheckCollision(Entity *other)
{
    //if (isStatic == true) return false;
    //if (isActive == false || other->isActive == false) return false;
    
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    float zdist = fabs(position.z - other->position.z) - ((depth + other->depth) / 2.0f);
    if (xdist < 0 && ydist < 0 && zdist < 0) return true;
    return false;
}
//Entity::Entity()
//{
//    position = glm::vec3(0);
//    scale = glm::vec3(1,1,1);
//}
//void Entity::forward(float speed);
void Entity::Update(float deltaTime, Entity player, Entity *enemies, Entity *objects, int objectCount, int enemyCount)
{
    if (billboard) {
        //Turn towards player
        float directionX = position.x - player.position.x;
        float directionZ = position.z - player.position.z;
        rotation.y = glm::degrees(atan2f(directionX, directionZ));
        
        velocity.z = cos(glm::radians(rotation.y)) * -1.0f;
        velocity.x = sin(glm::radians(rotation.y)) * -1.0f;
        position += velocity * deltaTime;
        return;
    }
    glm::vec3 previousPosition = position;
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    for (int i = 0; i < objectCount; i++)
    {
        if (objects[i].entityType == FLOOR) continue;
        if (CheckCollision(&objects[i])) {
            position = previousPosition;
            // We hit a wall
            break;
        }
        
    }
    
    if (this->entityType == PLAYER)
    {
        for (int i = 0; i < enemyCount; i++)
        {
            if (CheckCollision(&enemies[i])) {
                // We hit an enemy
                
                break;
            }
        }
    }
}
//void Entity::Update(float deltaTime)
//{
//    velocity += acceleration * deltaTime;
//    position += velocity * deltaTime;
////    rotation.x += 45 * deltaTime;
////    rotation.y += 45 * deltaTime;
////    rotation.z += 45 * deltaTime;
//}
void Entity::AIwalker(Entity player)
{
    switch(aiState){
        case IDLE:
            if (glm::distance(position, player.position)< 1.0){
                aiState = WALKING;
            }
            break;
        case WALKING:
            if (player.position.z > position.z){
                velocity.z = 0.7;
            } else{
            velocity.z = -0.7f;
            }
            break;
    }

}


void Entity::AIupdate(Entity player){
    switch(aiType){
        case WALKER:
            AIwalker(player);
            break;
    }
}
void Entity::Render(ShaderProgram *program) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, scale);
    
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,1,0));
    
    program->SetModelMatrix(modelMatrix);
//    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,1,0));
//    program->SetModelMatrix(modelMatrix);
//
//    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1,0,0));
//    program->SetModelMatrix(modelMatrix);
//    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,0,1));
//    program->SetModelMatrix(modelMatrix);
    
//    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
//    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
//
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 3, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (billboard) {
        DrawBillboard(program);
    } else {
        mesh->Render(program);
    }
    //mesh->Render(program);
   
}
void Entity::DrawBillboard(ShaderProgram *program) {
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
