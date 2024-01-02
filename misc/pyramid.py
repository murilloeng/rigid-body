from defs import *

x1, x2, x3 = symbols('x1, x2, x3')

xp = [x1, x2, x3]
dx1 = a / 2 * x3 / h
dx2 = b / 2 * x3 / h
M = integrate(p, [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, 0, h])
J1 = integrate(-p * spin(xp), [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, 0, h])
J2 = integrate(-p * spin(xp)**2, [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, 0, h])

print(M)
print(J1)
print(J2)

print(simplify(J2 / M))