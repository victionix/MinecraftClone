#ifndef DIRT_H
#define DIRT_H

#include <Blocks/Block.h>

class Dirt :public Block
{
public:
	Dirt() {
		id = DIRT;
		mesh = BLOCKMESH_DEFAULT;
		facesTextureId = { 1,1,1,1,0,3 };
	};
};




#endif