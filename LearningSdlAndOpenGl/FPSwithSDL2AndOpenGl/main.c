/*

Here i will try to implement a game of FPS(first-person-shooter)



gcc main.c -o main-lSDL2

OR

gcc main.c -o main -I/usr/include/SDL2 -lSDL2 -lGL



Algoritm of my actions

    Set up your development environment: Install the necessary tools and libraries, such as a C compiler, an OpenGL library, and any other dependencies you might need.

    Design your game: Decide on the gameplay mechanics, levels, and other aspects of your game. This will help you determine what features you will need to implement.

    Implement the graphics: Use OpenGL to create the 3D models and environments for your game. This will involve using OpenGL functions to define the geometry, materials, lighting, and other aspects of the scene.

    Implement the gameplay: Write the code that controls the player character and enemies, handles user input, and updates the game state. This will involve creating functions for movement, shooting, and other gameplay mechanics.

    Test and debug your game: Run your game and play through it to identify any bugs or issues that need to be fixed. Use a debugger to track down and fix any problems you encounter.

    Polish and release your game: Make any final changes or improvements to your game, then package it up and release it to the public.

*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <GL/glu.h>
#include <GL/glut.h>






#include <stdlib.h>
#include <string.h>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define NUM_PLATFORMS 10



float platforms[NUM_PLATFORMS][3];


float playerX = 0.0f;
float playerY = 0.0f;
float playerZ = 0.0f;
float playerYaw = 0.0f;
float floatLayerPitch = 0.0f;

float platformX = 0.0f;
float platformY = 0.0f;
float platformZ = 0.0f;

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;

float cameraPitch = 0.0f;
float cameraYaw = 0.0f;
float cameraFoV = 45.0f;
float cameraMovementSpeed = 0.1f;
float cameraRotationSpeed = 0.1f;
float cameraMouseSensitivity = 0.1f;


float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;




int quit = 0, frameCounter = 0, fps = 0, frameTime = 0, prevFrameTime = 0;




void shaders(void) {
    // set the clear color

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    // enable depth testing

    glEnable(GL_DEPTH_TEST);

    // Enable face culling

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // set the projection matrix

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspectRatio = (GLfloat) WINDOW_WIDTH / (GLfloat) WINDOW_HEIGHT;
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
    

    // set the modelview matrix

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void drawPlatform() {

    glColor3f(1.0f, 1.0f, 1.0f);


    glPushMatrix();

    glTranslatef(platformX, platformY, platformZ);


    glBegin(GL_QUADS);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();


    // Restore the modelview matrix
    glPopMatrix();
    

}


// void drawPlayer() {

// }

int main(int argc, char** argv) {
    // Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Set up the OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the window
    SDL_Window* window = SDL_CreateWindow("FPS Game by Max Chernikov", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    // Create the OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("Error of creating OpenGL context: %s\n", SDL_GetError());
        return 1;
    }



    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW: %s\n", glewGetErrorString(glewError));
        return 1;
    }

    
    shaders();

       


    while (!quit) {
        // Handle Events
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                  
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break; 
                        case SDLK_w:
                            playerY += cameraMovementSpeed;
                            break;
                        case SDLK_s:
                            playerY -= cameraMovementSpeed;
                            break;
                        case SDLK_a:
                            playerX -= cameraMovementSpeed;
                            break;
                        case SDLK_d:
                            playerX += cameraMovementSpeed;
                            break;
                        case SDLK_UP:
                            pitch -= cameraRotationSpeed;
                            break;
                        case SDLK_DOWN:
                            pitch += cameraRotationSpeed;
                            break;
                        case SDLK_LEFT:   
                            yaw -= cameraRotationSpeed; 
                            break;
                        case SDLK_RIGHT:
                            yaw += cameraRotationSpeed;
                            break;
                    }
                    break;
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        for (int i = 0; i < NUM_PLATFORMS; i++) {
            drawPlatform(platforms[i]);
        }


        // swap the buffers
        SDL_GL_SwapWindow(window);
    } 
 
    
    // Clean up

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}        
