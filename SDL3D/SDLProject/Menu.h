#include "scene.h"
class Menu : public Scene {

public:
    GLuint fontTextureID;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};

