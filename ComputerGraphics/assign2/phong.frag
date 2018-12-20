#version 140
#extension GL_ARB_compatibility: enable

in vec4 p;
in vec3 normal;
in float dist;
// in lightDir

/*
// Light Source 
uniform vec4 LightSourceAmbient;
uniform vec4 LightSourceDiffuse;
uniform vec4 LightSourceSpecular;

// Front Material
uniform vec4 FrontMaterialAmibent;
uniform vec4 FrontMaterialDiffuse;
uniform vec4 FrontMaterialSpecular;

//Light Model
uniform vec4 LightModelAmbient;
uniform vec4 LightModelDiffuse;
uniform vec4 LightModelSpecular;

// Light Attenuation
uniform float LightConstantAttenuation;
uniform float LightLinearAttenuation;
uniform float LightQuadraticAttenuation;
*/
			
uniform vec4 LightSourcePosition;
uniform vec4 specularConst;
uniform vec4 diffuseConst;
uniform vec4 ambientConst;

uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;
uniform float alpha;


void main()
{	

	vec4 v = normalize (-p);
	vec4 n = vec4(normalize(normal) , 0.0);
	vec4 l = normalize (LightSourcePosition - p);
	vec4 r = normalize (-reflect (l , n));
	float att = 1.0 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * dist * dist);
	vec4 ambient =  ambientConst;
	vec4 diffuse = max (dot(l , n) , 0) * diffuseConst;
	diffuse = clamp (diffuse,0.0,1.0);	
	vec4 specular = pow(max(dot(n , l + p), 0), alpha ) * specularConst;
	specular = clamp (specular , 0.0, 1.0);
	

	gl_FragColor = ambient + att * (diffuse  + specular);
				
							
	
}




