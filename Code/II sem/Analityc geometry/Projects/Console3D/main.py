"""
Test Field
"""

from Engine import *

if __name__ == "__main__":
    vc1 = Vector(1.0, 1.0, 1.0)
    vc1 = vc1.normalize()
    print(vc1)

    a = Camera(1, 1, 1, 4)
    print(a.vfov)
