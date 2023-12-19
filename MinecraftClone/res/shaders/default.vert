#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 v_Texpos;
layout(location = 2) in int v_TexID;



out vec2 u_Texpos;
flat out int u_TexID;

uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat4 u_Projection;



void main()
{
	u_Texpos = v_Texpos;
	u_TexID = v_TexID;

	gl_Position = (u_Projection * u_View * u_Model) * vec4(position);
}


