#ifndef SAFEMESH_H
#define SAFEMESH_H

#include <memory>
#include <mutex>
#include <vector>

namespace gfx {
	class Mesh;
}

class SafeMesh {

public:
	SafeMesh(std::unique_ptr<gfx::Mesh> mesh);
	~SafeMesh();

	gfx::Mesh* get();

	static void update();

private:
	std::unique_ptr<gfx::Mesh> mesh;
	static std::vector<std::unique_ptr<gfx::Mesh>> destructions;
};

#endif