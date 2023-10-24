#include <gfx/SafeMesh.h>

#include <utility>
#include <gfx/Mesh.h>

std::vector<std::unique_ptr<gfx::Mesh>> SafeMesh::destructions;

SafeMesh::SafeMesh(std::unique_ptr<gfx::Mesh> mesh)
	: mesh(std::move(mesh))
{}

SafeMesh::~SafeMesh() {
	destructions.push_back(std::move(mesh));
}

void SafeMesh::update() {
	destructions.clear();
}

gfx::Mesh* SafeMesh::get() {
	return mesh.get();
}