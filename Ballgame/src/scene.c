#include "scene.h"

#include <GL/glut.h>

#include <load.h>
#include <draw.h>


void init_scene(Scene* scene,Ball* ball)
{

    load_model(&(ball->model), "Objects/ball.obj");
    ball->texture = load_texture("textures/balltexture.png"); 

    ball->direction=0;
    ball->position.x=0;
    ball->position.y=0;
    ball->position.z=1;
    ball->rot_degree=0;
    ball->r=1;

    ball->material.ambient.red = 0.2;
    ball->material.ambient.green = 0.2;
    ball->material.ambient.blue = 0.2;

    ball->material.diffuse.red = 0.0;
    ball->material.diffuse.green = 0.0;
    ball->material.diffuse.blue = 0.0;

    ball->material.specular.red = 1.0;
    ball->material.specular.green = 1.0;
    ball->material.specular.blue = 1.0;

    ball->material.shininess = 1.0;


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

    scene->material_field.shininess = 0.1;
	
    load_model(&(scene->tri), "Objects/tri.obj");

    scene->texture_tri = load_texture("textures/tri.png"); 


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

void draw_scene(const Scene* scene,const Ball* ball)
{
    set_material(&(ball->material));
    set_lighting();
    //glTranslatef(num/1000.0,0.0,0.0);
    glScalef(1,1,1);
    draw_origin(); 

    
    

    glTranslatef(0,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_field);
    set_material(&(scene->material_field));
    draw_model(&(scene->field));
    glBindTexture(GL_TEXTURE_2D, scene->texture_tri);
    draw_model(&(scene->tri));
    move_ball(ball);
    glBindTexture(GL_TEXTURE_2D, ball->texture);
    draw_model(&(ball->model));
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

void move_ball(Ball* ball){
   int isSide;
   int rotY;
   int rotX;
   float dir; 
   float actual_movement=0.01745329252 * ball->speed;   
    if (ball->direction==0) {
	dir=1;
	isSide=0;
        rotY=1;
        rotX=0;
    }	
    else if (ball->direction==1){ //bal
	dir=0.7071067812;
	isSide=1;
        rotY=-1;
        rotX=1;
	}	
    else if (ball->direction==-1){ //jobb
	dir=0.7071067812;
  	isSide=-1;
        rotY=1;
        rotX=1;
	}
	printf("=%f=",ball->position.y);
    ball->position.x+=actual_movement*dir;
    ball->position.y+=dir*actual_movement*isSide;
    ball->position.z+=0;
    collusion(ball);
    glTranslatef(ball->position.x,ball->position.y,ball->position.z);
    ball->rot_degree+=ball->speed;	
    if (ball->rot_degree>360) ball->rot_degree-=360;
    glRotatef(ball->rot_degree*rotY,rotX,rotY,0);
}


void set_direction(Ball* ball,int value){
	ball->direction=value;
}

void set_ball_speed(Ball* ball,int value){
	ball->speed+=value;

}

void collusion(Ball* ball){
 printf("III%fIII",ball->position.x);
 if (ball->position.x>=100-ball->r){
	ball->speed=-ball->speed*0.66666;
	ball->position.x=99.9999-ball->r;
}
 else if (ball->position.x<=-100+ball->r){ 
	ball->speed=-ball->speed*0.66666;
	ball->position.x=-99.9999+ball->r;
}

 if (ball->position.y>=10-ball->r){
	ball->speed*=0.66666;
        ball->direction*=-1;
	ball->position.y=9.9999-ball->r;
}
 else if (ball->position.y<=-10+ball->r){
	ball->speed*=0.66666;
        ball->direction*=-1;
	ball->position.y=-9.9999+ball->r;


}

}
