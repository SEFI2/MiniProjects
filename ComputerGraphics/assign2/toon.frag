#version 140
#extension GL_ARB_compatibility: enable

in vec3 normal, lightDir;
uniform float range;
			
void main()
{	
	vec4 color;
	float intensity = dot (lightDir , normalize (normal));
	float Range = range + 1;
	
	float rangeIndex = Range;
	
			
	gl_FragColor = vec4(1.0,0.5,1.0,1.0);
	while (rangeIndex >= 1)
	{
		if ( intensity > rangeIndex / Range )
		{
			gl_FragColor = vec4(1.0/rangeIndex,0.5/rangeIndex,1.0/rangeIndex,1.0);
			break;
		}
		rangeIndex -= 1.0;
	}	
}