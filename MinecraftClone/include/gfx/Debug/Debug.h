#ifndef DEBUG_H
#define DEBUG_H

#include <assert.h>
#include <stdint.h>
#include <GL/glew.h>
#include <thread>


#define ASSERT(x) if (!(x)) assert(false);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())
#define INT2VOIDP(i) (void*)(uintptr_t)(i)
void GLClearError();
bool GLCheckError();


static const std::thread::id mainThread = std::this_thread::get_id();
static const auto nbrAvailableThreads = std::thread::hardware_concurrency();


#endif