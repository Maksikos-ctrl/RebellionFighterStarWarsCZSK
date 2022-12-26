/*

Here i will try to implement a game of FPS(first-person-shooter)


Algoritm of my actions

    Set up your development environment: Install the necessary tools and libraries, such as a C compiler, an OpenGL library, and any other dependencies you might need.

    Design your game: Decide on the gameplay mechanics, levels, and other aspects of your game. This will help you determine what features you will need to implement.

    Implement the graphics: Use OpenGL to create the 3D models and environments for your game. This will involve using OpenGL functions to define the geometry, materials, lighting, and other aspects of the scene.

    Implement the gameplay: Write the code that controls the player character and enemies, handles user input, and updates the game state. This will involve creating functions for movement, shooting, and other gameplay mechanics.

    Test and debug your game: Run your game and play through it to identify any bugs or issues that need to be fixed. Use a debugger to track down and fix any problems you encounter.

    Polish and release your game: Make any final changes or improvements to your game, then package it up and release it to the public.

*/


void drawPlayer();
void drawEnemies();

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>





#include "draw.h"







#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define M_PI 3.14159265358979323846
#define PLATFORM_WIDTH 20
#define PLATFORM_HEIGHT 2
#define PLATFORM_LENGTH 20





float playerX = 0.0f;
float playerY = 0.0f;
float playerZ = 0.0f;
float playerPitch = 0.0f;
float playerYaw = 0.0f;






// here i will create global arr where i'm gonna store the pos of the enemy characters


float enemyPositions[10][3] = {
    {-10.0f, 0.0f, 0.0f},
    {10.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, -10.0f},
    {0.0f, 0.0f, 10.0f},
    {0.0f, 10.0f, 0.0f},
    {0.0f, -10.0f, 0.0f},
    {5.0f, 5.0f, 5.0f},
    {-5.0f, -5.0f, -5.0f},
    {-5.0f, 5.0f, -5.0f},
    {5.0f, -5.0f, 5.0f}
};


// break it down
void keyboard_touch(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            playerX -= sin(playerYaw * M_PI / 180.0f);
            playerZ -= cos(playerYaw * M_PI / 180.0f);
            break;
        case 'a':
            playerX -= cos(playerYaw * M_PI / 180.0f);
            playerZ += sin(playerYaw * M_PI / 180.0f);
            break;
        case 's':
            playerZ += cos(playerYaw * M_PI / 180.0f);
            playerX += sin(playerYaw * M_PI / 180.0f);
            break;
        case 'd':
            playerX += cos(playerYaw * M_PI / 180.0f);
            playerZ -= sin(playerYaw * M_PI / 180.0f);
            break;

    }
}


// void keyboard_touch(unsigned char key, int x, int y) {
//     switch (key) {
//         case 'w':
//             // move the player forward by adding a small amount to the player's z-coordinate
//             playerZ += 0.1f;
//             break;
//         case 'a':
//             // move the player left by subtracting a small amount from the player's x-coordinate
//             playerX -= 0.1f;
//             break;
//         case 's':
//             // move the player backward by subtracting a small amount from the player's z-coordinate
//             playerZ -= 0.1f;
//             break;
//         case 'd':
//             // move the player right by adding a small amount to the player's x-coordinate
//             playerX += 0.1f;
//             break;
//     }
// }



void mouse_touch(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            playerPitch -= 1.0f;
            break;

        case GLUT_KEY_DOWN:
           
            playerPitch += 1.0f;
            break;

        case GLUT_KEY_RIGHT:

            playerYaw += 1.0f;
            break;

        case GLUT_KEY_LEFT:
            playerYaw -= 1.0f;
            break;    
    }       

}


void display_platform() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // here, i'm setting up projection matrix

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat) WINDOW_WIDTH / (GLfloat) WINDOW_HEIGHT, 1, 1000.0);


    // here, i'm setting up the modelview matrix

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(playerX, playerY, playerZ, // eye position
          playerX + sin(playerYaw * M_PI / 180.0f), playerY + sin(playerPitch * M_PI / 180.0f), playerZ + cos(playerYaw * M_PI / 180.0f), // look-at point
          0.0f, 1.0f, 0.0f); // up vector

    // Draw the platform
    drawPlatform();
    
    drawPlayer();

    drawEnemies();

    // Swap the front and back buffers to update the display
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}


void drawPlatform() {
    glPushMatrix();
    glTranslatef(0.0f, -PLATFORM_LENGTH / 2.0f,  0.0f);
    glScalef(PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_LENGTH);
    glutSolidCube(1.0f);
    glPopMatrix();
}





int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutCreateWindow("FPS game by Max Chernikov");  
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(mouse_touch);  
    glutDisplayFunc(display_platform);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}