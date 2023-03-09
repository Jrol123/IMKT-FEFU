import math
import configparser


class Coordinates:
    """
    Coordinates for different entities
    """

    def __init__(self, x, y, z):
        """
        initialization of coordinates
        :param x: coords 0
        :param y: coords 1
        :param z: coords 2
        """
        self.coords = [0, 0, 0]
        self.coords[0] = x
        self.coords[1] = y
        self.coords[2] = z

    def __getitem__(self, item):
        return self.coords[item]
        # Было бы круто, если бы можно было возвращать через .x, а не через массив

    def __add__(self, other):
        return Coordinates(self[0] + other[0],
                           self[1] + other[1],
                           self[2] + other[2])

    def __mul__(self, other):
        if isinstance(other, (int, float)):
            return Coordinates(self[0] * other,
                               self[1] * other,
                               self[2] * other)
        elif isinstance(other, Coordinates):
            return Coordinates(self[0] * other[0],
                               self[1] * other[1],
                               self[2] * other[2])
        else:
            TypeError("Wrong Type!")

    def output(self):
        """
        Output as list
        :return:
        """
        return self[0], self[1], self[2]


class Point:
    """
    Point class
    """

    def __init__(self, *obj):
        if isinstance(obj[0], Coordinates):
            self.coordinates = obj[0]
        elif isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2],(int, float)):
            self.coordinates = Coordinates(obj[0], obj[1], obj[2])

    def distance(self, other):
        """
        Distance between the self, and the other
        :param other: some other point
        :return: distance between points
        """
        return math.sqrt(sum([(self.coordinates[i] - other.coordinates[i]) ** 2 for i in range(0, 2 + 1)]))
        # return math.sqrt((self.x - other.x) ** 2 +
        #                  (self.y - other.y) ** 2 +
        #                  (self.z - other.z) ** 2)

    def __getitem__(self, item):
        return self.coordinates[item]

    def __add__(self, other):
        """
        sum of two points
        :param other: some point
        """
        return Point(self.coordinates + other.coordinates)

    # Преобразовать через map

    def __sub__(self, pt):
        """
        subtraction of two points
        :parameter pt:
        :return:
        """
        return self + pt * (-1)

    def __mul__(self, num):
        """
        multiplication point by num
        :param num:
        :return:
        """
        return Point(self.coordinates * num)

    def __rmul__(self, num):
        """

        :param num:
        :return:
        """
        return Point(self.coordinates * num)

    def __truediv__(self, obj):
        """
        div point by num
        :param num:
        :return:
        """
        assert obj != 0
        return self * (1 / obj)

    def __str__(self):
        return f"Point({self[0]}, {self[1]}, {self[2]})"


class Vector:
    """
    Vector class
    """

    def __init__(self, *obj):
        """

        :param obj:
        """
        if len(obj) == 1:
            if isinstance(obj[0], Point):
                self.coordinates = Coordinates(obj[0][0], obj[0][1], obj[0][2])
            elif isinstance(obj[0], Coordinates):
                self.coordinates = obj[0]
            else:
                raise TypeError("Wrong type")
        elif len(obj) == 3:
            if isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2], (int, float)):
                self.coordinates = Coordinates(obj[0], obj[1], obj[2])
            else:
                raise TypeError("Wrong type !")

    def __getitem__(self, item):
        return self.coordinates[item]

    def __add__(self, other):
        """
        Sum of the self-vector and other vector
        :param other: second vector
        """
        return Vector(self[0] + other[0],
                      self[1] + other[1],
                      self[2] + other[2])

    def __mul__(self, other):
        """

        :param other:
        """
        if isinstance(other, Vector):
            return Vector(self.coordinates * other.coordinates)
        elif isinstance(other, (int, float)):
            return Vector(self.coordinates * other)
        else:
            raise TypeError("Wrong type!")

    def __rmul__(self, other):
        return Vector


    def vectorMul(self, vc):
        """

        :param vc:
        :return: returns vector, as the result of vector multiplying
        """
        return Vector(self.point, self.y * vc.z - self.z * vc.y, -(self.x * vc.z - self.z * vc.x),
                      self.x * vc.y - self.y - vc.x)

    def __sub__(self, other):
        """

        :param other:
        :return:
        """
        return Vector(self[0] - other[0],
                      self[1] - other[1],
                      self[2] - other[2])
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
        Init
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
        object.contains (other) - bool
        :param pos: position of the camera
        :param rotation:
        """


if __name__ == "__main__":
    a = 2
    b = Point(1, 1, 1)
    b = a * b
    print(b)
