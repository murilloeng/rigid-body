#version 460 core

uniform uint frame;
uniform uint width;
uniform uint height;

uniform float x1_min;
uniform float x1_max;
uniform float x2_min;
uniform float x2_max;
uniform float x3_min;
uniform float x3_max;

out vec4 fragment_color;

vec3 vertical_g1_g2(float g1, float g2, float wp)
{
	//check
	if(abs(g1 - g2) > 1 || g1 + g2 < 1)
	{
		return vec3(0, 0, 0);
	}
	//data
	float e = 1 / (g1 * g2);
	float b = (g1 + g2) / (g1 * g2);
	float d = (g1 + g2 - 2) / (g1 * g2);
	float c = (g1 * g2 - g1 - g2 + 1) / (g1 * g2);
	float a = (2 * g1 * g2 - g1 - g2 + 1) / (g1 * g2);
	//return
	float B = a * wp * wp - b;
	float C = c * wp * wp * wp * wp + d * wp * wp + e;
	return B > 0 && C > 0 && B * B - 4 * C > 0 ? vec3(0, 0, 1) : vec3(1, 0, 0);
}

void main(void)
{
	uint n_frames = 200;
	float x1 = (x1_max - x1_min) * gl_FragCoord.x / width + x1_min;
	float x2 = (x2_max - x2_min) * gl_FragCoord.y / height + x2_min;
	float x3 = (x3_max - x3_min) * mod(frame, n_frames) / n_frames + x3_min;
	fragment_color = vec4(vertical_g1_g2(x1, x2, x3), 1);
}