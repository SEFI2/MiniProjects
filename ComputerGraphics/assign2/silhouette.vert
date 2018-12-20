#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

uniform float thickness;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
		


void main()
{	
	vec3 normal = normalize ( vec3(transpose(inverse(ModelViewMatrix)) * vec4(gl_Normal , 0.0)) );
	gl_Position = ProjectionMatrix * ModelViewMatrix * (gl_Vertex + vec4(thickness * normal , 0.0));
}
