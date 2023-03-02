import math
import configparser


class Point:
    """
    Point class
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
        :parameter pt:
        """
        self.x -= pt.x
        self.y -= pt.y
        self.z -= pt.z


class Vector:
    """
    Vector class
    """

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

    def sum(self, vc):
        """
        Sum of the self-vector and vc-vector
        :param vc: second vector
        """
        self.point += vc.point
        self.x += vc.x
        self.y += vc.y
        self.z += vc.z

    def scalarMul(self, vc):
        """

        :param vc:
        """
        self.x *= vc.x
        self.y *= vc.y
        self.z *= vc.z

    def vectorMul(self, vc):
        """

        :param vc:
        :return: returns vector, as the result of vector multiplying
        """
        return Vector(self.point, self.y * vc.z - self.z * vc.y, -(self.x * vc.z - self.z * vc.x), self.x * vc.y - self.y - vc.x)

    def length(self):
        """
        length of the vector
        :return: length of the vector
        """
        return VectorSpace.initialPt.distance(self.point)


class VectorSpace:
    """
    Main space
    At the __init__, it will be able to normalize its vectors
    """

    def __init__(self, initialPt, dir1, dir2, dir3):
        """

        :param initialPt:
        :param dir1:
        :param dir2:
        :param dir3:
        """
        self.initialPt = initialPt
        self.dir1 = dir1
        self.dir2 = dir2
        self.dir3 = dir3


class Camera:
    """
    docstring
    """

    def __int__(self, position, look_dir, fov, draw_distance):
        """

        :param fov: Горизонтальный "радиус" просмотра
        :param vfov: Вертикальный "радиус" просмотра
        :param look_at: Направление взгляда
        :param look_dir: Направление взгляда
        :param draw_distance: Дистанция рисовки
        :return:
        """
        config = configparser.ConfigParser()
        config.read(config.cfg)
        self.vfov = fov * (config['SCREEN_PARAM']['height'] / config['SCREEN_PARAM']['width'])

    def sent_rays(self, count):
        """
        ray-cast
        :param count:
        """
        pass


class Object:
    """
    Any object
    """

    def __init__(self, pos, rotation):
        """
        object.contains (pt) - bool
        :param pos: position of the camera
        :param rotation:
        """
