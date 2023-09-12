#version 330 core

uniform vec4 nodeColour;

in Vertex{
	vec2 texCoord;
	vec4 colour;

}IN;

out vec4 fragColour;

void main(void){

  fragColour=nodeColour;
	
}