#include "scene.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <load.h>
#include <draw.h>

int help=0;

long points=0;

float lighty=0;
float lmodder=0.1;

void init_scene(Scene* scene,Ball* ball)
{

    scene->light=1;	
    load_model(&(ball->model), "Objects/ball.obj");
    ball->texture = load_texture("textures/balltexture.png"); 

    ball->direction=0;
    ball->position.x=-95;
    ball->position.y=0;
    ball->position.z=1;
    ball->rot_degree=0;
    ball->r=1;
    ball->isAlive=1;

    ball->material.ambient.red = 0.6;
    ball->material.ambient.green = 0.6;
    ball->material.ambient.blue = 0.6;

    ball->material.diffuse.red = 0.3;
    ball->material.diffuse.green = 0.3;
    ball->material.diffuse.blue = 0.3;

    ball->material.specular.red = 1.0;
    ball->material.specular.green = 1.0;
    ball->material.specular.blue = 1.0;

    ball->material.shininess = 1.0;


    load_model(&(scene->field), "Objects/field.obj");
    scene->texture_field = load_texture("textures/field.png"); 





    load_model(&(tri.model), "Objects/tri.obj");
    load_model(&(tri2mod),"Objects/tri_hard.obj");

    tri.texture = load_texture("textures/tri.png"); 
    tri2tex = load_texture("textures/tri_hard.png");	

    fill_tris();

    scene->material_field.ambient.red = 0.6;
    scene->material_field.ambient.green = 0.6;
    scene->material_field.ambient.blue = 0.6;

    scene->material_field.diffuse.red = 0.3;
    scene->material_field.diffuse.green = 0.3;
    scene->material_field.diffuse.blue = 0.3;

    scene->material_field.specular.red = 1.0;
    scene->material_field.specular.green = 1.0;
    scene->material_field.specular.blue = 1.0;

    scene->material_field.shininess = 0.0;

    tri.material.ambient.red = 0.1;
    tri.material.ambient.green = 0.1;
    tri.material.ambient.blue = 0.1;

    tri.material.diffuse.red = 0;
    tri.material.diffuse.green = 0;
    tri.material.diffuse.blue = 0;

    tri.material.specular.red = 0.4;
    tri.material.specular.green = 0.4;
    tri.material.specular.blue = 0.4;

    tri.material.shininess = 1.0;


}

