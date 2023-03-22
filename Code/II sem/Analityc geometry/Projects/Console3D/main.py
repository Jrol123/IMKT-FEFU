"""
Зона тестирования
"""

import HighObjects
import LowObjects

if __name__ == "__main__":
    print()
    pt1 = LowObjects.Point(1, 1, 1)
    pt2 = LowObjects.Point(1, 1, 1)
    pt3 = pt1 - pt2
    print(pt3)
