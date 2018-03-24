#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "window"

#define MAX_NUM_VERTEX_ATTRIBUTES 5;

#define MODEL_PATH "../data/models/"

#define TEXTURE_SUB_PATH "textures/"

#define SHADER_PATH "../src/Shader/GLSL/"
#define VERTEX_SHADER_EXT ".vs"
#define FRAGMENT_SHADER_EXT ".fs"
#define GEOMETRY_SHADER_EXT ".gs"

#define BULLET_TIME_STEP 1/60.f
#define BULLET_SUBSTEPS 10

#define CAMERA_FORWARD_KEY sf::Keyboard::W
#define CAMERA_BACKWARD_KEY sf::Keyboard::S
#define CAMERA_DEFAULT_SPEED 0.01f

#endif