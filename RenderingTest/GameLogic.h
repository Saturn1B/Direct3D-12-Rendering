#pragma once

#include "d3dx12.h"
#include "Transform.h"
#include "Renderer.h"
#include <chrono>

// camera transform
extern Transform cameraTransform;

// camera rotation
extern float rotationAngleX;
extern float rotationAngleY;
extern float rotationAngleZ;

// camera speed parameter
extern float cameraMoveSpeed;
extern float cameraRotationSpeed;

// cube rotation
extern float xrot;
extern float yrot;
extern float zrot;

// we will exit the program when this becomes false
extern bool Running;

using high_resolution_clock = std::chrono::high_resolution_clock;

using time_point = std::chrono::high_resolution_clock::time_point;
using duration = std::chrono::high_resolution_clock::duration;

extern time_point startTime;
extern time_point prevTime;

void Update(double deltaTimeSec); // update the game logic

extern XMFLOAT4X4 cube1WorldMat; // our first cubes world matrix (transformation matrix)
extern XMFLOAT4X4 cube1RotMat; // this will keep track of our rotation for the first cube
extern XMFLOAT4 cube1Position; // our first cubes position in space