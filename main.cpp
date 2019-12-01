#include <glew.h>
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <string>
#include "mymath.h"

#define PI 3.14159265358979323846

void setTransMatrix(float *mat, float x, float y, float z);
void multiplyMatrix(float *a, float *b);
void xProduct(float *a, float *b, float *res);
void normalize(float *a);
void setIdentMatrix(float *mat, int size);
void placeCam(float posX, float posY, float posZ, float lookX, float lookY, float lookZ);
void rotationMatrix(float *rotation, float x, float y, float z, float angle);
void keyup(unsigned char key, int x, int y);

void init();
GLuint loadBMP_custom(const char *imagepath);

struct vec3 {
    float x;
    float y;
    float z;
};

// vertices for triangle
float spinner[] = {-1.0f, -1.0f, -1.0f, // triangle 1 : begin
                   -1.0f, -1.0f, 1.0f,
                   -1.0f, 1.0f, 1.0f, // triangle 1 : end

                   1.0f, 1.0f, -1.0f, // triangle 2 : begin
                   -1.0f, -1.0f, -1.0f,
                   -1.0f, 1.0f, -1.0f, // triangle 2 : end

                   1.0f, -1.0f, 1.0f,
                   -1.0f, -1.0f, -1.0f,
                   1.0f, -1.0f, -1.0f,

                   1.0f, 1.0f, -1.0f,
                   1.0f, -1.0f, -1.0f,
                   -1.0f, -1.0f, -1.0f,

                   -1.0f, -1.0f, -1.0f,
                   -1.0f, 1.0f, 1.0f,
                   -1.0f, 1.0f, -1.0f,

                   1.0f, -1.0f, 1.0f,
                   -1.0f, -1.0f, 1.0f,
                   -1.0f, -1.0f, -1.0f,

                   -1.0f, 1.0f, 1.0f,
                   -1.0f, -1.0f, 1.0f,
                   1.0f, -1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, -1.0f, -1.0f,
                   1.0f, 1.0f, -1.0f,

                   1.0f, -1.0f, -1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, -1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, -1.0f,
                   -1.0f, 1.0f, -1.0f,

                   1.0f, 1.0f, 1.0f,
                   -1.0f, 1.0f, -1.0f,
                   -1.0f, 1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   -1.0f, 1.0f, 1.0f,
                   1.0f, -1.0f, 1.0f
};
float scale = 2.0;
int num_ver = sizeof(spinner) / sizeof(float);
float revolver[sizeof(spinner) / sizeof(float)];

float sp_norm[] = {-1.0f, 0.0f, 0.0f, // triangle 1 : begin
                   -1.0f, 0.0f, 0.0f,
                   -1.0f, 0.0f, 0.0f, // triangle 1 : end

                   0.0f, 0.0f, -1.0f, // triangle 2 : begin
                   0.0f, 0.0f, -1.0f,
                   0.0f, 0.0f, -1.0f, // triangle 2 : end

                   0.0f, -1.0f, 0.0f,
                   0.0f, -1.0f, 0.0f,
                   0.0f, -1.0f, 0.0f,

                   0.0f, 0.0f, -1.0f,
                   0.0f, 0.0f, -1.0f,
                   0.0f, 0.0f, -1.0f,

                   -1.0f, 0.0f, 0.0f,
                   -1.0f, 0.0f, 0.0f,
                   -1.0f, 0.0f, 0.0f,

                   0.0f, -1.0f, 0.0f,
                   0.0f, -1.0f, 0.0f,
                   0.0f, -1.0f, 0.0f,

                   0.0f, 0.0f, 1.0f,
                   0.0f, 0.0f, 1.0f,
                   0.0f, 0.0f, 1.0f,

                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,

                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,

                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,

                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,

                   0.0f, 0.0f, 1.0f,
                   0.0f, 0.0f, 1.0f,
                   0.0f, 0.0f, 1.0f
};
float re_norm[sizeof(spinner) / sizeof(float)];


