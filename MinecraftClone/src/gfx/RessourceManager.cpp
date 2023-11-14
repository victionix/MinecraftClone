#include <gfx/RessourceManager.h>
#include <gfx/gfx.h>

//DO NOT INCLUDE THAT IT DOESN'T WORK


std::unordered_map<std::string, std::unique_ptr<gfx::Shader>> gfx::RessourceManager::m_Shaders;
//std::unordered_map<std::string, std::unique_ptr<gfx::Texture>> gfx::RessourceManager::m_Textures;
//std::unique_ptr<gfx::TextureArray> m_TextureArray;

void gfx::RessourceManager::addShader(std::string& vertexPath, std::string& FragmentPath,  std::string& name)
{
	auto shader = std::make_unique<gfx::Shader>(vertexPath.c_str(), FragmentPath.c_str());
	auto it = m_Shaders.emplace(name,shader);
	if (!it.second)
	{
		throw std::runtime_error("Shader already inserted name : " + name);
	}
}

gfx::Shader* gfx::RessourceManager::getShader( std::string& name)
{
	auto shader = m_Shaders.find(name);
	if (shader == m_Shaders.end())
	{
		throw std::runtime_error("Shader not found name : " + name);
	}
	return shader->second.get();
}

//void gfx::RessourceManager::addTexture(std::string& path, int unit,  std::string& name)
//{
//	auto texture = std::make_unique<gfx::Texture>(path,unit);
//	auto it = m_Textures.emplace(name, texture);
//	if (!it.second)
//	{
//		throw std::runtime_error("Texture already inserted name : " + name);
//	}
//}
//
//gfx::Texture* gfx::RessourceManager::getTexture( std::string& name)
//{
//	auto texture = m_Textures.find(name);
//	if (texture == m_Textures.end())
//	{
//		throw std::runtime_error("Texture not found name : " + name);
//	}
//	return texture->second.get();
//}
//
//void gfx::RessourceManager::initTextureArray(const std::vector<std::string>& path, int unit)
//{
//	if (m_TextureArray != nullptr)
//	{
//		throw std::runtime_error("TextureArray already exist");
//	}
//	m_TextureArray = std::make_unique<gfx::TextureArray>(path, unit);
//	util::Log("Texture array has been created");
//}
//
//gfx::TextureArray* gfx::RessourceManager::getTextureArray()
//{
//	if (m_TextureArray == nullptr)
//	{
//		throw std::runtime_error("TextureArray not found ");
//	}
//	return m_TextureArray.get();
//}

void gfx::RessourceManager::free()
{
	m_Shaders.clear();
	//m_Textures.clear();
}
