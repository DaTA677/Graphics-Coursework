#version 330 core

uniform sampler2D diffuseTex;
uniform samplerCube cubeTex;

uniform vec3 lightPos[50];
uniform vec4 lightColour[50];
uniform float lightR[50];

uniform float waterCycle;
uniform float waterRotate;

uniform vec3 cameraPos;

in Vertex{
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
	vec3 worldPos;
} IN;

out vec4 fragColour;

void main(void){
	vec2 waterTexCoord = IN.texCoord;

	waterTexCoord.x = waterTexCoord.x - waterRotate;
	waterTexCoord.y = waterTexCoord.y + waterCycle;
			
			
	vec4 diffuse = texture(diffuseTex, waterTexCoord);
	
	
	vec3 viewDir = normalize(cameraPos - IN.worldPos);
	vec3 reflectDir = reflect(-viewDir, normalize(IN.normal));
	vec4 reflectTex = texture(cubeTex, reflectDir);


	diffuse = reflectTex + (diffuse*0.25f);
	fragColour.rgb= diffuse.rgb;
	
	for(int i=25;i<50;i++){
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