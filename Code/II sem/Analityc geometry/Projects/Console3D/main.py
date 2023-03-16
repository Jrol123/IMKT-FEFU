"""
Test Field
"""

import Engine

if __name__ == "__main__":
    vc1 = Engine.Vector(1, 2, 3)
    vc2 = .Vector(1.0, 2.0, 3.0)
    vc3 = Vector(0.0, 1.0, 0.0)
    vc1 = vc1.normalize()
    vc2 = vc2.normalize()
    vc3 = vc3.normalize()
    print(vc1, vc1.length())
    print(vc2, vc2.length())
    print(vc3, vc3.length())
    print()

    c = Object.PCube()

    b = VectorSpace(Point(1, 2, 3), vc1, vc2, vc3)
    a = Vector(0, 10, 23).normalize()
