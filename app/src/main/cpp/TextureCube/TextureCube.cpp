//
// Created by Lilong Zhang on 2023/4/18.
//
#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "../Matrix/Matrix.h"
#include "Texture.h"

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
namespace textureCube
{
    /* [shaders] */
    static const char glVertexShader[] =
            "attribute vec4 vertexPosition;\n"
            "attribute vec2 vertexTextureCord;\n"
            "varying vec2 textureCord;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 modelView;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * modelView * vertexPosition;\n"
            "    textureCord = vertexTextureCord;\n"
            "}\n";

    static const char glFragmentShader[] =
            "precision mediump float;\n"
            "uniform sampler2D texture;\n"
            "varying vec2 textureCord;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, textureCord);\n"
            "}\n";

    /* [shaders] */

    GLuint loadShader(GLenum shaderType, const char *shaderSource)
    {
        GLuint shader = glCreateShader(shaderType);
        if (shader != 0)
        {
            glShaderSource(shader, 1, &shaderSource, NULL);
            glCompileShader(shader);

            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

            if (compiled != GL_TRUE)
            {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen > 0)
                {
                    char *logBuffer = (char *) malloc(infoLen);

                    if (logBuffer != NULL)
                    {
                        glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                        LOGE("Could not Compile Shader %d:\n%s\n", shaderType, logBuffer);
                        free(logBuffer);
                        logBuffer = NULL;
                    }

                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }

        return shader;
    }

    GLuint createProgram(const char *vertexSource, const char *fragmentSource)
    {
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
        if (vertexShader == 0)
        {
            return 0;
        }

        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
        if (fragmentShader == 0)
        {
            return 0;
        }

        GLuint program = glCreateProgram();

        if (program != 0)
        {
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

            if (linkStatus != GL_TRUE)
            {
                GLint bufLength = 0;

                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

                if (bufLength > 0)
                {
                    char *logBuffer = (char *) malloc(bufLength);

                    if (logBuffer != NULL)
                    {
                        glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                        LOGE("Could not link program:\n%s\n", logBuffer);
                        free(logBuffer);
                        logBuffer = NULL;
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
        return program;
    }

    GLuint glProgram;
    GLuint vertexLocation;
    GLuint samplerLocation;
    GLuint projectionLocation;
    GLuint modelViewLocation;
    GLuint textureCordLocation;
    GLuint textureId;

    float projectionMatrix[16];
    float modelViewMatrix[16];
    float angle = 0;

/* [setupGraphicsUpdate] */
    bool setupGraphics(int width, int height)
    {
        glProgram = createProgram(glVertexShader, glFragmentShader);

        if (!glProgram)
        {
            LOGE ("Could not create program");
            return false;
        }

        vertexLocation = glGetAttribLocation(glProgram, "vertexPosition");
        textureCordLocation = glGetAttribLocation(glProgram, "vertexTextureCord");
        projectionLocation = glGetUniformLocation(glProgram, "projection");
        modelViewLocation = glGetUniformLocation(glProgram, "modelView");
        samplerLocation = glGetUniformLocation(glProgram, "texture");

        /* Setup the perspective. */
        matrixPerspective(projectionMatrix, 45, (float) width / (float) height, 0.1f, 100);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, width, height);

        /* Load the Texture. */
        textureId = loadSimpleTexture();
        if (textureId == 0)
        {
            return false;
        } else
        {
            return true;
        }
    }
/* [setupGraphicsUpdate] */
/* [verticesAndTexture] */
    GLfloat cubeVertices[] = {-1.0f, 1.0f, -1.0f, /* Back. */
                              1.0f, 1.0f, -1.0f,
                              -1.0f, -1.0f, -1.0f,
                              1.0f, -1.0f, -1.0f,
                              -1.0f, 1.0f, 1.0f, /* Front. */
                              1.0f, 1.0f, 1.0f,
                              -1.0f, -1.0f, 1.0f,
                              1.0f, -1.0f, 1.0f,
                              -1.0f, 1.0f, -1.0f, /* Left. */
                              -1.0f, -1.0f, -1.0f,
                              -1.0f, -1.0f, 1.0f,
                              -1.0f, 1.0f, 1.0f,
                              1.0f, 1.0f, -1.0f, /* Right. */
                              1.0f, -1.0f, -1.0f,
                              1.0f, -1.0f, 1.0f,
                              1.0f, 1.0f, 1.0f,
                              -1.0f, 1.0f, -1.0f, /* Top. */
                              -1.0f, 1.0f, 1.0f,
                              1.0f, 1.0f, 1.0f,
                              1.0f, 1.0f, -1.0f,
                              -1.0f, -1.0f, -1.0f, /* Bottom. */
                              -1.0f, -1.0f, 1.0f,
                              1.0f, -1.0f, 1.0f,
                              1.0f, -1.0f, -1.0f
    };

    GLfloat textureCords[] = {1.0f, 1.0f, /* Back. */
                              0.0f, 1.0f,
                              1.0f, 0.0f,
                              0.0f, 0.0f,
                              0.0f, 1.0f, /* Front. */
                              1.0f, 1.0f,
                              0.0f, 0.0f,
                              1.0f, 0.0f,
                              0.0f, 1.0f, /* Left. */
                              0.0f, 0.0f,
                              1.0f, 0.0f,
                              1.0f, 1.0f,
                              1.0f, 1.0f, /* Right. */
                              1.0f, 0.0f,
                              0.0f, 0.0f,
                              0.0f, 1.0f,
                              0.0f, 1.0f, /* Top. */
                              0.0f, 0.0f,
                              1.0f, 0.0f,
                              1.0f, 1.0f,
                              0.0f, 0.0f, /* Bottom. */
                              0.0f, 1.0f,
                              1.0f, 1.0f,
                              1.0f, 0.0f
    };
/* [verticesAndTexture] */

    GLushort indicies[] = {0, 3, 2, 0, 1, 3, 4, 6, 7, 4, 7, 5, 8, 9, 10, 8, 11, 10, 12, 13, 14, 15,
                           12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22};

    void renderFrame()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        matrixIdentityFunction(modelViewMatrix);

        matrixRotateX(modelViewMatrix, angle);
        matrixRotateY(modelViewMatrix, angle);

        matrixTranslate(modelViewMatrix, 0.0f, 0.0f, -10.0f);

        glUseProgram(glProgram);
        glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices);
        glEnableVertexAttribArray(vertexLocation);

        /* [enableAttributes] */
        glVertexAttribPointer(textureCordLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCords);
        glEnableVertexAttribArray(textureCordLocation);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);

        /* Set the sampler texture unit to 0. */
        glUniform1i(samplerLocation, 0);
        /* [enableAttributes] */
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indicies);

        angle += 1;
        if (angle > 360)
        {
            angle -= 360;
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_openglesdemo_cver_NativeLibrary_stepTextureCube(JNIEnv *env, jclass clazz)
{
    textureCube::renderFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_openglesdemo_cver_NativeLibrary_initTextureCube(JNIEnv *env, jclass clazz,
                                                                jint width,
                                                                jint height)
{
    textureCube::setupGraphics(width, height);
}
