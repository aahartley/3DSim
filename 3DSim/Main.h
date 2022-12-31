#pragma once
#include "gl/glew.h"
#include "GLFW/glfw3.h"
#include "Constants.h"
#include "ParticleGenerator.h"
#include "Particle.h"
#include "ParticleList.h"
#include "Polygon.h"
#include "ParticleCollision.h"
#include "SpatialHashGrid.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

double mx = 0;
double my = 0;
double mz = 0;
float rotateValue = 135;
float zoom = 45.0f;
float rotatey = 20.0f;
float moveF = 0;
GLFWwindow* window;
Particle p =  Particle();
std::vector<Polygon*> objects;
ParticleList pL(1000);
ParticleGenerator pG(Vector3f(0,100,0),10,0,50);
SpatialHashGrid spg(Vector3f(200, 20, 200), 10, Vector3f (-100, 0, -100));

int init();
void render();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
