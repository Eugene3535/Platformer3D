#include "Defines.hpp"
#include "Texture2D.hpp"
#include "Shader.hpp"
#include "PrimitiveShapes.hpp"
#include "RenderTarget.hpp"
#include "MeshMaker.hpp"
#include "Camera.hpp"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const GLuint map_size = 20;

bool mass[map_size][map_size][map_size];

bool check(int x, int y, int z)
{
   if ((x < 0) || (x >= map_size) || 
	   (y < 0) || (y >= map_size) || 
	   (z < 0) || (z >= map_size)) return false;
  
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

    for (int x = 0; x < map_size; ++x)
        for (int y = 0; y < map_size; ++y)
            for (int z = 0; z < map_size; ++z)
            { //   floor generation
                if (/*y == 0 || */ rand() % 100 == 1)
                {
                    mass[x][y][z] = true;
                    cube_count++;
                }
                
            }

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
    Texture2D tBox;
    bool res = tBox.loadFromFile("res/textures/anim_tiles.png");

    Texture2D tFloor;
    res = tFloor.loadFromFile("res/textures/trstone2.png");
    tFloor.setRepeated(true);

//  Shaders
    Shader default_shader;
    res = default_shader.compile("res/shaders/shader.vert", "res/shaders/shader.frag");
    default_shader.bind();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    default_shader.setUniform("projection", projection);

//  Create cube
    glm::vec3 minPt(-0.5f);
    glm::vec3 maxPt(0.5f);

    std::vector<Vertex> cube_vertices;
    std::vector<GLuint> cube_indices;
    std::vector<glm::vec2> tex_coords =
    {
//      Front
        { 1.0f / 3.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 1.0f },
        { 1.0f / 3.0f, 1.0f },
//      Back
        { 1.0f / 3.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 1.0f },
        { 1.0f / 3.0f, 1.0f },
//      Bottom
        { 1.0f / 3.0f * 2.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f / 3.0f * 2.0f, 1.0f },
//      Top
        { 0.0f, 0.0f },
        { 1.0f / 3.0f, 0.0f },
        { 1.0f / 3.0f, 1.0f },
        { 0.0f, 1.0f },
//      Left
        { 1.0f / 3.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 1.0f },
        { 1.0f / 3.0f, 1.0f },
//      Right
        { 1.0f / 3.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 0.0f },
        { 1.0f / 3.0f * 2.0f, 1.0f },
        { 1.0f / 3.0f, 1.0f }
    };

    MakeCubeMesh(cube_vertices, cube_indices, minPt, maxPt);

    TexturedCube cube(&default_shader);
    cube.setTexture(&tBox);
    cube.init(cube_vertices, cube_indices, glm::vec3(0.5), GL_DYNAMIC_DRAW);
    cube.setAxisOfRotation(glm::vec3(0, 1, 0));
    cube.setTextureRect(glm::ivec4(0, 0, 32, 32));

//  Create floor
    std::vector<Vertex> floor_vertices;
    std::vector<GLuint> floor_indices;

    MakeRepeatedSurfaceMesh(floor_vertices, floor_indices, map_size, map_size);

    TexturedSurface surface(&default_shader);
    surface.init(floor_vertices, floor_indices, glm::vec3(1.0f));
    surface.setTexture(&tFloor);

    surface.setPosition(10, -3, 10);

//  Main loop
    RenderTarget renderer;

    Camera camera;
    camera.setPosition(10, 5, 10);

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

        if (camNeedUpdate)
        {
            camera.rotate(xoffset * 0.1f, yoffset * 0.1f);
            camNeedUpdate = false;
        }

        default_shader.bind();
        default_shader.setUniform("view", camera.getViewMatrix());
        
        renderer.clear();

        static float a = 0;
        a += 1.0f;

        static int delay = 0;
        static int frame = 0;
        
        if(++delay > 30)
        {
            delay = 0;
            ++frame;

            if(frame >= 4) frame = 0;
            cube.setTextureRect(glm::ivec4(frame * 32, 0, 32, 32));
        }

        renderer.draw(surface);
        
        for (int x = 0; x < map_size; ++x)
            for (int y = 0; y < map_size; ++y)
                for (int z = 0; z < map_size; ++z)
                {
                    if (mass[x][y][z])
                    {
                        cube.setPosition(x, y, z);
                        cube.setRotation(a); 
                        renderer.draw(cube);
                    }           
                }
        

        default_shader.unbind();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}