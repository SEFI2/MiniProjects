//
// Passing example with per-vertex coloring
//

#version 150
#extension GL_ARB_compatibility: enable
#extension GL_ARB_arrays_of_arrays: enable
 
out vec3 normal_out;

uniform int level;

layout(triangles) in;
layout(triangle_strip, max_vertices = 300) out;
 
 
int pascals[2][18];
	
void main() 
{
    
	vec3 A = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	
	
	
	normal_out = normalize(cross(A,B));
	int layers = (1 << level);
	
	float left_d = length(A) / float(layers);
	float right_d = length(B) / float(layers);

	A = normalize(A);
	B = normalize(B);
	
	
	
	vec3 left_current = gl_in[0].gl_Position.xyz;
	vec3 right_current = gl_in[0].gl_Position.xyz;
	pascals[1][0] = 1;
	
	for (int i = 1 ; i <= layers ; ++i) {
			
			vec3 from_left = left_current , dir = right_current - left_current;
			
			float d = length (dir) / (i==1?1 : i - 1);
			dir = normalize(dir);
								
			pascals[(i + 1) % 2][0] = 0;
			for (int j = 0 ; j < i ; ++j) {
				pascals[(i + 1) % 2][j + 1] = 0;
			}
													
			for (int j = 0 ; j < i ; ++j) {
				if (pascals[i % 2][j] % 2 == 1) {
					gl_Position = vec4 (from_left , 1);
					EmitVertex();
					gl_Position = vec4 (from_left + A * left_d , 1);
					EmitVertex();
					gl_Position = vec4 (from_left + B * right_d, 1);
					EmitVertex();					
					EndPrimitive();
				}
				pascals[(i + 1) % 2][j + 1] += pascals[i % 2][j];
				pascals[(i + 1) % 2][j] += pascals[i % 2][j];
				from_left += dir * d;
			}
		
			left_current += A * left_d;
			right_current += B * right_d;
	}
		
}
