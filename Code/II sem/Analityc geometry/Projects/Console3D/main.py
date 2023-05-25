"""
Зона тестирования
"""

import LowObjects as LO
import UtilityObjects as UO
import HighObjects as HO

if __name__ == "__main__":
    BP = HO.BoundedPlane(LO.Point(0, 0, 0), LO.Vector(LO.Point(0, 0, 0), 0, 0, 1), 90, 90, 2, 2, 1, 0, -1)
    BP.rotate(90, 0, 0)