float colors1[] = {0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
                   0.0f, 0.0f, 1.0f, 0.3f,
};

float colors2[] = {1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
                   1.0f, 0.0f, 0.0f, 0.3f,
};

// program and shader Id
GLuint p, v, f;

// obj_id attrib locations
GLuint vertexLoc, colorLoc, normalLoc;

// uniform var locations
GLuint projMatrixLoc, viewMatrixLoc, normalMatrixLoc;

GLuint ambientColorLoc, lightColorLoc, lightPositionLoc, ShininessLoc, StrengthLoc, EyeDirectionLoc;

GLuint textureLoc, samplerLoc;

// obj_id array obj Id
GLuint obj_id[3];

// storage for matrices
float projMatrix[16];
float viewMatrix[16];
float normalMatrix[9];

float ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
float lightColor[] = {0.9f, 0.9f, 0.9f};
float lightPosition[] = {0.0f, 0.0f, 2.0f};
float Shininess = 15.0;
float Strength = 10.0;
float EyeDirection[] = {0, 0, 10};


int frame = 0, t, timebase = 0;
char s[50];

int viewPosition[] = {0, 0, 10};
float angle = 0.0;
float angle2 = 0.0;
int startX;
int startY;

int selectX;
int selectY;
int window_width;
int window_height;
GLuint texID;

// vector opt
// res = a cross b;
void xProduct(float *a, float *b, float *res) {

    res[0] = a[1] * b[2] - b[1] * a[2];
    res[1] = a[2] * b[0] - b[2] * a[0];
    res[2] = a[0] * b[1] - b[0] * a[1];
}

// normalize a vec3
void normalize(float *a) {

    float mag = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}

// Matrix Opt. - In Opengl 3 we need to handle our own matrix.

// View Matrix
// just like glulookat
void placeCam(float posX, float posY, float posZ, float lookX, float lookY, float lookZ) {

    float dir[3], right[3], up[3];

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;

    dir[0] = (lookX - posX);
    dir[1] = (lookY - posY);
    dir[2] = (lookZ - posZ);
    normalize(dir);

    // this order matters
    xProduct(dir, up, right);
    normalize(right);

    xProduct(right, dir, up);
    normalize(up);

    float aux[16];

    viewMatrix[0] = right[0];
    viewMatrix[1] = up[0];
    viewMatrix[2] = -dir[0];
    viewMatrix[3] = 0.0f;
    viewMatrix[4] = right[1];
    viewMatrix[5] = up[1];
    viewMatrix[6] = -dir[1];
    viewMatrix[7] = 0.0f;
    viewMatrix[8] = right[2];
    viewMatrix[9] = up[2];
    viewMatrix[10] = -dir[2];
    viewMatrix[11] = 0.0f;
    viewMatrix[12] = 0.0f;
    viewMatrix[13] = 0.0f;
    viewMatrix[14] = 0.0f;
    viewMatrix[15] = 1.0f;

    normalMatrix[0] = viewMatrix[0];
    normalMatrix[1] = viewMatrix[1];
    normalMatrix[2] = viewMatrix[2];
    normalMatrix[3] = viewMatrix[4];
    normalMatrix[4] = viewMatrix[5];
    normalMatrix[5] = viewMatrix[6];
    normalMatrix[6] = viewMatrix[8];
    normalMatrix[7] = viewMatrix[9];
    normalMatrix[8] = viewMatrix[10];

    setTransMatrix(aux, -posX, -posY, -posZ);
    multiplyMatrix(viewMatrix, aux);

}

// In this form : a = a * b;
void multiplyMatrix(float *a, float *b) {
    float res[16];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j * 4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
            }
        }
    }
    memcpy(a, res, 16 * sizeof(float));
}

