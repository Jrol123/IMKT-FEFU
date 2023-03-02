import math
import configparser


class Point:
    """
    Point at VectorSpace

    :module a:
    """
    def __init__(self, x, y, z):
        """
        Initialisation of the point class

        :parameter x: location of point by x
        :parameter y: location of point by y
        :parameter z: location of point by z
        """
        self.x = x
        self.y = y
        self.z = z

    def distance(self, pt):
        """
        Distance between the self, and the pt

        :param pt: some other point
        :return: returns distance between points
        """
        return math.sqrt((self.x - pt.x) ** 2 +
                         (self.y - pt.y) ** 2 +
                         (self.z - pt.z) ** 2)

    def sum(self, pt):
        """
        sum of two points

        :param pt: some point
        """
        self.x += pt.x
        self.y += pt.y
        self.z += pt.z

    def sub(self, pt):
        """
        subtraction of two points

        :param pt:
        """
        self.x -= pt.x
        self.y -= pt.y
        self.z -= pt.z


class Vector:
    def __init__(self, point, x, y, z):
        """
        :param point:
        :param x:
        :param y:
        :param z:
        """
        self.point = point(x, y, z)
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
        config = configparser.ConfigParser()
        config.read(config.cfg)
        self.vfov = fov * (config['SCREEN_PARAM']['height'] / config['SCREEN_PARAM']['width'])
        """
        :param fov: горизонтальный "радиус" просмотра
        :param vfov: вертикальный "радиус" просмотра
        :param look_at: направление взгляда
        :param look_dir:
        """

    def sent_rays(self, count):
        pass


class Object:
    def __init__(self, pos, rotation):
        """
        object.contains (pt) - bool
        :param pos: position of the camera
        :param rotation:
        """


a = Camera()
