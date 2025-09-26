#include "renderer.h"
#include <stdio.h>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void GLLogError(const char* func, const char* file, int line) {

    unsigned int err;while((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "[OpenGL Error] (0x%x) in %s %s:%d\n",err, func, file, line);
    }

}