// sets the square matrix mat to the ID matrix,
void setIdentMatrix(float *mat, int size) {
    // input: size: size of the matrix (for example size=4 means 4 by 4 matrix)
    // output: mat: Identity matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mat[i * 4 + j] = 0.;
        }
    }
    for (int i = 0; i < size; ++i) {
        mat[i * size + i] = 1.;
    }
}

// Generates a rotation matrix.  Angle is in radian.
void rotationMatrix(float *rotation, float x, float y, float z, float angle) {
    // inputs:  x,y,z: rotation vector
    //          angle:  angle of rotation around vector(x,y,z)
    // output:  returns rotation matrix
    float length = sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    float c = cos(angle);
    float s = sin(angle);
    // From http://ksuweb.kennesaw.edu/~plaval/math4490/rotgen.pdf
    rotation[0] = x * x * (1 - c) + c;
    rotation[1] = x * y * (1 - c) + z * s;
    rotation[2] = x * z * (1 - c) - y * s;
    rotation[3] = 0;
    rotation[4] = y * x * (1 - c) - z * s;
    rotation[5] = y * y * (1 - c) + c;
    rotation[6] = y * z * (1 - c) + x * s;
    rotation[7] = 0;
    rotation[8] = z * x * (1 - c) + y * s;
    rotation[9] = z * y * (1 - c) - x * s;
    rotation[10] = z * z * (1 - c) + c;
    rotation[11] = 0;
    rotation[12] = 0;
    rotation[13] = 0;
    rotation[14] = 0;
    rotation[15] = 1;
}

// Transformation matrix mat with a translation
void setTransMatrix(float *mat, float x, float y, float z) {
    // inputs:  x: translation in x direction
    //          y: translation in y direction
    //          z: translation in z direction
    // output:  mat : translation matrix
    setIdentMatrix(mat, 4);
    mat[3 * 4 + 0] = x;
    mat[3 * 4 + 1] = y;
    mat[3 * 4 + 2] = z;
}

//Transformation matrix mat with a scaling
void setScale(float *mat, float xScale, float yScale, float zScale) {
    // inputs:  xScale: scale in x direction
    //          yScale: scale in y direction
    //          zScale: scale in z direction
    // output:  mat : Scale matrix
    setIdentMatrix(mat, 4);
    mat[0 * 4 + 0] = xScale;
    mat[1 * 4 + 1] = yScale;
    mat[2 * 4 + 2] = zScale;
}

// Projection Matrix
void buildProjMatrix(float fov, float ratio, float nearP, float farP) {

    float f = 1.0f / tan(fov * (PI / 360.0));
    setIdentMatrix(projMatrix, 4);
    projMatrix[0] = f / ratio;
    projMatrix[1 * 4 + 1] = f;
    projMatrix[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    projMatrix[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    projMatrix[2 * 4 + 3] = -1.0f;
    projMatrix[3 * 4 + 3] = 0.0f;
}

void changeSize(int w, int h) {

    float ratio;

    // place viewport to be the entire window
    glViewport(0, 0, w, h);
    ratio = (1.0f * w) / h;
    buildProjMatrix(53.13f, ratio, 1.0f, 30.0f);
}

void setupBuffers() {

    GLuint buffers[6];

    glGenVertexArrays(2, obj_id);

    // first triangle
    glBindVertexArray(obj_id[0]);
    // generate 2 buffers for obj_id and color
    glGenBuffers(6, buffers);
    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spinner), spinner, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, 0, 0, 0);

    // bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

    // bind buffer for normals and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sp_norm), sp_norm, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, 0, 0, 0);

    glBindVertexArray(obj_id[1]);
    glGenBuffers(3, buffers);
    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(revolver), revolver, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, 0, 0, 0);

    // bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

    // bind buffer for normals and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(re_norm), re_norm, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, 0, 0, 0);
}

