"""
Зона тестирования
"""

import HighObjects as HO
import LowObjects as LO

if __name__ == "__main__":
    HO.BoundedPlane(LO.Point(0, 0, 0), LO.Vector(LO.Point(0, 0, 0), 0, 0, 1), 90, 90, 2, 2, 1, 1, 1)
