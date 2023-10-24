#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>


#include <gfx/gfx.h>
#include <terrain/ChunkMap.h>

#include <gfx/Window.h>
#include <Player/Player.h>

#include <chrono>
#include <util/Log.h>

#include <terrain/World.h>
#include <util/Raycast.h>

int main()
{
    gfx::Window window(1920, 1080, "Minecraft Clone");
    Player m_Player;
    terrain::ChunkMap m_ChunkMap(1);
    {
        {
            gfx::Shader shader("res/shaders/default.vert", "res/shaders/default.frag");
    
            std::vector<std::string> paths = { "res/textures/dirt.png", "res/textures/grass_block_side.png", "res/textures/grass_block_side_overlay.png", "res/textures/grass_block_top.png", "res/textures/cobblestone.png"};
            gfx::TextureArray textureArray(paths, 0);
    
           textureArray.texUnit(shader, "tex0");
           textureArray.Bind();
    
            glm::vec4 grassTopColor = glm::vec4(1.0F);
    
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 460");
    
    
            float deltaTime = 0.0f; 
            float lastFrame = 0.0f;
            util::Raycast ray(2);
    
            std::string targetBlock  = "AIR";
    
            while(!glfwWindowShouldClose(window.getWindow())) {
                window.clear();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
            
            
                {
                    double currentFrame = glfwGetTime();
                    deltaTime = currentFrame - lastFrame;
                    lastFrame = currentFrame;
                    glm::ivec2 lastChunkPos = m_Player.m_ChunkPos;
                    m_Player.update(deltaTime);
            
                    if (m_Player.m_ChunkPos != lastChunkPos)
                    {
                        m_ChunkMap.updateChunks(lastChunkPos, m_Player.m_ChunkPos);
                    }
                    
                    m_ChunkMap.RenderChunks(textureArray, shader, m_Player.m_Cam.m_ViewMatrix, m_Player.m_Cam.m_ProjectionMatrix, grassTopColor);
            
                    //auto resultCast = ray.rayCast(world.m_Player.m_Cam.m_Position, world.m_Player.m_Cam.m_Front);
                    //if (resultCast.sucess)
                    //{
                    //    targetBlock = "DIRT";
                    //}
                    //else
                    //{
                    //    targetBlock = "AIR";
                    //}
                }
            
                {
                    ImGui::Begin("Application info");
                    ImGui::Text("Application average %.7f s/frame (%.1f FPS)", deltaTime, ImGui::GetIO().Framerate);
                    ImGui::Text("Position : %f, %f, %f ", m_Player.m_Cam.m_Position.x,m_Player.m_Cam.m_Position.y, m_Player.m_Cam.m_Position.z);
                    //ImGui::Text("ChunkPosition : %d, %d ", world.m_Player.m_ChunkPos.x, world.m_Player.m_ChunkPos.y);
                    ImGui::Text(targetBlock.c_str());
                    ImGui::ColorEdit4("GrassColor", &grassTopColor.x);
                    ImGui::End();
                }
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
                
                window.update();
            };
            
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            
            textureArray.~TextureArray();
            shader.~Shader();
            
           
        }   
    }       


    return 0;
}   
    