from sympy import *
from sympy.abc import *

pi = acos(-1)

def spin(v):
	return Matrix([
		[0, -v[2], v[1]],
		[v[2], 0, -v[0]],
		[-v[1], v[0], 0]
	])