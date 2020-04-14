#include "info.h"

#include <stdio.h>

void print_model_info(const Model* model)
{
    printf("Vertices: %d\n", model->n_vertices);
    printf("Texture vertices: %d\n", model->n_texture_vertices);
    printf("Normals: %d\n", model->n_normals);
    printf("Triangles: %d\n", model->n_triangles);
}

void print_bounding_box(const Model* model)
{
    int i;
    double x, y, z;
    double min_x, max_x, min_y, max_y, min_z, max_z;

    if (model->n_vertices == 0) {
        return;
    }

    min_x = model->vertices[0].x;
    max_x = model->vertices[0].x;
    min_y = model->vertices[0].y;
    max_y = model->vertices[0].y;
    min_z = model->vertices[0].z;
    max_z = model->vertices[0].z;

    for (i = 0; i < model->n_vertices; ++i) {
        x = model->vertices[i].x;
        y = model->vertices[i].y;
        z = model->vertices[i].z;
        if (x < min_x) {
            min_x = x;
        }
        else if (x > max_x) {
            max_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
        else if (y > max_y) {
            max_y = y;
        }
        if (z < min_z) {
            min_z = z;
        }
        else if (z > max_z) {
            max_z = z;
        }
    }

    printf("Bounding box:\n");
    printf("x in [%lf, %lf]\n", min_x, max_x);
    printf("y in [%lf, %lf]\n", min_y, max_y);
    printf("z in [%lf, %lf]\n", min_z, max_z);
}
