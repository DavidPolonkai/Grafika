#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <model.h>

typedef struct Scene
{
    Camera camera;
    Model field;
    Material material_field;
    GLuint texture_field;
    float light;
    int lightfx;
} Scene;

typedef struct Ball
{
 Model model;
 Material material;
 GLuint texture;
 vec3 position;
 float rot_degree;
 int direction;
 int speed;
 float r;
 int isAlive;
} Ball;

typedef struct Tri
{
 Model model;
 Material material;
 GLuint texture;
 vec3 position[100];
} Tri;

Tri tri;
Model tri2mod;
GLuint tri2tex;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene,Ball* ball);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene, Ball* ball,int type);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();


void set_direction(Ball* ball,int value);

void set_ball_speed(Ball* ball, int value);

void collusion(Ball* ball);

void set_help();

void set_light(Scene* scene,float i);

void null_points();

void set_lightfx(Scene* scene);

#endif /* SCENE_H */