void setUniforms() {

    // must be called after glUseProgram
    // set the variables for the shader
    glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);
    glUniformMatrix4fv(viewMatrixLoc, 1, false, viewMatrix);
    glUniformMatrix3fv(normalMatrixLoc, 1, false, normalMatrix);
    glUniform4fv(ambientColorLoc, 1, ambientColor);
    glUniform3fv(lightColorLoc, 1, lightColor);
    glUniform3fv(lightPositionLoc, 1, lightPosition);
    glUniform1f(ShininessLoc, Shininess);
    glUniform1f(StrengthLoc, Strength);
    glUniform3fv(EyeDirectionLoc, 1, EyeDirection);

}

void renderScene(void) {
    frame++;
    angle++;
    angle2+=2;

    float spin = angle/50.0f;
    float revolve = angle2/100.0f;

    t = glutGet(GLUT_ELAPSED_TIME);
    if (t - timebase > 1000) {
        sprintf(s, "FPS:%4.2f",
                frame * 1000.0 / (t - timebase));
        timebase = t;
        frame = 0;
    }
    glutSetWindowTitle(s);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //placeCam(10,2,10,0,2,-5);
    placeCam(viewPosition[0], viewPosition[1], viewPosition[2], 0, 0, -5);
//    float rotation[16];
//    rotationMatrix(rotation, 0.0, 1.0, 0.0, fmod((angle + 0.0001 * t / 200), 2 * PI));
//    multiplyMatrix(viewMatrix, rotation);
//    rotationMatrix(rotation, 0.0, 1.0, 0.0, fmod((angle + 0.0001 * t / 200), 2 * PI));
//    multiplyMatrix(viewMatrix, rotation);
    float eye[16];
    memcpy(eye, viewMatrix, sizeof(float) * 16);

    // fitst cube
    float T[16];
    setScale(T,0.5,0.5,0.5);
    multiplyMatrix(viewMatrix, T);
    rotationMatrix(T, 0, 1.0, 0.0, spin);
    multiplyMatrix(viewMatrix, T);
    normalMatrix[0] = viewMatrix[0];
    normalMatrix[1] = viewMatrix[1];
    normalMatrix[2] = viewMatrix[2];
    normalMatrix[3] = viewMatrix[4];
    normalMatrix[4] = viewMatrix[5];
    normalMatrix[5] = viewMatrix[6];
    normalMatrix[6] = viewMatrix[8];
    normalMatrix[7] = viewMatrix[9];
    normalMatrix[8] = viewMatrix[10];
    glUseProgram(p);
    setUniforms();

    glBindVertexArray(obj_id[0]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(spinner));

    memcpy(viewMatrix, eye, sizeof(float) * 16);

    float U[16];
    setScale(U,0.25,0.25,0.25);
    multiplyMatrix(viewMatrix, U);
    rotationMatrix(U, 0, 1.0, 0.0, revolve);
    multiplyMatrix(viewMatrix, U);
    setTransMatrix(U, 15 ,0,0);
    multiplyMatrix(viewMatrix, U);
    rotationMatrix(U, 0, 1.0, 0.0, -1*revolve);
    multiplyMatrix(viewMatrix, U);

    normalMatrix[0] = viewMatrix[0];
    normalMatrix[1] = viewMatrix[1];
    normalMatrix[2] = viewMatrix[2];
    normalMatrix[3] = viewMatrix[4];
    normalMatrix[4] = viewMatrix[5];
    normalMatrix[5] = viewMatrix[6];
    normalMatrix[6] = viewMatrix[8];
    normalMatrix[7] = viewMatrix[9];
    normalMatrix[8] = viewMatrix[10];
    glUseProgram(p);
    setUniforms();


    glBindVertexArray(obj_id[1]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(revolver));
    glutSwapBuffers();
}


void printShaderInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0) {
        infoLog = (char *) malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0) {
        infoLog = (char *) malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

GLuint initShaders(char *vertex_name, char *fragment_name) {

    char *vertShader = NULL, *fragShader = NULL;

    GLuint p, v, f;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    vertShader = getTxtFile(vertex_name);
    fragShader = getTxtFile(fragment_name);
    const char *vv = vertShader;
    const char *ff = fragShader;
    glShaderSource(v, 1, &vv, NULL);
    glShaderSource(f, 1, &ff, NULL);
    free(vertShader);
    free(fragShader);
    glCompileShader(v);
    glCompileShader(f);
    printShaderInfoLog(v);
//    printShaderInfoLog(f);
    p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glBindFragDataLocation(p, 0, "outputF");
    glLinkProgram(p);
//    printProgramInfoLog(p);
    vertexLoc = glGetAttribLocation(p, "position");
    colorLoc = glGetAttribLocation(p, "color");
    normalLoc = glGetAttribLocation(p, "normal");
    projMatrixLoc = glGetUniformLocation(p, "projMatrix");
    viewMatrixLoc = glGetUniformLocation(p, "viewMatrix");
    normalMatrixLoc = glGetUniformLocation(p, "normalMatrix");
    ambientColorLoc = glGetUniformLocation(p, "Ambient");
    lightColorLoc = glGetUniformLocation(p, "LightColor");
    lightPositionLoc = glGetUniformLocation(p, "LightPosition");
    ShininessLoc = glGetUniformLocation(p, "Shininess");
    StrengthLoc = glGetUniformLocation(p, "Strength");
    EyeDirectionLoc = glGetUniformLocation(p, "EyeDirection");

    return (p);
}

float deltaAngle = 0.0f;
int xOrigin = -1;


//This event will trigger when you have a mouse button pressed down.
void mouseMove(int x, int y) {
    // x and y is the mouse position.
    //printf("%d ,  %d \n",x,y);
    int motionMode = 1;
    switch (motionMode) {
        case 0:
            /* No mouse button is pressed... do nothing */
            /* return; */
            break;

        case 1:
            /* rotating the view*/
            angle = angle + (x - startX) / 2;
            angle2 = angle2 + (y - startY) / 2;
            startX = x;
            startY = y;
            break;

        case 2:

            break;

        case 3:

            break;
    }

}

//This event occur when you press a mouse button.
void mouseButton(int button, int state, int x, int y) {
    startX = x;
    startY = y;
    selectX = x;
    selectY = y;
    //printf("%d , %d",selectX,selectY);
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is released
        if (state == GLUT_UP) {
            window_width = glutGet(GLUT_WINDOW_WIDTH);
            window_height = glutGet(GLUT_WINDOW_HEIGHT);

            GLbyte color[4];
            GLfloat depth;
            GLuint index;

            glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
                   x, y, color[0], color[1], color[2], color[3], depth, index);
        } else  // state = GLUT_DOWN
        {
        }
    }
}
void keyup(unsigned char key, int x, int y) {
    switch (key) {
        //"a": no shading
        case 97:
            p = initShaders("../vertex.txt", "../frag.txt");
            setupBuffers();
            break;
            //"p": Phong shading
        case 112:
            p = initShaders("../vertex_phong.txt", "../frag_phong.txt");
            setupBuffers();
            break;
            //"g": Gouraud shading
        case 103:
            p = initShaders("../vertex_gouraud.txt", "../frag_gouraud.txt");
            setupBuffers();
            break;
        default:
            break;
    }
}
void init() {
//    viewPosition[0] = 0;
//    viewPosition[1] = 0;
//    viewPosition[2] = 3;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < num_ver; i++) {
        revolver[i] = spinner[i] / scale;
        re_norm[i] = sp_norm[i] / scale;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("ICS Graphics");
    glutSetWindowTitle(s);
    // call back functions
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutKeyboardUpFunc(keyup);
    // check if a particular extension is available on your platform
    glewInit();
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    if (glewIsSupported("GL_VERSION_3_3")) {
        printf("OpenGL 3.3 is supported\n");
    } else {
        printf("OpenGL 3.3 not supported\n");
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init();
    p = initShaders("../vertex.txt", "../frag.txt");
    setupBuffers();
    glutMainLoop();
    return 0;
}
