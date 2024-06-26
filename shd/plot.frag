#version 460 core

uniform uint width;
uniform uint height;

uniform uint mode;
uniform float time;
uniform float offset;
uniform float x1_min;
uniform float x1_max;
uniform float x2_min;
uniform float x2_max;
uniform float x3_min;
uniform float x3_max;

out vec4 fragment_color;

const float inf = +1.0 / 0.0;
const vec3 color_null = vec3(0.8);

struct interval
{
	float m_min;
	float m_max;
};
const interval empty = interval(0, 0);
bool check_inside(interval i, float v)
{
	return v > i.m_min && v < i.m_max;
}
bool iunion(inout interval i1, inout interval i2)
{
	bool test_1 = check_inside(i1, i2.m_min);
	bool test_2 = check_inside(i1, i2.m_max);
	if(i1 != empty && i2 != empty && (test_1 || test_2))
	{
		i2 = empty;
		i1 = interval(min(i1.m_min, i2.m_min), max(i1.m_max, i2.m_max));
		return true;
	}
	return false;
}
interval intersection(interval i1, interval i2)
{
	if(i1 == empty || i2 == empty || i1.m_max < i2.m_min || i2.m_max < i1.m_min)
	{
		return empty;
	}
	else
	{
		return interval(max(i1.m_min, i2.m_min), min(i1.m_max, i2.m_max));
	}
}

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
	float B = a * pow(wp, 2) - b;
	float C = c * pow(wp, 4) + d * pow(wp, 2) + e;
	return B > 0 && C > 0 && B * B - 4 * C > 0 ? vec3(0, 0, 1) : vec3(1, 0, 0);
}
vec3 vertical_limit(float g1, float g2)
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
	//test 1
	interval i0;
	if(a < 0 && b > 0) i0 = empty;
	if(a > 0 && b < 0) i0 = interval(0, inf);
	if(a < 0 && b < 0) i0 = interval(0, sqrt(b / a));
	if(a > 0 && b > 0) i0 = interval(sqrt(b / a), inf);
	//test 2
	interval i1, i2;
	float d1 = d * d - 4 * c * e;
	float s1 = (-d - sqrt(d1)) / (2 * c);
	float s2 = (-d + sqrt(d1)) / (2 * c);
	if(c > 0 && d1 > 0)
	{
		if(s1 < 0) i1 = empty;
		if(s2 < 0) i2 = interval(0, inf);
		if(s1 > 0) i1 = interval(0, sqrt(s1));
		if(s2 > 0) i2 = interval(sqrt(s2), inf);
	}
	if(c < 0 && d1 > 0)
	{
		i2 = empty;
		if(s2 < 0) i1 = empty;
		if(s1 < 0 && s2 > 0) i1 = interval(0, sqrt(s2));
		if(s1 > 0 && s2 > 0) i1 = interval(sqrt(s1), sqrt(s2));
	}
	if(c < 0 && d1 < 0) i1 = empty, i2 = empty;
	if(c > 0 && d1 < 0) i1 = interval(0, inf), i2 = empty;
	//test 3
	interval i3, i4;
	float p1 = a * a - 4 * c;
	float p3 = b * b - 4 * e;
	float p2 = -(2 * a * b + 4 * d);
	float d2 = p2 * p2 - 4 * p1 * p3;
	float s3 = (-p2 - sqrt(d2)) / (2 * p1);
	float s4 = (-p2 + sqrt(d2)) / (2 * p1);
	if(p1 > 0 && d2 > 0)
	{
		if(s3 < 0) i3 = empty;
		if(s4 < 0) i4 = interval(0, inf);
		if(s3 > 0) i3 = interval(0, sqrt(s3));
		if(s4 > 0) i4 = interval(sqrt(s4), inf);
	}
	if(p1 < 0 && d2 > 0)
	{
		i4 = empty;
		if(s4 < 0) i3 = empty;
		if(s3 < 0 && s4 > 0) i3 = interval(0, sqrt(s4));
		if(s3 > 0 && s4 > 0) i3 = interval(sqrt(s3), sqrt(s4));
	}
	if(p1 < 0 && d2 < 0) i3 = empty, i4 = empty;
	if(p1 > 0 && d2 < 0) i3 = interval(0, inf), i4 = empty;
	//return
	interval[4] set = {
		intersection(intersection(i0, i1), i3),
		intersection(intersection(i0, i1), i4),
		intersection(intersection(i0, i2), i3),
		intersection(intersection(i0, i2), i4)
	};
	while(true)
	{
		bool test = false;
		for(uint i = 0; i < 4; i++)
		{
			for(uint j = i + 1; j < 4; j++)
			{
				test = test || iunion(set[i], set[j]);
			}
		}
		if(!test) break;
	}
	uint count = 0;
	for(uint i = 0; i < 4; i++) if(set[i] != empty) count++;
	return count == 0 ? vec3(1, 0, 0) : count == 1 ? vec3(0, 0, 1) : vec3(0, 1, 0);
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
	fragment_color = 
		mode == 0 ? vec4(vertical(x1, x2, x3), 1) : 
		mode == 1 ? vec4(vertical_limit(x1, x2), 1) : 
		vec4(0, 0, 0, 0);
}