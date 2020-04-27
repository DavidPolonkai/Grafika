#include "model.h"

#include <stdlib.h>

void init_model(Model* model)
{
    model->n_vertices = 0;
    model->n_texture_vertices = 0;
    model->n_normals = 0;
    model->n_triangles = 0;
    model->vertices = NULL;
    model->texture_vertices = NULL;
    model->normals = NULL;
    model->triangles = NULL;
}

void allocate_model(Model* model)
{
    model->vertices =
        (Vertex*)malloc((model->n_vertices + 1) * sizeof(Vertex));
    model->texture_vertices =
        (TextureVertex*)malloc((model->n_texture_vertices + 1) * sizeof(TextureVertex));
    model->normals =
        (Vertex*)malloc((model->n_normals + 1) * sizeof(Vertex));
    model->triangles =
        (Triangle*)malloc(model->n_triangles * sizeof(Triangle));
}

void free_model(Model* model)
{
    if (model->vertices != NULL) {
        free(model->vertices);
    }
    if (model->texture_vertices != NULL) {
        free(model->texture_vertices);
    }
    if (model->normals != NULL) {
        free(model->normals);
    }
    if (model->triangles != NULL) {
        free(model->triangles);
    }
    init_model(model);
}
