#include "Defines.hpp"
#include "Texture2D.hpp"
#include "Shader.hpp"
#include "TexturedSurface.hpp"
#include "TexturedCube.hpp"
#include "Camera.hpp"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const GLuint map_width = 10u;
const GLuint map_height = 16u;
const GLuint map_length = 230u;

bool mass[map_width][map_height][map_length];

bool check(int x, int y, int z)
{
   if ((x < 0) || (x >= map_width) || 
	   (y < 0) || (y >= map_height) || 
	   (z < 0) || (z >= map_length)) return false;
  
   return mass[x][y][z];
}


float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLFWwindow* pWindow;

bool IsKeyPressed(const int key)
{
#ifdef DEBUG
    if( ! pWindow) return false; // Not initialized
#endif

    return glfwGetKey(pWindow, key) == GLFW_PRESS;
}

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float xoffset;
float yoffset; 

bool firstMouse = true;
bool camNeedUpdate = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camNeedUpdate = true;
}

int main()
{
    int cube_count = 0;

    // for (int x = 0; x < map_width; ++x)
    //     for (int y = 0; y < map_height; ++y)
    //         for (int z = 0; z < map_length; ++z)
    //         { //   floor generation
    //             if (/*y == 0 || */ rand() % 100 == 1)
    //             {
    //                 mass[x][y][z] = true;
    //                 cube_count++;
    //             }
                
    //         }

    std::cout << "Cube count : " << cube_count << '\n';

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Platformer3D", NULL, NULL);

    if (!pWindow)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);
    glfwSwapInterval(1);
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//  Callbacks
    glfwSetFramebufferSizeCallback(pWindow, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    glfwSetCursorPosCallback(pWindow, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback( [](GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
        {
        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                    type, severity, message );
        }, 0 );
#endif

//  Load textures
    Texture2D anim_tiles;
    bool res = anim_tiles.loadFromFile("res/textures/anim_tiles.png");

    Texture2D tFloor;
    res = tFloor.loadFromFile("res/textures/stone_block.png");
    tFloor.setRepeated(true);

    Texture2D tiles;
    res = tiles.loadFromFile("res/textures/tiles.png");

//  Shaders
    Shader default_shader;
    res = default_shader.compile("res/shaders/shader.vert", "res/shaders/shader.frag");
    default_shader.bind();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    default_shader.setUniform("projection", projection);

//  Create cube
    TexturedCube cube(&default_shader);
    cube.setTexture(&anim_tiles);
    cube.create(glm::vec3(-0.5), glm::vec3(0.5), GL_DYNAMIC_DRAW);
    cube.setAxisOfRotation(glm::vec3(0, 1, 0));
    cube.setTextureRect(glm::ivec4(0, 0, 32, 32));

    std::vector<TexturedCube> blocks(5, &default_shader);

    for (std::size_t i = 0; i < blocks.size(); ++i)
    {
        blocks[i].create(glm::vec3(-0.5), glm::vec3(0.5), GL_DYNAMIC_DRAW);
        blocks[i].setTexture(&tiles);
        blocks[i].setPosition(5, 6, 26 + i);
    }

    blocks[0].setTextureRect(glm::ivec4(32, 0, 32, 32));
    blocks[1].setTexture(&anim_tiles);
    blocks[1].setTextureRect(glm::ivec4(0, 0, 32, 32));
    blocks[2].setTextureRect(glm::ivec4(32, 0, 32, 32));
    blocks[3].setTexture(&anim_tiles);
    blocks[3].setTextureRect(glm::ivec4(0, 0, 32, 32));
    blocks[4].setTextureRect(glm::ivec4(32, 0, 32, 32));
    
//  Create surface
    TexturedSurface surface1(&default_shader);
    surface1.create(10, 75);
    surface1.setTexture(&tFloor);
    surface1.setPosition(0, 0, 0);

    TexturedSurface surface2(&default_shader);
    surface2.create(2, 75);
    surface2.setTexture(&tFloor);
    surface2.setAxisOfRotation(0, 0, 1);
    surface2.setRotation(90.0f);
    surface2.setPosition(0, -2, 0);

//  Main loop

    Camera camera;
    camera.setPosition(2, 5, 3);

    while (!glfwWindowShouldClose(pWindow))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if(IsKeyPressed(GLFW_KEY_ESCAPE)) 
        {
            glfwSetWindowShouldClose(pWindow, true);
            continue;
        }

        if (IsKeyPressed(GLFW_KEY_W))
            camera.move(Camera::FORWARD, deltaTime);

        if (IsKeyPressed(GLFW_KEY_S))
            camera.move(Camera::BACKWARD, deltaTime);

        if (IsKeyPressed(GLFW_KEY_A))
            camera.move(Camera::LEFT, deltaTime);

        if (IsKeyPressed(GLFW_KEY_D))
            camera.move(Camera::RIGHT, deltaTime);

        if (IsKeyPressed(GLFW_KEY_R))
            cube.setColor(Color::Cyan);

        if (camNeedUpdate)
        {
            camera.rotate(xoffset * 0.1f, yoffset * 0.1f);
            camNeedUpdate = false;
        }

        default_shader.bind();
        default_shader.setUniform("view", camera.getViewMatrix());
        
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        static int delay = 0;
        static int frame = 0;
        static float R = 0;

        if(++delay > 10)
        {
            delay = 0;
            ++frame;

            if(frame >= 4) frame = 0;
            blocks[1].setTextureRect(glm::ivec4(frame * 32, 0, 32, 32));
            blocks[3].setTextureRect(glm::ivec4(frame * 32, 0, 32, 32));
        }

        surface1.draw();
//        surface2.draw();
        
        // for (int x = 0; x < map_width; ++x)
        //     for (int y = 0; y < map_height; ++y)
        //         for (int z = 0; z < map_length; ++z)
        //         {
        //             if (mass[x][y][z])
        //             {
        //                 cube.setPosition(x, y, z);
        //                 cube.draw();
        //             }           
        //         }
        
        for (auto& block : blocks)
        {
            block.draw();
        }
        

        default_shader.unbind();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}