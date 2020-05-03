#include "camera.h"
#include "utils.h"
#include <GL/glut.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = -4.0;
    camera->position.y = 0.0;
    camera->position.z = 4.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    camera->distance=10;
    camera->angle = 45;

    is_preview_visible = FALSE;
}

void update_camera(Camera* camera, double time,vec3* vector)
{
    double angle;
    double side_angle;
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

     //camera->position.x += camera->speed.y * time;
    //camera->position.y += sin(angle) * camera->speed.y * time;
    //camera->position.x += cos(side_angle) camera->speed.x * time;
    //camera->position.y += sin(side_angle) * camera->speed.x * time;
     //camera->position.z += camera->speed.z * time;
	
	camera->position.x=sin(degree_to_radian(camera->angle))*-(camera->distance)+vector->x;
        camera->position.z=cos(degree_to_radian(camera->angle))*(camera->distance)+vector->z;
        camera->position.y = 0;
	camera->rotation.x = -90+camera->angle;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x = vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void set_camera_vert_speed(Camera* camera, double speed){
	camera->speed.z = speed;
}

void set_camera_pos(Camera* camera,vec3 ballpos,float distance, float angle){
float alpha = degree_to_radian(angle);
camera->position.x=0;
camera->position.y=cos(alpha)*distance;
camera->position.z=sin(alpha)*distance;
}

void set_camera_angle(Camera* camera,int a){
 camera->angle+=(float)a;

}

void set_camera_distance(Camera* camera,int  a){
 camera->distance+=a;

}

