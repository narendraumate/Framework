//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C5E1v_basicLight
//

#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;

out vec4 vColor;

uniform mat3 worldViewNorm;
uniform mat4 worldViewProjection;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
//uniform vec3 transmittance;
uniform vec3 emission;
uniform float shininess;
//uniform float ior;
uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;

void main()
{
	gl_Position = worldViewProjection * vec4(position, 1.0);
	vec4 vPosition = gl_Position;
	vec3 P = vPosition.xyz;
	vec3 N = normalize(worldViewNorm * normal);
	vec3 emission_ = emission;
	vec3 ambient_ = ambient * texture(ambientTextureSampler, texcoord).rgb;
	vec3 L = normalize(lightPosition - P);
	float diffuseLight = max(dot(N, L), 0);
	vec3 diffuse_ = diffuse * texture(diffuseTextureSampler, texcoord).rgb * lightColor * diffuseLight;
	vec3 V = normalize(eyePosition - P);
	vec3 H = normalize(L + V);
	float specularLight = 0.0;
	if (diffuseLight <= 0.0)
	{
		specularLight = 0.0;
	}
	else
	{
		specularLight = pow(max(dot(N, H), 0), shininess);
	}
	vec3 specular_ = specular * texture(specularTextureSampler, texcoord).rgb * lightColor * specularLight;
	vColor = vec4(emission_ + ambient_ + diffuse_ + specular_, 1);
}
