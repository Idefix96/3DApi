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
uniform sampler2D normalMap;
uniform bool hasTexture;
uniform bool hasNormalMap;

void main()
{	
	vec3 Normal0 = normalize(vec3(NormalTF.x, NormalTF.y, NormalTF.z));
	if (hasNormalMap)
	{		
		vec3 Tangent0 = normalize(vec3(Tangent_FS.x, Tangent_FS.y, Tangent_FS.z));
		Tangent0 = normalize(Tangent0 - dot(Tangent0, Normal0) * Normal0);
		vec3 Bitangent0 = normalize(vec3(Bitangent_FS.x, Bitangent_FS.y, Bitangent_FS.z));
		vec3 BumpMapNormal = texture(normalMap, UV_FS).xyz;
		BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
		vec3 NewNormal;
		mat3 TBN = mat3(Tangent0, Bitangent0, Normal0);
		NewNormal = TBN * BumpMapNormal;
		Normal0 = normalize(NewNormal);
	}
	float DiffuseFactor = dot(normalize(Normal0), -DirectionalDirection);
	vec4 Diffuse;
	
    if (DiffuseFactor > 0) {
        Diffuse = DirectionalColor * DirectionalIntensity * DiffuseFactor;
    }
    else {
        Diffuse = vec4(0, 0, 0, 0);
    }
	
	vec4 Ambient = AmbientColor*AmbientIntensity;
	if (hasTexture)
		FragColor = texture2D(diffuseTexture, UV_FS)*(Ambient + Diffuse);	
	else
		FragColor = vec4(1.0,1.0,1.0,1.0)*(Ambient + Diffuse);	
}