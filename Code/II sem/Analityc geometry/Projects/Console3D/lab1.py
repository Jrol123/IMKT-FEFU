import math


class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def distance(self, pt):
        return math.sqrt((self.x - pt.x) ** 2 +
                         (self.y - pt.y) ** 2 +
                         (self.z - pt.z) ** 2)

    def sum(self, pt):
        self.x += pt.x
        self.y += pt.y
        self.z += pt.z


class Vector:
    def __init__(self, point, x, y, z):
        self.point = point(x, y, z)
        self.length = math.sqrt()
        self.x = x
        self.y = y
        self.z = z

    def sum(self, pt):
        self.point += pt.point
        self.x += pt.x
        self.y += pt.y
        self.z += pt.z
    def length(self):
        return VectorSpace.initialPt.distance(self.point)


class VectorSpace:
    def __init__(self, initialPt, dir1, dir2, dir3):
        self.initialPt = initialPt
        self.dir1 = dir1
        self.dir2 = dir2
        self.dir3 = dir3


class Camera:
    def __int__(self, position, look_dir, fov, draw_distance):
        """
        self.vfov = fov * (h / w) - вертикальный угол наклона


        :param look_at: направление взгляда
        :param look_dir:
        """

    def sent_rays(self, count):
        pass


class Object:
    def __init__(self, pos, rotation):
        """
        object.contains (pt) - bool
        :param pos:
        :param rotation:
        """
