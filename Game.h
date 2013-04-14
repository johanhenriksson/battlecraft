#ifndef GAME_H
#define GAME_H
#include "battlecraft.h"
#include "Component.h"
#include "Camera.h"
#include "Chunk.h"
#include "Tileset.h"
#include "VoxelShader.h"
#include "LineShader.h"
#include "Boundbox.h"

class Game
{
public:
    Game(int w, int h);

    bool init();
    void quit();
    void run();
    void keyUp(int key);
    void keyDown(int key);
    void mouseUp(int x, int y, int button);
    void mouseDown(int x, int y, int button);

protected:

    void draw();
    void update(float dt);

private:
    int width;
    int height;
    bool running;
    int window;

    Camera* camera;
    
    Chunk* chunk;
    Tileset* tileset;
    VoxelShader* shader;

    Boundbox* bounds;
    LineShader* linesh;
};

#endif