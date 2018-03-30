#version 440 compatibility

in vec2 UV_FS; 

out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform bool hasTexture;
uniform bool hasMaterialColor;
uniform vec4 materialColor;

void main()
{	
	if (hasTexture)
		FragColor = texture2D(diffuseTexture, UV_FS);
	else 
		if (hasMaterialColor)
		{
			FragColor = materialColor;
		}
	else
		FragColor = vec4(0.1, 0.1, 0.1, 0.6); 
}