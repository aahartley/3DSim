#include "Main.h"

void test() {
    Particle* p = new Particle();
    p->mass = 1.0f;
    p->pos = Vector3f(0.0f, 100.0f, 0.0f);
    p->vel = Vector3f(10.0f, 0.0f, 30.0f);
    std::cout << p->pos.x << ' ' << p->pos.y << ' ' << p->pos.z << '\n';
    for (int i = 0; i < 5; i++) {
        p->addForce(Vector3f(0.0f, -10.0f * p->mass, 0.0f)); //gravity
        p->integrate(1);
        p->addForce(p->vel * -0.4f); //air resitance -dV
        p->addForce(Vector3f(-12.5f, 0, 0) * 0.4f); //wind Vwind-v
        //why integrate first without forces, ex from textbook?

        std::cout << p->pos.x << ' ' << p->pos.y << ' ' << p->pos.z << '\n';
    }
    delete p;

}

int main() {
    //test();
    if(init()<0)return -1;
    random.populateRand(1000);
    ParticleGenerator pG(Vector3f(0, 100, 0), 100, 0, 50,random);

    p.mass = 1.0f;
    p.pos = Vector3f(0.0f, 100.0f, 0.0f);
    p.vel = Vector3f(10.0f, 0.0f, 30.0f);

    pL.add(p);

    //std::vector<Vector3f> infinPlaneVert;
    //infinPlaneVert.push_back(Vector3f(50, 0, 50));
    //InfinitePlane infinitePlane(infinPlaneVert);

    std::vector<Vector3f> finPlaneVert;
    //3 2
    //0 1   bottom big plane
    finPlaneVert.push_back(Vector3f(-100.0f, 0.0f, 100.0f)); //p0
    finPlaneVert.push_back(Vector3f(100.0f, 0.0f, 100.0f)); //p1
    finPlaneVert.push_back(Vector3f(100.0f, 0.0f, -100.0f)); //p2
    finPlaneVert.push_back(Vector3f(-100.0f, 0.0f, -100.0f)); //p3

    Plane* finitePlane= new Plane(finPlaneVert,Vector3f(0,0,0));

    //1 2
    //0 3 right-side cube
    std::vector<Vector3f> finPlaneVert2;
    finPlaneVert2.push_back(Vector3f(-30.0f, 0.0f, 60.0f)); //p0
    finPlaneVert2.push_back(Vector3f(-30.0f, 10.0f, 60.0f)); //p1
    finPlaneVert2.push_back(Vector3f(-30.0f, 10.0f, 70.0f)); //p2
    finPlaneVert2.push_back(Vector3f(-30.0f, 0.0f, 70.0f)); //p3

    Plane* finitePlane2 = new Plane(finPlaneVert2, Vector3f(-30,5,65));

    //1 2
    //0 3 left-side
    std::vector<Vector3f> finPlaneVert3;
    finPlaneVert3.push_back(Vector3f(-40.0f, 0.0f, 60.0f)); //p0
    finPlaneVert3.push_back(Vector3f(-40.0f, 10.0f, 60.0f)); //p1
    finPlaneVert3.push_back(Vector3f(-40.0f, 10.0f, 70.0f)); //p2
    finPlaneVert3.push_back(Vector3f(-40.0f, 0.0f, 70.0f)); //p3

    Plane* finitePlane3 = new Plane(finPlaneVert3, Vector3f(-30, 5, 65));

    //3 2
    //0 1 back
    std::vector<Vector3f> finPlaneVert4;
    finPlaneVert4.push_back(Vector3f(-40.0f, 0.0f, 60.0f)); //p0
    finPlaneVert4.push_back(Vector3f(-30.0f, 0.0f, 60.0f)); //p1
    finPlaneVert4.push_back(Vector3f(-30.0f, 10.0f, 60.0f)); //p2
    finPlaneVert4.push_back(Vector3f(-40.0f, 10.0f, 60.0f)); //p3

    Plane* finitePlane4 = new Plane(finPlaneVert4, Vector3f(-30, 5, 65));

    //3 2
    //0 1 front
    std::vector<Vector3f> finPlaneVert5;
    finPlaneVert5.push_back(Vector3f(-40.0f, 0.0f, 70.0f)); //p0
    finPlaneVert5.push_back(Vector3f(-30.0f, 0.0f, 70.0f)); //p1
    finPlaneVert5.push_back(Vector3f(-30.0f, 10.0f, 70.0f)); //p2
    finPlaneVert5.push_back(Vector3f(-40.0f, 10.0f, 70.0f)); //p3
    
    Plane* finitePlane5 = new Plane(finPlaneVert5, Vector3f(-30, 5, 65));

    std::vector<Vector3f> finPlaneVert6;
    //3 2
    //0 1   top
    finPlaneVert6.push_back(Vector3f(-40.0f, 10.0f, 70.0f)); //p0
    finPlaneVert6.push_back(Vector3f(-30.0f, 10.0f, 70.0f)); //p1
    finPlaneVert6.push_back(Vector3f(-30.0f, 10.0f, 60.0f)); //p2
    finPlaneVert6.push_back(Vector3f(-40.0f, 10.0f, 60.0f)); //p3

    Plane* finitePlane6 = new Plane(finPlaneVert6, Vector3f(0, 0, 0));

    std::vector<Vector3f> triVert;
    triVert.push_back(Vector3f(-30.0f, 0.0f, 60.0f)); //p0
    triVert.push_back(Vector3f(-30.0f, 10.0f, 65.0f)); //p1
    triVert.push_back(Vector3f(-30.0f, 0.0f, 70.0f)); //p3
    Triangle* triangle = new Triangle(triVert, Vector3f(0, 0, 0));

    //objects.push_back(infinitePlane);
    objects.push_back(finitePlane);
    objects.push_back(finitePlane2);
    objects.push_back(finitePlane3);
    objects.push_back(finitePlane4);
    objects.push_back(finitePlane5);
    objects.push_back(finitePlane6);
    //objects.push_back(triangle);

    spg.initializeGrid(objects);


    float lastUpdateTime = 0.0f;  // number of seconds since the last loop
    float lastFrameTime = 0.0f;   // number of seconds since the last frame
    float deltaTime = 0.016f; // timestep
    float t = 0; //current time
    int n = 0; //iterations
    while (!glfwWindowShouldClose(window) && t <= 100)
    {

        //camera perspective  and zoom
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(zoom, 1, 0.1, 1000);
        glMatrixMode(GL_MODELVIEW);

        // std::cout << "time: " << t<<'\n';
        static int timePreviousFrame;
        int timeToWait = 16 - ((int)glfwGetTime() - timePreviousFrame);
        if (timeToWait > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
        timePreviousFrame = (int)glfwGetTime();
        glfwPollEvents();

        //input
        processInput(window);

        pG.generateParticles(pL, t, deltaTime);
        pL.testAndDeactivate();
        //render
        render();
        auto t1 = std::chrono::high_resolution_clock::now();

        //integrate
        //#pragma omp parallel for num_threads(12)
        for (int i = 0; i < pL.particles.size(); i++) {
            if (pL.particles[i].active) {
                pL.particles[i].addForce(Forces::gravity(pL.particles[i]));
   
                pL.particles[i].integrate(deltaTime);
                pL.particles[i].addForce(Forces::airResistance(pL.particles[i],0.4f)); //air resitance -dV
                pL.particles[i].addForce(Forces::wind(pL.particles[i],-12.5,0,0,0.4f)); //wind Vwind-v
               // pL.particles[i].addForce(Forces::potentialField(pL.particles[i], 10.0f, Vector3f(-35, 0, 65), 2, 10.0f));
                //pL.particles[i].addForce(Forces::steering(pL.particles[i], Vector3f(-35, 0, 65), 10.0f));
               // pL.particles[i].addForce(Forces::gravPoint(pL.particles[i],100.0f,Vector3f(0,10,0),2));
               // pL.particles[i].addForce(Forces::gravLine(pL.particles[i], Vector3f(0, 10, 0), Vector3f(0, 0, 1), 10.0f, 100.0f, 2));
                //pL.particles[i].addForce(Forces::randForce(pL.particles[i], random, deltaTime, 5.0f));
                //Forces::limitVelMin(pL.particles[i], 10.0f);
          /*      ParticleCollision pc(pL.particles[i]);
                for (int j = 0; j < objects.size(); j++) {
                    if (pc.ParticleDetection(*objects[j])) {
                        pc.ParticleResponse(*objects[j]);
                    }
                }*/
        /*        if(pL.particles[i].pos.y<1)
                 std::cout << pL.particles[i].pos << '\n';*/

                spg.checkCollision(pL.particles[i]);

            }
        }
      
     
        auto t2 = std::chrono::high_resolution_clock::now();

        /* Getting number of milliseconds as a double. */
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;

       // std::cout << ms_double.count() << "ms\n";
      //  std::cout << pL.particles[0].pos << '\n';
        
        // Swap front and back buffers 
        glfwSwapBuffers(window);
        n++;
        t = n * deltaTime;


    }
    glfwTerminate();

    return 0;
}

void render() {
    //render
    glEnable(GL_POINT_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                 // Reset the model-view matrix
    if (rotateValue >= 360) {
        rotateValue = 0;
    }
    if (rotatey >= 360) {
        rotatey = 0;
    }
    float x = 250 * std::cosf(3.14f * rotateValue / 180);
    float z = 250 * std::sinf(3.14f * rotateValue / 180);
    float y = 250 * std::sinf(3.14f * rotatey / 180);

    gluLookAt(x, y, z, 0.0, 30.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    /*   glBegin(GL_LINES);
       glVertex3f(0.0f, 0.0f, -10.0f);
       glVertex3f(0.0f, 0.0f, 10.0f);
       glEnd();*/

    glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
    glBegin(GL_POINTS);
    // std::cout << p->pos.x << ' '<< p->pos.y <<' '<< p->pos.z << '\n';
    for (Particle p : pL.particles) {
        if(p.active)
            glVertex3f(p.pos.x, p.pos.y, p.pos.z);
    }
    glEnd();
    /*      glBegin(GL_LINES);
          glVertex3f(-100.0f, 0.0f, 0.0f);
          glVertex3f(100.0f, 0.0f, 0.0f);
          glEnd();*/
    glColor3f(1.0f, 1.0f, 1.0f);

    //glBegin(GL_TRIANGLES);
    //glVertex3f(-30.0f, 0.0f, 60.0f); //p0
    //glVertex3f(-30.0f, 10.0f, 65.0f); //p1
    //glVertex3f(-30.0f, 0.0f, 70.0f); //p3
    //glEnd();

    //'infinite' white plane
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Red
    glBegin(GL_QUADS);
    //bottom
    glVertex3f(-40.0f, 0.0f, 60.0f);
    glVertex3f(-40.0f, 0.0f, 70.0f);
    glVertex3f(-30.0f, 0.0f, 70.0f);
    glVertex3f(-30.0f, 0.0f, 60.0f);
    //top
    glVertex3f(-40.0f, 10.0f, 60.0f);
    glVertex3f(-40.0f, 10.0f, 70.0f);
    glVertex3f(-30.0f, 10.0f, 70.0f);
    glVertex3f(-30.0f, 10.0f, 60.0f);
    //back
    glVertex3f(-30.0f, 10.0f, 60.0f);
    glVertex3f(-40.0f, 10.0f, 60.0f);
    glVertex3f(-40.0f, 0.0f, 60.0f);
    glVertex3f(-30.0f, 0.0f, 60.0f);
    //front
    glVertex3f(-30.0f, 10.0f, 70.0f);
    glVertex3f(-40.0f, 10.0f, 70.0f);
    glVertex3f(-40.0f, 0.0f, 70.0f);
    glVertex3f(-30.0f, 0.0f, 70.0f);
    //left-side
    glVertex3f(-40.0f, 10.0f, 70.0f);
    glVertex3f(-40.0f, 10.0f, 60.0f);
    glVertex3f(-40.0f, 0.0f, 60.0f);
    glVertex3f(-40.0f, 0.0f, 70.0f);
    //right-side
    glVertex3f(-30.0f, 10.0f, 70.0f);
    glVertex3f(-30.0f, 10.0f, 60.0f);
    glVertex3f(-30.0f, 0.0f, 60.0f);
    glVertex3f(-30.0f, 0.0f, 70.0f);
    glEnd();

}
int init() {

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
    glfwSetWindowPos(window, (monitor->width - WINDOW_SIZE) / 2, (monitor->height - WINDOW_SIZE) / 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ///glViewport(0, 0, WINDOW_SIZE, WINDOW_SIZE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);

    //glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
     //glShadeModel(GL_SMOOTH);   // Enable smooth shading
     //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rotateValue+=3;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rotateValue-=3;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        rotatey += 3;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        rotatey -= 3;
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom,1,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  //  std::cout << xpos << ' ' << ypos << '\n';
  //  mx = xpos;
   // my = ypos;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //std::cout << xoffset << ' ' << yoffset << '\n';
    zoom += (float) - yoffset * 10;
}
//cube
/*
 glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
        glBegin(GL_QUADS);
        //bottom
        glVertex3f(-10.0f, 0.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, -10.0f);
        //top
        glVertex3f(-10.0f, 10.0f, -10.0f);
        glVertex3f(-10.0f, 10.0f, 10.0f);
        glVertex3f(10.0f, 10.0f, 10.0f);
        glVertex3f(10.0f, 10.0f, -10.0f);
        //back
        glVertex3f(10.0f, 10.0f, -10.0f);
        glVertex3f(-10.0f, 10.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, -10.0f);
        glVertex3f(10.0f, 0.0f, -10.0f);
        //front
        glVertex3f(10.0f, 10.0f, 10.0f);
        glVertex3f(-10.0f, 10.0f, 10.0f);
        glVertex3f(-10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, 10.0f);
        //left-side
        glVertex3f(-10.0f, 10.0f, 10.0f);
        glVertex3f(-10.0f, 10.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, 10.0f);
        //right-side
        glVertex3f(10.0f, 10.0f, 10.0f);
        glVertex3f(10.0f, 10.0f, -10.0f);
        glVertex3f(10.0f, 0.0f, -10.0f);
        glVertex3f(10.0f, 0.0f, 10.0f);
        glEnd();*/