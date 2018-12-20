#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

out vec3 normal, lightDir;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;
uniform vec4 LightSourcePosition;


void main()
{	
	mat4 normalMatrix = transpose(inverse(ModelViewMatrix));
	normal = normalize ( vec3(normalMatrix * vec4(gl_Normal , 0.0)) );
	lightDir = normalize(vec3(LightSourcePosition - ModelViewMatrix * gl_Vertex));				
	gl_Position = ProjectionMatrix * ModelViewMatrix * gl_Vertex;
}
