#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <terrain/ChunkMap.h>

#include <Player/Player.h>

#include <chrono>
#include <util/Log.h>

#include <thread>
#include <conio.h>

#include <util/Raycast.h>

#include <ui/Crosshair.h>


#define DEBUG_MOI



#ifdef DEBUG_MOI

struct Data
{
    unsigned int vbo;
    Data()
    {
        Dirt block;
        std::vector<glm::vec3> vertices = {glm::vec3(0.0f,0.0f,0.0f)};
        GLCall(glGenBuffers(1, &vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    };
    ~Data()
    {
        GLCall(glDeleteBuffers(1, &vbo));
    };
};

void test()
{
    using namespace std::chrono_literals;
    
    std::vector<Data*> chunkMap;
    chunkMap.push_back(new Data());
    std::this_thread::sleep_for(5000ms);
    chunkMap.push_back(new Data());
    delete chunkMap[0];
    chunkMap.erase(chunkMap.begin());
    delete chunkMap[0];
    std::this_thread::sleep_for(5000ms);
}


void test2()
{
    using namespace std::chrono_literals;
    //DoubleWhooper whopper;
    //whopper.addElement(glm::ivec3(0, 0, 0));
    //std::this_thread::sleep_for(5000ms);
    ////for (int i = 0; i < 500; i++) {
    //whopper.addElement(glm::ivec3(1, 0, 0));
    //whopper.eraseElement(glm::ivec3(0,0,0));
    //    
    ////}
    //std::this_thread::sleep_for(5000ms);
}
#endif

int main() {
    
    gfx::Window window(1920, 1080, "Minecraft Clone");
    {
        //terrain::ChunkMap chunkMap(1);   
#ifdef DEBUG_MOI
        test();
#else
        Player m_Player(glm::vec3(8.0f,2.0f,8.0f));
        {
            {
        
                gfx::Shader shader("res/shaders/default.vert", "res/shaders/default.frag");
        
                std::vector<std::string> paths = {"res/textures/dirt.png", "res/textures/grass_block_side.png",
                                                  "res/textures/grass_block_side_overlay.png",
                                                  "res/textures/grass_block_top.png", "res/textures/cobblestone.png"};


                gfx::TextureArray textureArray(paths, 0);
        
                textureArray.texUnit(shader, "textureArray");
        
                glm::vec4 grassTopColor = glm::vec4(1.0F);
        

                ui::Crosshair crosshair(50.0f);

                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO &io = ImGui::GetIO();
                (void) io;
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
                ImGui_ImplOpenGL3_Init("#version 420");
        
        
                float deltaTime = 0.0f;
                float lastFrame = 0.0f;
                util::Raycast ray(5.0f, &chunkMap);
        
                std::string targetBlock = "AIR";
        
                while (!glfwWindowShouldClose(window.getWindow())) {
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
                    
                        if (m_Player.m_ChunkPos != lastChunkPos) {
                            chunkMap.updateChunks(lastChunkPos, m_Player.m_ChunkPos);
                        }
                    
                        chunkMap.RenderChunks(textureArray, shader, m_Player.m_Cam.m_ViewMatrix,
                                              m_Player.m_Cam.m_ProjectionMatrix, grassTopColor);
                    
                        
                    }

                    crosshair.Render();

                    auto resultCast = ray.rayCast(m_Player.m_Cam.m_Position, m_Player.m_Cam.m_Front);
                    if (resultCast.sucess)
                    {
                        targetBlock = "DIRT";
                    }
                    else
                    {
                        targetBlock = "AIR";
                    }
                    {
                        ImGui::Begin("Application info");
                        ImGui::Text("Application average %.7f s/frame (%.1f FPS)", deltaTime, ImGui::GetIO().Framerate);
                        ImGui::Text("Position : %f, %f, %f ", m_Player.m_Cam.m_Position.x, m_Player.m_Cam.m_Position.y,
                                    m_Player.m_Cam.m_Position.z);
                        ImGui::Text("Ray End Position : %f, %f, %f ", resultCast.position.x, resultCast.position.y,
                            resultCast.position.z);
                        

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
                crosshair.~Crosshair();
            }   
        }

#endif
    }
    window.~Window();
    return 0;
}



