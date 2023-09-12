#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 textureMatrix;

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec4 colour;

out Vertex{
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
	vec3 worldPos;

}OUT;


void main(void)	{
	OUT.texCoord = (textureMatrix* vec4(texCoord,0.0,1.0)).xy;

	OUT.colour=colour;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

	OUT.normal= normalize(normalMatrix * normalize(normal));

	vec4 worldPos = (modelMatrix*vec4(position,1));

	OUT.worldPos = worldPos.xyz;

	gl_Position=  (projMatrix*viewMatrix)* worldPos;

}