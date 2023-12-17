cmake_minimum_required(VERSION 3.22) # avant WSL c'etait 26
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        MinecraftClone/lib/ImGUI/imgui_widgets.cpp
        MinecraftClone/lib/ImGUI/imgui.cpp
        MinecraftClone/lib/ImGUI/imgui_impl_opengl3.cpp
        MinecraftClone/lib/ImGUI/imgui_tables.cpp
        MinecraftClone/lib/ImGUI/imgui_impl_glfw.cpp
        MinecraftClone/lib/ImGUI/imgui_demo.cpp
        MinecraftClone/lib/ImGUI/imgui_draw.cpp
        MinecraftClone/lib/stb_image/stb_image.cpp
        #./lib/glad/src/glad.c
        #./lib/glm/detail/glm.cpp
        MinecraftClone/src/Blocks/Block.cpp
        MinecraftClone/src/util/Log.cpp
        MinecraftClone/src/util/Camera.cpp
        MinecraftClone/src/util/Raycast.cpp
        MinecraftClone/src/terrain/ChunkMesh.cpp
        MinecraftClone/src/terrain/Chunk.cpp
        MinecraftClone/src/terrain/ChunkMap.cpp
        MinecraftClone/src/terrain/World.cpp
        MinecraftClone/src/terrain/WorldGenerator.cpp
        MinecraftClone/src/gfx/Buffers/IndexBuffer.cpp
        MinecraftClone/src/gfx/Buffers/VertexBuffer.cpp
        MinecraftClone/src/gfx/Debug/Debug.cpp
        #MinecraftClone/src/gfx/Mesh.cpp
        MinecraftClone/src/gfx/Window.cpp
        #./src/gfx/RessourceManager.cpp
        MinecraftClone/src/gfx/Arrays/VertexArray.cpp
        MinecraftClone/src/gfx/Shaders/Shader.cpp
        MinecraftClone/src/gfx/Texture/Texture.cpp
        MinecraftClone/src/Player/Player.cpp
        MinecraftClone/main.cpp
)


add_executable(MinecraftClone ${SOURCE_FILES})

target_include_directories(MinecraftClone
        PRIVATE
        Dependencies/GL/include
        Dependencies/GLFW/include
        MinecraftClone/lib
        MinecraftClone/include
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/lib
)

set(GLFW3_LIBRARY C:/Users/Victor/Documents/CodingProject/COrC++/OpenGL/MinecraftClone/Dependencies/GLFW/lib-mingw-w64/libglfw3.a )
set(GLEW_LIB
        C:/Users/Victor/Documents/CodingProject/COrC++/OpenGL/MinecraftClone/Dependencies/GL/x64/glew32.lib
        C:/Users/Victor/Documents/CodingProject/COrC++/OpenGL/MinecraftClone/Dependencies/GL/x64/glew32s.lib
)
#set(OPENGL_LIB C:/windows/system32/opengl32.dll  C:/windows/system32/glu32.dll)

target_link_libraries(MinecraftClone
        PUBLIC
        glfw #glfw3 #${GLFW3_LIBRARY}
        GLEW# glew  #${GLEW_LIB}
        #       ${OPENGL_LIB}
        GL #opengl32
        GLU #glu32
)

file(COPY MinecraftClone/res DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY Dependencies/GL/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
