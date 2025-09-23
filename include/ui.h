#ifndef UI_H
#define UI_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING   // <-- this one is critical for nk_font_atlas
#define NK_INCLUDE_DEFAULT_FONT


#include <GLFW/glfw3.h>
#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

struct nk_glfw glfw;
struct nk_context* ctx;


void initUI(GLFWwindow* window);
void startRenderUI();
void endRenderUI();
void quitUI();

#endif // UI_H