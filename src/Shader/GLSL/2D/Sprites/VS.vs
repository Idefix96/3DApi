#version 440 compatibility

layout (location = 0) in vec4 Position;
layout (location = 2) in vec2 UV;

out vec2 UV_FS; 

uniform mat4 gTranslation;

void main()
{	
	
	UV_FS = vec2(UV.x, UV.y);
	
	gl_Position = gTranslation*vec4(Position.x, Position.y, 0.0, 1.0);
}