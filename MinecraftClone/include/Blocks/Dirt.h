#ifndef DIRT_H
#define DIRT_H

#include <Blocks/Block.h>

class Dirt :public Block
{
public:
	static Dirt* get() {
		static Dirt inst;
		return &inst;
	}
	Dirt() {
		id = DIRT;
		mesh = BLOCKMESH_DEFAULT;
		facesTextureId = { 1,1,1,1,0,3 };
	};
};




#endif