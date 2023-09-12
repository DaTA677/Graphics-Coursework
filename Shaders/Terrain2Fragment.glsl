#version 330 core

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specTex;
uniform sampler2D splatMap;

uniform vec3 lightPos[50];
uniform vec4 lightColour[50];
uniform float lightR[50];

uniform vec3 cameraPos;

uniform sampler2D extraTex[3];
uniform sampler2D extraNor[3];
uniform sampler2D extraSpec[3];



uniform float waterCycle;
uniform float waterRotate;


struct directionLight{
	vec3 position;
	vec4 colour;
};


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
	
	vec3 viewDir = normalize(cameraPos - IN.worldPos);

	mat3 TBN = mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));

	vec3 bumpNormal = vec3(0,0,0);
	  
	//vec3 spec= texture(specTex, IN.texCoord).rgb;
	


	vec3 incident = normalize((sun.position));
	vec3 halfDir = normalize(incident+viewDir);
	

	fragColour = vec4(0,0,0,1);
	
	vec3 colour = texture(splatMap,IN.texCoord/8.0).xyz;
	vec2 waterTexCoord = IN.texCoord;
	
	if(colour.r>0){
		vec3 bumpNormal1 = texture(extraNor[0], IN.texCoord).rgb;
		bumpNormal1 = normalize(TBN * normalize(bumpNormal1* 2.0 -1.0));
		bumpNormal = bumpNormal1;
	}
	if(colour.b>0.0){
		/*mat4 scaleMatrix;
		mat4 translate;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				scaleMatrix[i][j]=0;
				translate[i][j]=0;
			}
		}
		for(int i =0;i<3;i++) scaleMatrix[i][i]=5;
		scaleMatrix[3][3]=1;

		translate[3][0] = waterCycle;
		translate[3][2] = waterCycle;
		translate[3][3] = 1;
		waterTexCoord = (translate*scaleMatrix*vec4(waterTexCoord,0.0,1.0)).xy *2 -1.0;*/

		
		
		if(IN.worldPos.y>0.0){
			float x = waterTexCoord.x - waterRotate;
			float y = waterTexCoord.y + waterCycle;
			waterTexCoord = vec2(x,y);
		}
		else{
			float x = waterTexCoord.x;
			float y = waterTexCoord.y - waterCycle;
			waterTexCoord = vec2(x,y);
		}
		vec3 bumpNormal1 = texture(extraNor[1], waterTexCoord).rgb;
		bumpNormal1 = normalize(TBN * normalize(bumpNormal1* 2.0 -1.0));
		bumpNormal = bumpNormal1;

	}
	
	if(colour.g>0){
		vec3 bumpNormal1 = texture(extraNor[2], IN.texCoord).rgb;
		bumpNormal1 = normalize(TBN * normalize(bumpNormal1* 2.0 -1.0));
		bumpNormal = bumpNormal1;
	}
	
	if(colour.r ==0 && colour.g==0&&colour.b==0){
		bumpNormal = texture(normalTex, IN.texCoord).rgb;
		bumpNormal = normalize(TBN * normalize(bumpNormal* 2.0 -1.0));
	}

	vec4 tex1 = texture(extraTex[0],IN.texCoord);
	vec4 tex2 = texture(extraTex[1], waterTexCoord);
	vec4 tex3 = texture(extraTex[2],IN.texCoord);



	vec4 diffuse=mix(mix(mix(texture(diffuseTex, IN.texCoord),tex1,colour.r),tex2,colour.b),tex3,colour.g);
	
	
	float specFactor = clamp(dot(halfDir, bumpNormal), 0.0, 1.0f);
	specFactor = pow(specFactor,60.0);
	
	float lambert = max(dot(incident, bumpNormal), 0.0f);
	
	
	
	vec3 surface = (diffuse.rgb * sun.colour.rgb);
	fragColour.rgb = surface* lambert;
	fragColour.rgb += ((sun.colour.rgb * specFactor));
	fragColour.rgb += surface*0.1f;
	
	for(int i=25;i<50;i++){
		if(distance(IN.worldPos,lightPos[i]) <=lightR[i]){
		vec3 incident = normalize((lightPos[i] - IN.worldPos));
		vec3 halfDir = normalize(incident+viewDir);
	
	
		float lambert = max(dot(incident, bumpNormal), 0.0f);
		float distance = length(lightPos[i]-IN.worldPos);
		float attenuation = 1.0 - clamp(distance/lightR[i], 0.0,1.0);
		
		float specFactor = clamp(dot(halfDir, bumpNormal), 0.0, 1.0f);
		specFactor = pow(specFactor,60.0);
		
		vec3 surface = (diffuse.rgb * lightColour[i].rgb);
		fragColour.rgb += surface* lambert* attenuation;
		fragColour.rgb += ((lightColour[i].rgb * specFactor)* attenuation*0.33);
		fragColour.rgb += surface*0.1f;
		
		}
	}
	
	fragColour.a = diffuse.a;
	
}