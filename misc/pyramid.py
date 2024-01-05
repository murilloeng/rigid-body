from defs import *

x1, x2, x3 = symbols('x1, x2, x3')

xp = [x1, x2, x3]
dx1 = a * x3 / h / 2 + 3 * a / 8
dx2 = b * x3 / h / 2 + 3 * b / 8
M = integrate(p, [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, -3 * h / 4, h / 4])
J1 = integrate(-p * spin(xp), [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, -3 * h / 4, h / 4])
J2 = integrate(-p * spin(xp)**2, [x1, -dx1, dx1], [x2, -dx2, dx2], [x3, -3 * h / 4, h / 4])

print(M)
print(simplify(J1 / M))
print(simplify(J2 / M))