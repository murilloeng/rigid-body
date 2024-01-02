from defs import *

x3 = z
x1 = r * cos(t)
x2 = r * sin(t)

J = zeros(3, 3)
J[0, 0] = diff(x1, r)
J[1, 0] = diff(x2, r)
J[2, 0] = diff(x3, r)
J[0, 1] = diff(x1, t)
J[1, 1] = diff(x2, t)
J[2, 1] = diff(x3, t)
J[0, 2] = diff(x1, z)
J[1, 2] = diff(x2, z)
J[2, 2] = diff(x3, z)

d = simplify(det(J))

xp = [x1, x2, x3]
M = integrate(p * d, [r, 0, R], [t, 0, 2 * pi], [z, -h / 2, h / 2])
J1 = integrate(-p * d * spin(xp), [r, 0, R], [t, 0, 2 * pi], [z, -h / 2, h / 2])
J2 = integrate(-p * d * spin(xp)**2, [r, 0, R], [t, 0, 2 * pi], [z, -h / 2, h / 2])

print(M)
print(J1)
print(J2)