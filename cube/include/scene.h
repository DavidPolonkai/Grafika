#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <model.h>

typedef struct Scene
{
    Camera camera;
    Model cube;
    Model cube2;
    Material material;
    GLuint texture_id;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

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
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
