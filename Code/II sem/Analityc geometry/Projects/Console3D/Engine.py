"""
The main body of Engine
"""

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
        self.coords[0] = float(x)
        self.coords[1] = float(y)
        self.coords[2] = float(z)

    def __getitem__(self, item: int):
        return self.coords[item]
        # Было бы круто, если бы можно было возвращать через [0], а не через массив

    def __add__(self, other):
        return Coordinates(self[0] + other[0],
                           self[1] + other[1],
                           self[2] + other[2])

    def __mul__(self, other: (int, float)):
        # , Coordinates
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


class Point:
    """
    Point class
    """

    def __init__(self, *obj):
        if isinstance(obj[0], Coordinates):
            self.coordinates = obj[0]
        elif isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2], (int, float)):
            self.coordinates = Coordinates(obj[0], obj[1], obj[2])

    def distance(self, other):
        """
        Distance between the self, and the other
        :param other: some other point
        :return: distance between points
        """
        if isinstance(other, Point):
            return math.sqrt(sum([(self.coordinates[i] - other.coordinates[i]) ** 2 for i in range(0, 2 + 1)]))
        elif isinstance(other, Coordinates):
            return math.sqrt(sum([(self.coordinates[i] - other[i]) ** 2 for i in range(0, 2 + 1)]))

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

    def __init__(self, *obj: [Coordinates, Point, list]):
        """
        Initialization of vector
        :param obj: Either a Coordinates, Point or a list of float
        """
        if len(obj) == 1:
            if isinstance(obj[0], Point):
                self.coordinates = Coordinates(obj[0][0], obj[0][1], obj[0][2])
            elif isinstance(obj[0], Coordinates):
                self.coordinates = obj[0]
            else:
                raise TypeError("Wrong type")
        elif len(obj) == 3:
            if isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2],
                                                                                                    (int, float)):
                self.coordinates = Coordinates(obj[0], obj[1], obj[2])
            else:
                raise TypeError("Wrong type !")
        else:
            raise TypeError("Wrong type !")

    def __getitem__(self, item: [int]):
        return self.coordinates[item]

    def __add__(self, other):
        """
        Sum of the self-vector and other vector
        :param other: second vector
        """
        return Vector(self.coordinates + other.coordinates)

    def __mul__(self, other):
        """
        multiplication of 2 vector
        :param other:
        :return: Vector, if num is present. Otherwise, — scalar
        """
        if isinstance(other, Vector):
            return self.vectorMul  # По умолчанию возвращает векторное произведение
        elif isinstance(other, (int, float)):
            return Vector(self.coordinates * other)
        else:
            raise TypeError("Wrong type!")

    def __rmul__(self, other):
        return self * other

    def scalarMul(self, vc):
        """
        duplicate of __mul__
        :param vc:
        :return: Float
        """
        return sum([self[i] * vc[i] for i in range(0, 2 + 1)])

    def vectorMul(self, vc):
        """

        :param vc:
        :return: Returns vector, as the result of vector multiplying
        """
        return Vector(self[1] * vc[2] - self[2] * vc[1], -(self[0] * vc[2] - self[2] * vc[0]),
                      self[0] * vc[1] - self[1] - vc[0])

    def __sub__(self, other):
        """

        :param other:
        :return: Vector
        """
        return Vector(self.coordinates + (other.coordinates * -1))

    def __truediv__(self, other):
        """

        :param other:
        :return: Vector
        """
        assert other != 0
        return self * (1 / other)

    def normalize(self):
        """
        Normalization of the vector
        :return: Normalized vector
        """
        return self / self.length()

    def length(self):
        """
        length of the vector
        :return: length of the vector
        """
        return VectorSpace.initialPt.distance(self.coordinates)

    def __str__(self):
        return f"Vector({self[0]}, {self[1]}, {self[2]})"


class VectorSpace:
    """
    Main space

    """
    # issue 13
    initialPt = Point(0, 0, 0)
    basis = [Vector(Point(1, 0, 0)), Vector(Point(0, 1, 0)), Vector(Point(0, 0, 1))]

    def __init__(self, InitPoint: Point, dir1: Vector, dir2: Vector, dir3: Vector):
        """
        Init for Vector Space
        :param InitPoint: Initial point
        :param dir1: Vector1
        :param dir2: Vector2
        :param dir3: Vector3
        :return: Nothing. It just changes the existing VectorSpace
        """
        VectorSpace.initialPt = InitPoint  # Меняет корневые параметры класса
        VectorSpace.basis = [dir1.normalize(), dir2.normalize(), dir3.normalize()]
        # Помнится, я как-то по другому реализовывал изменение корневых параметров, но раз уж оно работает...


class Camera:
    """
    Empty
    """

    def __init__(self, posPoint: Point, look_at_dir: [Point, Vector], fov: [int, float], drawDist: [int, float]):
        """
        Init for Camera
        :param posPoint: Point
        :param fov: Горизонтальный "радиус" просмотра
        :param vfov: Вертикальный "радиус" просмотра
        :param look_at_dir: Направление взгляда. Задаётся либо с помощью точки, либо с помощью вектора
        :param draw_distance: Дистанция рисовки
        :return: Camera
        """
        self.posPoint = posPoint
        self.drawDist = drawDist
        if isinstance(look_at_dir, Point):
            pass
        elif isinstance(look_at_dir, Vector):
            pass
        else:
            TypeError("Wrong Type!")

        config = configparser.ConfigParser()
        config.read("config.cfg")
        height = int(config['SCREEN_PARAM']['height'])
        width = int(config['SCREEN_PARAM']['width'])

        self.vfov = fov * (height / width)

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
        :param pos: position of the object (Point)
        :param rotation:
        """
        pass
