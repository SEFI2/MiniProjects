//
// Passing example
//

#version 140
#extension GL_ARB_compatibility: enable

in vec3 normal_out;




void main()
{	
	vec3 N = normalize (normal_out);
	gl_FragColor = vec4(N * vec3(0 , 0 , 1)  , 1.0);
}