#version 460 core

uniform uint width;
uniform uint height;

uniform float time;
uniform float offset;
uniform float x1_min;
uniform float x1_max;
uniform float x2_min;
uniform float x2_max;
uniform float x3_min;
uniform float x3_max;

out vec4 fragment_color;

const vec3 color_null = vec3(0.8);

vec3 vertical(float g1, float g2, float wp)
{
	//check
	if(abs(g1 - g2) > 1 || g1 + g2 < 1)
	{
		return color_null;
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
vec3 tilted_1(float g1, float g2, float wp)
{
	//check
	if(abs(g1 - g2) > 1 || g1 + g2 < 1)
	{
		return color_null;
	}
	//data
	float c = (g2 - g1) * (g2 - 1) / g1;
	float a = (g2 * g2 - g2 - g1 * g2 + 2 * g1) / g1;
	float e = 3 * (g1 - g2) / g1 / g2 / pow(g2 - 1, 2);
	float d = (3 - 2 * g2) * (g1 - g2) / g1 / g2 / (g2 - 1);
	float b = (g1 * g2 + 2 * g1 - g2 * g2 + g2 - 1) / g1 / g2 / (g2 - 1);
	//return
	float B = (a * pow(wp, 4) + b) / pow(wp, 2);
	float C = (c * pow(wp, 8) + d * pow(wp, 4) + e) / pow(wp, 4);
	return B > 0 && C > 0 && B * B - 4 * C > 0 ? vec3(0, 0, 1) : vec3(1, 0, 0);
}

void main(void)
{
	uint w = width;
	uint h = height;
	float s = 1 - offset;
	float d = offset / 2;
	float x3 = (x3_max - x3_min) * time + x3_min;
	float x1 = (x1_max - x1_min) / s * (gl_FragCoord.x / w - d) + x1_min;
	float x2 = (x2_max - x2_min) / s * (gl_FragCoord.y / h - d) + x2_min;
	fragment_color = vec4(vertical(x1, x2, x3), 1);
}