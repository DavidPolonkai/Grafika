#include "scene.h"

#include <GL/glut.h>

#include <load.h>
#include <draw.h>

int num=0;

void init_scene(Scene* scene)
{
    load_model(&(scene->ball), "Objects/ball.obj");
    scene->texture_ball = load_texture("textures/balltexture.png"); 






    //load_model(&(scene->tri), "Objects/tri.obj");
    //scene->texture_tri = load_texture("textures/tri.png"); 
    //glBindTexture(GL_TEXTURE_2D, scene->texture_tri);



    scene->material_ball.ambient.red = 0.2;
    scene->material_ball.ambient.green = 0.2;
    scene->material_ball.ambient.blue = 0.2;

    scene->material_ball.diffuse.red = 0.3;
    scene->material_ball.diffuse.green = 0.3;
    scene->material_ball.diffuse.blue = 0.3;

    scene->material_ball.specular.red = 1.0;
    scene->material_ball.specular.green = 1.0;
    scene->material_ball.specular.blue = 0.2;

    scene->material_ball.shininess = 0.1;


    load_model(&(scene->field), "Objects/field.obj");
    scene->texture_field = load_texture("textures/field.png"); 



    scene->material_field.ambient.red = 0.2;
    scene->material_field.ambient.green = 0.2;
    scene->material_field.ambient.blue = 0.2;

    scene->material_field.diffuse.red = 0.3;
    scene->material_field.diffuse.green = 0.3;
    scene->material_field.diffuse.blue = 0.3;

    scene->material_field.specular.red = 1.0;
    scene->material_field.specular.green = 1.0;
    scene->material_field.specular.blue = 1.0;

    scene->material_field.shininess = 1.0;

}

void set_lighting()
{
    float ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    num++;
    set_material(&(scene->material_ball));
    set_lighting();
    //glTranslatef(num/1000.0,0.0,0.0);
    glScalef(1,1,1);
    draw_origin(); 
    //glRotatef(num,0,1,0);
    glTranslatef(num/1000.0,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ball);
    draw_model(&(scene->ball));
    //glTranslatef(0,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_field);
    set_material(&(scene->material_field));
    draw_model(&(scene->field));
    //draw_model(&(scene->tri));
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 3, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);

    glEnd();
}

