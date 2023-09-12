#version 400


uniform vec3 lightPos[50];
uniform vec4 lightColour[50];
uniform float lightR[50];

uniform vec3 cameraPos;

struct directionLight{
	vec3 position;
	vec4 colour;
};

uniform sampler2D diffuseTex;


in Vertex{
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
	vec3 tangent;
	vec3 binormal;
	vec3 worldPos;
} IN;

out vec4 fragColour;

void main(void){
	
	directionLight sun;
	sun.position = vec3(1000,1000,1000);
	sun.colour = vec4(1,1,1,1);
	
	vec4 diffuse = texture(diffuseTex, IN.texCoord);
	vec3 viewDir = normalize(cameraPos - IN.worldPos);

	vec3 incident = normalize((sun.position));
	vec3 halfDir = normalize(incident+viewDir);
		
	float lambert = max(dot(incident, IN.normal), 0.0f);
	
	float specFactor = clamp(dot(halfDir, IN.normal), 0.0, 1.0f);
	specFactor = pow(specFactor,60.0);
	
	vec3 surface = (diffuse.rgb * sun.colour.rgb);
	fragColour.rgb = surface* lambert;
	fragColour.rgb += ((sun.colour.rgb * specFactor));
	fragColour.rgb += surface*0.1f;

	for(int i=0;i<25;i++){
		if(distance(IN.worldPos,lightPos[i]) <=lightR[i]){
		vec3 incident = normalize((lightPos[i] - IN.worldPos));
		vec3 halfDir = normalize(incident+viewDir);
	
	
		float lambert = max(dot(incident, IN.normal), 0.0f);
		float distance = length(lightPos[i]-IN.worldPos);
		float attenuation = 1.0 - clamp(distance/lightR[i], 0.0,1.0);
		
		float specFactor = clamp(dot(halfDir, IN.normal), 0.0, 1.0f);
		specFactor = pow(specFactor,60.0);
		
		vec3 surface = (diffuse.rgb * lightColour[i].rgb);
		fragColour.rgb += surface* lambert* attenuation;
		fragColour.rgb += ((lightColour[i].rgb * specFactor)* attenuation*0.33);
		fragColour.rgb += surface*0.1f;
		
		}
	}

	fragColour.a=diffuse.a;
	
}