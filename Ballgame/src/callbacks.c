#include "callbacks.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0


int isAlive;
int type=0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    set_camera_pos(&camera,ball.position);
    draw_scene(&scene,&ball,type);
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}



void keyboard(unsigned char key)
{
    switch (key) {
    case 'e':
        set_camera_angle(&camera,-1);
        break;
    case 'q':
        set_camera_angle(&camera,1);
        break;
    case 'a':
	set_direction(&ball,1);
        break;
    case 'd':
	set_direction(&ball,-1);
        break;
    case '-':
        set_camera_distance(&camera,1);
        break;
    case '+':
 	set_camera_distance(&camera ,-1);
        break;
    case 'w':
	set_ball_speed(&ball,1);
	break;
    case 's':
	set_ball_speed(&ball,-1);
	break;
    case 'x':
        //set_direction(&ball,0);  //only for debugging
        break;
    case 'h':{
	
	stop_ball(&ball);
	set_help();
	}	        
	break;
    case ',':set_light(&scene,-0.1);
	break;
    case '.':set_light(&scene,0.1);
        break;
    case '1':type=1;
	break;
    case '0':type=0;
        break;
    case ' ': {
		if (ball.isAlive==0){
			ball.direction=0;
			ball.speed=0;
    			ball.position.x=-95;
			ball.position.y=0;
			ball.position.z=1;
			ball.rot_degree=0;
			ball.r=1;
			ball.isAlive=1;
			null_points();
	
		}
              }
 	break; 
    case 'l':
		set_lightfx(&scene);
        break;
    case 27: exit(0);
	break;
    }

    glutPostRedisplay();
}





void idle()
{
    static int last_frame_time = 0;
    int current_time;
  //  double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
   // elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera,&ball.position);
    
    glutPostRedisplay();
}
