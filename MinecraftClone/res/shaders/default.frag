#version 460 core

layout(location = 0) out vec4 color;

in vec2 u_Texpos;
flat in int u_TexID;
//in float u_TexID;
uniform sampler2DArray tex0;
//Index 0 classic dirt texture
//Index 1 dirt side texture
//Index 2 dirt side overlay texture
//Index 3 dirt top texture

uniform vec4 grassTopColor;

void main()
{
	//Grass top textures
	switch (u_TexID)
	{
	case 1:
		vec4 overlay = texture(tex0,vec3(u_Texpos, 2));
		if (overlay.z > 0)
		{
		color = overlay * grassTopColor;
		break;
		}
		color = texture(tex0,vec3(u_Texpos, u_TexID));
		break;
	case 3:
		color = texture(tex0,vec3(u_Texpos, u_TexID)) * grassTopColor;
		break;
	default:
		color = texture(tex0,vec3(u_Texpos, u_TexID));
		break;
	}

	
};