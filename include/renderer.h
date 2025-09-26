#pragma once
#include <glad/glad.h>

void GLClearError();
void GLLogError(const char* func, const char* file, int line);

#ifndef NDEBUG   // --- DEBUG MODE ---

#define GLCALL(x) do { \
    GLClearError(); \
    x; \
    GLLogError(#x, __FILE__, __LINE__); \
} while (0)

#else   // --- RELEASE MODE ---

#define GLCALL(x) x

#endif
