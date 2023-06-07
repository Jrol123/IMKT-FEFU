"""
Зона тестирования
"""

import LowObjects as LO
import HighObjects as HO

if __name__ == "__main__":
    mp = HO.Map()
    sp = HO.Sphere(LO.Point(0, 5, 0), LO.Vector(LO.Point(0, 3, 0)), 2)
    mp.push(sp)
    c = HO.Camera(LO.Point(0, 0, 0), LO.Vector(LO.Point(0, 1, 0)), 90, 45)
    console = HO.Console(mp, c)
    console.draw()
    """
    Нормально пускает лучи. Не отрисовывает
    """
