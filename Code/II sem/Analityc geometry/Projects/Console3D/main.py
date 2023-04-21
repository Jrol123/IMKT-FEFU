"""
Зона тестирования
"""

import HighObjects
import LowObjects

if __name__ == "__main__":
    vector1 = LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 0)
    bp = HighObjects.BoundedPlane(LowObjects.Point(0, 0, 0), LowObjects.Vector(0, 0, 2).normalize(), 0, 0, 1, 1)
    print(bp.vector_normal.length())
    print(bp.sub_vector_1.length())
    print(bp.sub_vector_2.length())
