#include "gl/glew.h"
#include "GLFW/glfw3.h"
#include "Constants.h"
#include "Particle.h"
#include <iostream>
#include <thread>
#include <chrono>
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float xPosInWindow(float x)
{
    return (WINDOW_SIZE/2) + (x * 4);
}

float yPosInWindow(float y)
{
   // std::cout << "yposinwindow "<<(WINDOW_SIZE / 2) - (y * 1) << '\n';
    return (WINDOW_SIZE *.2) + (y * 4);
}
float NDC(float n) {
   // std::cout << "ndc " << n / WINDOW_SIZE * 2 - 1 << '\n';
    return n / WINDOW_SIZE * 2 - 1;
}
int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //glfwSwapInterval(1);
    const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (monitor->width-WINDOW_SIZE) / 2, (monitor->height-WINDOW_SIZE) / 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ///glViewport(0, 0, WINDOW_SIZE, WINDOW_SIZE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    glClearDepth(1.0f);                
    glEnable(GL_DEPTH_TEST);                     
    glDepthFunc(GL_LEQUAL);        
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    Particle* p = new Particle();
    p->mass = 5.0f;
    p->pos = Vector3f(0.0f,100.0f, 0.0f);
    p->vel = Vector3f(10.0f, 0.0f, 30.0f);

    float lastUpdateTime = 0.0f;  // number of seconds since the last loop
    float lastFrameTime = 0.0f;   // number of seconds since the last frame
    float deltaTime = 0.046f;
    float t = 0;
    int n = 0;
    while (!glfwWindowShouldClose(window)&& t<=5)
    {
       // std::cout << "time: " << t<<'\n';
        static int timePreviousFrame;
        int timeToWait = 46 - ((int)glfwGetTime() - timePreviousFrame);
        if (timeToWait > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
        timePreviousFrame = (int)glfwGetTime();
        glfwPollEvents();
        //input
        processInput(window);



        //render
        //std::cout << p->pos << '\n';
        glEnable(GL_POINT_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();                 // Reset the model-view matrix

        gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
        glBegin(GL_POINTS);                   
        glVertex3f(0.0f, 0.5f, 0.0f);        
        glEnd();
        
        glColor3f(1.0f, 1.0f, 1.0f);          // Set The Color To white
        glBegin(GL_POINTS);
        std::cout << NDC(xPosInWindow(p->pos.z)) << '\n';
        glVertex3f(NDC(xPosInWindow(p->pos.x)), NDC(yPosInWindow(p->pos.y)), NDC(xPosInWindow(p->pos.z)));
        glEnd();

        //glColor3f(1.0f, 1.0f, 1.0f);          // Set The Color To white
        //glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
        //glVertex3f(0.0f, 1.0f, -4.0f);              // Top
        //glVertex3f(-1.0f, -1.0f, -4.0f);              // Bottom Left
        //glVertex3f(1.0f, -1.0f, -4.0f);              // Bottom Right
        //glEnd();
        
        p->addForce(Vector3f(0.0f, -10.0f * p->mass, 0.0f));
        p->addForce(p->vel * -0.4f); //air resitance -dV
        p->integrate(deltaTime);
        if (p->pos.y <= 0.0f) {
            p->pos.y = 0.0f;
            p->vel.y *= -0.9f;
            // p->pos.z += 0.1;
        }

        // Swap front and back buffers 
        glfwSwapBuffers(window);
        n++;
        t = n * deltaTime;




    }
    glfwTerminate();

	return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}