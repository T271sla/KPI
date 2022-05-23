import math

class TVector():
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def length(self):
        len = abs(math.sqrt(self.x * self.x + self.y * self.y))
        return len

    def perpen(self, j):
        if (self.x * j.x + self.y * j.y == 0):
            print("Vectors are perpendicular")
        else:
            print("Vectors are not perpendicular")

    def paral(self, j):
        if (self.x / j.x == self.y / j.y):
            return 1
        else:
            return 0

    def print(self):
        print(str(self.x) + " " + str(self.y))

class R2(TVector):
    def __init__(self, x, y):
        super().__init__(x, y)

class R3(TVector):
    def __init__(self, x, y, z):
        super().__init__(x, y)
        self.z = z

    def length3D(self):
        len = abs(math.sqrt(self.x * self.x + self.y * self.y + self.z + self.z))
        return len

    def perpen3D(self, j):
        if (self.x * j.x + self.y * j.y + self.z + j.z == 0):
            return 1
        else:
            return 0



print("Enter 2D vectors:")

for i in range(3):
    x, y = map(int, input().split())
    if i == 0:
        a = R2(x, y)
    if i == 1:
        b = R2(x, y)
    if i == 2:
        c = R2(x, y)

print("\n" + "Enter 3D vectors:")

for i in range(4):
    x, y, z = map(int, input().split())
    if i == 0:
        d = R3(x, y, z)
    if i == 1:
        e = R3(x, y, z)
    if i == 2:
        f = R3(x, y, z)
    if i == 3:
        g = R3(x, y, z)

print("\n")

sum = 0

if (d.paral(a) == 1):
    sum = sum + a.length()
if (d.paral(b) == 1):
    sum = sum + b.length()
if (d.paral(c) == 1):
    sum = sum + c.length()
if (d.paral(e) == 1):
    sum = sum + e.length3D()
if (d.paral(f) == 1):
    sum = sum + f.length3D()
if (d.paral(g) == 1):
    sum = sum + g.length3D()

sum2 = 0
    
if (d.perpen3D(e) == 1):
    sum += e.length3D()
if (d.perpen3D(f) == 1):
    sum += f.length3D()
if (d.perpen3D(g) == 1):
    sum += g.length3D()

print("Sum lengths of parallel vectors: " + str(sum))
print("Sum lengths of perpendicular vectors: " + str(sum2))