void set_lighting(Scene scene,Ball* ball)
{
if (scene.lightfx>0){
    if (lighty<-10) lmodder=0.1;
    else if (lighty>10) lmodder=-0.1;
    lighty+=lmodder;
}
    float ambient_light[] = { 0.2, 0.2, 0.2, 1.0f };
    float diffuse_light[] = { 1.0*scene.light, 1.0*scene.light, 1.0*scene.light, 1.0f };
    float specular_light[] = { 0.5*scene.light, 0.5*scene.light, 0.5*scene.light, 1.0f };
    float position[] = { ball->position.x-0.3, lighty, 10.0f, 1.0f };

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

void draw_scene(const Scene* scene, Ball* ball,int type)
{
    set_material(&(ball->material));
    set_lighting(*scene,ball);
    glScalef(1,1,1);
    glPushMatrix();
    glTranslatef(0,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_field);
    set_material(&(scene->material_field));
    glColor3f(0.5,0.5,0.5); 
    draw_model(&(scene->field));

	
    draw_triangular_pyramids(type);

    glPopMatrix();


    move_ball(ball);




}


void drawString(float x,float y,float z, char string[]) {
  glPushAttrib(GL_CURRENT_BIT);
  glRasterPos3f(x,y,z);  
  glDisable(GL_LIGHTING);

  for (char* c = string; *c != '\0'; c++) {

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
 }	
  glPopAttrib();
}

void move_ball(Ball* ball){
 if (ball->isAlive==1 && help==0){
   glEnable(GL_LIGHTING);
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
    ball->position.x+=actual_movement*dir;
    ball->position.y+=dir*actual_movement*isSide;
    ball->position.z+=0;
  	
	


    glTranslatef(ball->position.x,ball->position.y,ball->position.z);
    ball->rot_degree+=ball->speed;	
    if (ball->rot_degree>360) ball->rot_degree-=360;
    glRotatef(ball->rot_degree*rotY,rotX,rotY,0);
 
    collusion(ball);
  
    glBindTexture(GL_TEXTURE_2D, ball->texture);
    draw_model(&(ball->model));
    if (ball->speed>0) points+=ball->speed*0.1;
    else points+=ball->speed*-0.2;
   
 }
 else if (help==1){
        glColor3f(1.0,1.0,1.0);
	drawString(ball->position.x,ball->position.y,ball->position.z+3.6,"Gyorsitas: W");
	drawString(ball->position.x,ball->position.y,ball->position.z+3.2,"Lassitas: S");
	drawString(ball->position.x,ball->position.y,ball->position.z+2.8,"Jobbra: D");
	drawString(ball->position.x,ball->position.y,ball->position.z+2.4,"Ballra: A");
	drawString(ball->position.x,ball->position.y,ball->position.z+2.0,"Zoom: +-");
	drawString(ball->position.x,ball->position.y,ball->position.z+1.6,"Camera angle: QE");
	drawString(ball->position.x,ball->position.y,ball->position.z+1.2,"Light_FX: L");
	drawString(ball->position.x,ball->position.y,ball->position.z+0.8,"Light: ,.");
	drawString(ball->position.x,ball->position.y,ball->position.z+0.4,"EXIT: ESC");
	drawString(ball->position.x,ball->position.y,ball->position.z,"Obstacle type: 0 1");
	
}
 else{
	glPushMatrix();
	glTranslatef(ball->position.x,ball->position.y,ball->r);
	if (ball->r>0.3)ball->r-=0.01;
	glScalef(1,1,ball->r);
        glBindTexture(GL_TEXTURE_2D, ball->texture);
        draw_model(&(ball->model));
	glPopMatrix();
        char str[50]="You died, press space to restart. Your score: ";
        char n[6];
	sprintf(n,"%ld",points);
	glColor3f(1.0,1.0,1.0);
	if (ball->r<0.3) drawString(ball->position.x,3.0f,ball->position.z+1,strcat(str,n));

 }

}





void set_direction(Ball* ball,int value){
 if (ball->speed>0)ball->direction=value;
 else if (ball->speed<0)ball->direction=-value;
}

void set_ball_speed(Ball* ball,int value){
	ball->speed+=value;

}

void stop_ball(Ball* ball){
	ball->speed=0;	
}

void set_help(){
	if (help==0) help++;
	else help--;
}

void set_light(Scene* scene,float i){
	scene->light+=i;
}

void null_points(){
	points=0;
}

void set_lightfx(Scene* scene){
	if (scene->lightfx==0) scene->lightfx++;
        else scene->lightfx--;
}

void collusion(Ball* ball){
 if (ball->position.x>=100-ball->r){
	ball->speed=-ball->speed*0.66666;
        ball->direction*=-1;
	ball->position.x=99.9999-ball->r;
 }
 else if (ball->position.x<=-100+ball->r){ 
	ball->speed=-ball->speed*0.66666;
	ball->direction*=-1;
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
 tri_collusion(ball->position,1,&ball->isAlive);
}

void tri_collusion(vec3 pos,int r,int* live){
 for (unsigned int i=0;i<sizeof(tri.position)/sizeof(*(tri.position));i++){
	if (sqrt(pow((pos.x-tri.position[i].x),2)+pow((pos.y-tri.position[i].y),2))<r)
	{
		*live=0;
	}
 }   
}

void draw_triangular_pyramids(int type){

 for (unsigned int i=0;i<(sizeof(tri.position)/sizeof(*(tri.position)));i++){
	glPushMatrix();
	glTranslatef(tri.position[i].x,tri.position[i].y,0);
	if (type==0){

	glBindTexture(GL_TEXTURE_2D, tri.texture);
        draw_model(&(tri.model));
	}
	else if(type==1){
	glBindTexture(GL_TEXTURE_2D, tri2tex);
        draw_model(&(tri2mod));
	}
	glPopMatrix();
 
 }	

}

void fill_tris(){
	srand(time(NULL));
	for (unsigned int i=0;i<(sizeof(tri.position)/sizeof(*(tri.position)));i++){
		tri.position[i].x=(float)rand()/((float)RAND_MAX/190)-90;
		tri.position[i].y=(float)rand()/((float)RAND_MAX/20)-10;
		tri.position[i].z=0;
		

	}
}


