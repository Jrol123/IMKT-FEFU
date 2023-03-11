"""
Test Field
"""

from Engine import *

if __name__ == "__main__":
    vc1 = Vector(1.0, 2.0, 3.0)
    vc2 = Vector(2.0, 3.0, 4.0)
    vc3 = Vector(0.0, 1.0, 0.0)
    vc1 = vc1.normalize()
    vc2 = vc2.normalize()
    vc3 = vc3.normalize()
    print(vc1, vc1.length())
    print(vc2, vc2.length())
    print(vc3, vc3.length())
    print()

    a = Camera(1, 1, 1, 4)
    print(a.vfov)
