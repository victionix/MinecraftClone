#ifndef AIR_H
#define AIR_H

#include <Blocks/Block.h>

class Air : public Block
{
public: 
	Air() {
		id = AIR;	
		mesh = BLOCKMESH_NULL;
		facesTextureId = {};
	};
};

#endif