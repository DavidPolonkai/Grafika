#include "callbacks.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);

    set_camera_pos(&camera,ball.position,10,45);
    draw_scene(&scene,&ball);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }

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

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    //rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'e':
        set_camera_angle(&camera,-1);
        break;
    case 'q':
        set_camera_angle(&camera,1);
        break;
    case 'a':
        //set_camera_side_speed(&camera, 1);
	set_direction(&ball,1);
        break;
    case 'd':
        //set_camera_side_speed(&camera, -1);
	set_direction(&ball,-1);
        break;
    case '+':
        set_camera_distance(&camera,1);
        break;
    case '-':
 	set_camera_distance(&camera ,-1);
        break;
    case 'w':
	set_ball_speed(&ball,1);
	break;
    case 's':
	set_ball_speed(&ball,-1);
	break;
    case 'x':
        set_direction(&ball,0);
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        //set_camera_side_speed(&camera, 0.0);
	//wsset_direction(&ball,0);
        break;
    case 'q':
    case 'e':
        set_camera_vert_speed(&camera,0.0);
        break; 
    /*case '':
    case 'y':
        rotate_obj(&obj,0.0);
	break;*/
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time,&ball.position);
    
    glutPostRedisplay();
}
