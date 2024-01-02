from defs import *

t1, t2 = symbols('t1, t2')

x3 = r * cos(t2)
x1 = r * cos(t1) * sin(t2)
x2 = r * sin(t1) * sin(t2)

J = zeros(3, 3)
J[0, 1] = diff(x1, r)
J[1, 1] = diff(x2, r)
J[2, 1] = diff(x3, r)
J[0, 0] = diff(x1, t1)
J[1, 0] = diff(x2, t1)
J[2, 0] = diff(x3, t1)
J[0, 2] = diff(x1, t2)
J[1, 2] = diff(x2, t2)
J[2, 2] = diff(x3, t2)

d = simplify(det(J))

xp = [x1, x2, x3]
M = integrate(p * d, [r, 0, R], [t1, 0, 2 * pi], [t2, 0, pi])
J1 = integrate(-p * d * spin(xp), [r, 0, R], [t1, 0, 2 * pi], [t2, 0, pi])
J2 = integrate(-p * d * spin(xp)**2, [r, 0, R], [t1, 0, 2 * pi], [t2, 0, pi])

print(M)
print(J1)
print(J2)