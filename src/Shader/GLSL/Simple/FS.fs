#version 440

in vec4 NormalTF;
in vec2 UV_FS; 
in vec4 Tangent_FS;
in vec4 Bitangent_FS;
out vec4 FragColor;

uniform float AmbientIntensity;
uniform vec4 AmbientColor;
uniform float DirectionalIntensity;
uniform vec4 DirectionalColor;
uniform vec3 DirectionalDirection;
uniform sampler2D diffuseTexture;

void main()
{	
	vec3 Normal0 = vec3(NormalTF.x, NormalTF.y, NormalTF.z);
	float DiffuseFactor = dot(normalize(Normal0), -DirectionalDirection);
	 vec4 Diffuse;

    if (DiffuseFactor > 0) {
        Diffuse = DirectionalColor * DirectionalIntensity * DiffuseFactor;
    }
    else {
        Diffuse = vec4(0, 0, 0, 0);
    }
	
	vec4 Ambient = AmbientColor*AmbientIntensity;
	FragColor = texture2D(diffuseTexture, UV_FS)*(Ambient + Diffuse);		
}