#include "Game.h"

Game::Game(int width, int height)
{
    this->width = width;
    this->height = height;
}

bool Game::init()
{
    if (glfwInit() != GL_TRUE)
        return false;

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwOpenWindow(this->width, this->height, 8, 8, 8, 0, 24, 0, GLFW_WINDOW);
    if (!this->window)
        return false;

    glfwSetWindowTitle("Battlecraft Editor");
    glfwSwapInterval(1);

    // OpenGL Settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    srand(11247);

    this->camera = new Camera(width, height, 90);

    shader = new VoxelShader();
    shader->compile();

    tileset = new Tileset(256);
    tileset->set(1, 250,20,20);
    tileset->set(2, 20,250,20);
    tileset->set(3, 20,20,250);
    tileset->set(4, 255,0,255);

    chunk = new Chunk(tileset, 16,16,16);

    chunk->compute();

    glErrorCheck("pre linesh compilation")

    linesh = new LineShader();
    if (!linesh->compile()) return false;

    bounds = new Boundbox(16,16,16);

    printf("A: %d, a: %d\n", 'A','a');

    return true;
}

void Game::run()
{
    double lastTime = glfwGetTime(), currentTime = 0.0;
    float delta = 0.0f;

    running = true;
    while(running && glfwGetWindowParam(GLFW_OPENED))
    {
        // Calculate delta t
        currentTime = glfwGetTime();
        delta = (float)(currentTime - lastTime);
        lastTime = currentTime;

        update(delta);
        draw();

        camera->update(delta);

        glErrorCheck("main loop");
        glfwSwapBuffers();
        glfwSleep(0.001);
    }
}

void Game::quit()
{
    glfwTerminate();
}

void Game::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->setUniformMatrix("view", camera->view());
    shader->setUniformMatrix("projection", camera->projection());

    chunk->draw(shader);

    linesh->use();
    shader->setUniformMatrix("view", camera->view());
    shader->setUniformMatrix("projection", camera->projection());
    bounds->draw(linesh);
}

void Game::update(float dt)
{
    
}

void Game::keyDown(int key)
{
    
}

void Game::keyUp(int key)
{
    switch(key)
    {
        case 'F': // place block    
        {
            int mx,my;
            glfwGetMousePos(&mx, &my);
            vec3 pos = vec3(0,0,0);
            if (camera->unProject(mx,my,&pos))
            {
                int x = (int)pos.x;
                int y = (int)pos.y;
                int z = (int)pos.z;
                chunk->set(x,y,z,4);
                chunk->compute();
            }
            return;
        }
        case 'R': // remove block    
        {
            int mx,my;
            glfwGetMousePos(&mx, &my);
            vec3 pos = vec3(0,0,0);
            if (camera->unProject(mx,my,&pos))
            {
                int x = (int)pos.x;
                int y = (int)pos.y;
                int z = (int)pos.z;
                chunk->set(x,y,z,0);
                chunk->compute();
            }
            return;
        }
    }
}

void Game::mouseDown(int x, int y, int button)
{
    
}

void Game::mouseUp(int x, int y, int button)
{

}