#include <GL/gl.h>

#define NUM_VERTICES 8 

extern float playerX;
extern float playerY;
extern float playerZ;
extern float playerPitch;
extern float playerYaw;




void drawPlayer() {
    glPushMatrix();
    glTranslatef(playerX, playerY, playerZ);
    glRotatef(playerPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(playerYaw, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);


    GLfloat vertices[NUM_VERTICES][3] = {
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f}
    };  // add a semicolon here


    // Set the color to red
    glColor3f(1.0f, 0.0f, 0.0f);
    // Begin rendering using GL_QUADS
    glBegin(GL_QUADS);
    // Render the front face using the vertices in the vertices array
    glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);  // vertex 0
    glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);  // vertex 1
    glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);  // vertex 2
    glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);  // vertex 3
    // End rendering using GL_QUADS
    glEnd();
    glPopMatrix();

    

    // // Front face
    // glColor3f(1.0f, 0.0f, 0.0f);
    // glVertex3f(-1.0f, 1.0f, 1.0f);
    // glVertex3f(1.0f, 1.0f, 1.0f);
    // glVertex3f(1.0f, -1.0f, 1.0f);
    // glVertex3f(-1.0f, -1.0f, 1.0f);

    // // Back face
    // glColor3f(0.0f, 1.0f, 0.0f);
    // glVertex3f(-1.0f, 1.0f, -1.0f);
    // glVertex3f(1.0f, 1.0f, -1.0f);
    // glVertex3f(1.0f, -1.0f, -1.0f);
    // glVertex3f(-1.0f, -1.0f, -1.0f);

    // // Left face
    // glColor3f(0.0f, 0.0f, 1.0f);
    // glVertex3f(-1.0f, 1.0f, 1.0f);
    // glVertex3f(-1.0f, 1.0f, -1.0f);
    // glVertex3f(-1.0f, -1.0f, -1.0f);
    // glVertex3f(-1.0f, -1.0f, 1.0f);

    // // Right face
    // glColor3f(1.0f, 0.0f, 1.0f);
    // glVertex3f(1.0f, 1.0f, 1.0f);
    // glVertex3f(1.0f, 1.0f, -1.0f);
    // glVertex3f(1.0f, -1.0f, -1.0f);
    // glVertex3f(1.0f, -1.0f, 1.0f);

    glEnd();
}

// void drawPlayer() {
//     // save the current modelview matrix
//     glPushMatrix();
//     // translate the modelview matrix to the player's position
//     glTranslatef(playerX, playerY, playerZ);
//     // rotate the modelview matrix around the y-axis to match the player's yaw angle
//     glRotatef(playerYaw, 0.0f, 1.0f, 0.0f);
//     // rotate the modelview matrix around the x-axis to match the player's pitch angle
//     glRotatef(playerPitch, 1.0f, 0.0f, 0.0f);
//     // draw the player model here using OpenGL drawing commands
//     // (e.g. glutSolidSphere(), glBegin(GL_TRIANGLES), etc.)
//     // restore the previous modelview matrix
//     glPopMatrix();
// }

