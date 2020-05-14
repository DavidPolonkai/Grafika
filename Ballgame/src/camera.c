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
    camera->distance=13;
    camera->angle = 45;

    is_preview_visible = FALSE;
}

void update_camera(Camera* camera,vec3* vector)
{
	camera->position.x=sin(degree_to_radian(camera->angle))*-(camera->distance)+vector->x;
        camera->position.z=cos(degree_to_radian(camera->angle))*(camera->distance)+vector->z;
        camera->position.y = 0;
        camera->rotation.x = -90+camera->angle;
}

void set_camera_follow(Camera* camera,float y,float d,float alpha,float modifier){
 camera->rotation.z=sin(alpha)*radian_to_degree(atan(y/d))/modifier;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}







void set_camera_pos(Camera* camera,vec3 ballpos){
float alpha = degree_to_radian(camera->angle);
camera->position.x=0;
camera->position.y=cos(alpha)*camera->distance;
camera->position.z=sin(alpha)*camera->distance;
set_camera_follow(camera,ballpos.y,camera->distance,alpha,2.6);
}

void set_camera_angle(Camera* camera,int a){
if ((a==1 && camera->angle<=90) || (a==-1 && camera->angle>=0) ) camera->angle+=(float)a;

}

void set_camera_distance(Camera* camera,int  a){
 if (!(a==-1 && camera->distance<3))camera->distance+=a;

}


