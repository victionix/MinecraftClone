#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

//DO NOT INCLUDE THAT IT DOESN'T WORK

#include <unordered_map>
#include <string>
#include <util/Log.h>
#include <gfx/gfx.h>



namespace gfx {
	class RessourceManager {
	public:
		RessourceManager() {};
		~RessourceManager() { free(); };

		static void addShader(std::string& vertexPath,std::string& FragmentPath,  std::string& name);
		static gfx::Shader* getShader(std::string& name);

		//static void addTexture(std::string& path, int unit,  std::string& name);
		//static gfx::Texture* getTexture(std::string& name);
		//
		//static void initTextureArray(const std::vector<std::string>& path, int unit);
		//static gfx::TextureArray* getTextureArray();

		static void free();
	private:
		static std::unordered_map<std::string, std::unique_ptr<gfx::Shader>> m_Shaders;
		//static std::unordered_map<std::string, std::unique_ptr<gfx::Texture>> m_Textures;

//		static std::unique_ptr<gfx::TextureArray> m_TextureArray;
	};
};

#endif