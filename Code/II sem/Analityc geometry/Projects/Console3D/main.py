"""
Зона тестирования
"""

import LowObjects as LO
import UtilityObjects as UO
import HighObjects as HO

if __name__ == "__main__":
    c = HO.Camera(LO.Point(0, 0, 0), LO.Vector(LO.Point(1, 0, 0)), 90, 45)
    print(c.width)
