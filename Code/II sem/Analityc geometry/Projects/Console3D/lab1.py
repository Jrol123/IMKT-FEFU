import math
import configparser


class Coord:
    """
    Different coordinates
    """

    def __init__(self, x, y, z):
        """
        initialization of coordinates
        :param x:
        :param y: 
        :param z:
        """
        self.x = x
        self.y = y
        self.z = z


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
        coordinates = Coord(x, y, z)

    def distance(self, pt):
        """
        Distance between the self, and the pt
        :param pt: some other point
        :return: distance between points
        """
        return math.sqrt((self.x - pt.x) ** 2 +
                         (self.y - pt.y) ** 2 +
                         (self.z - pt.z) ** 2)

    def __add__(self, pt):
        """
        sum of two points
        :param pt: some point
        """
        return Point(self.x + pt.x, self.y + pt.y, self.z + pt.z)

    def __mul__(self, num):
        """
        multiplication point by num
        :param num:
        :return:
        """
        return Point(self.x * num, self.y * num, self.z * num)

    def __sub__(self, pt):
        """
        subtraction of two points
        :parameter pt:
        """
        return self + pt * (-1)

    def __truediv__(self, obj):
        """
        div point by num
        :param num:
        :return:
        """
        # if isinstance(obj, Point):
        #     self.x /= obj.x
        #     self.y /= obj.y
        #     self.z /= obj.z
        # else:
        #     self.x /= obj
        #     self.y /= obj
        #     self.z /= obj
        assert obj != 0
        return self * (1 / obj)

    def __str__(self):
        return f"Point({self.x}, {self.y}, {self.z})"


class Vector:
    """
    Vector class
    """

    def __init__(self, *obj):
        """

        :param x:
        :param y:
        :param z:
        """
        if len(obj) == 1:
            if isinstance(obj[0], Point):
                self.x = obj[0].x
                self.y = obj[0].y
                self.z = obj[0].z
        elif len(obj) == 3:
            if map(isinstance, obj, [int, float]):
                self.x = obj[0]
                self.y = obj[1]
                self.z = obj[2]

    def __add__(self, vc):
        """
        Sum of the self-vector and vc-vector
        :param vc: second vector
        """
        self.point += vc.point
        self.x += vc.x
        self.y += vc.y
        self.z += vc.z

    def __sub__(self, vc):
        """

        :param vc:
        :return:
        """
        self.point -= vc.point
        self.x -= vc.x
        self.y -= vc.y
        self.z -= vc.z

    def __mul__(self, vc):
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
        return Vector(self.point, self.y * vc.z - self.z * vc.y, -(self.x * vc.z - self.z * vc.x),
                      self.x * vc.y - self.y - vc.x)

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
    initialPt = Point(0, 0, 0)
    basis = [Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 1)]

    def __init__(self, initialPt=None, dir1=None, dir2=None, dir3=None):
        """

        :param initialPt:
        :param dir1:
        :param dir2:
        :param dir3:
        """
        if initialPt is not None:
            self.initialPt = initialPt
        if all([dir1, dir2, dir3]):
            self.basis
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
        init
        :param position: Point
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


if __name__ == "__main__":
    a = Point(1, 2, 3)
    b = a * 2
    print(a, b)
