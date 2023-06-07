"""
Низкоуровневые объекты

Coordinates, Point, Vector, Vector space
"""

import math


class Point:
    def __init__(self, x, y, z):
        self.coords = [x, y, z]

    def __str__(self):
        return "Point({:.4f}, {:.4f}, {:.4f})".format(*self.coords)

    def __bool__(self):
        return bool(sum(self.coords))

    def __eq__(self, other):
        return self.coords == other.coords

    def __ne__(self, other):
        return self.coords != other.coords

    def __add__(self, other):
        return Point(*[self.coords[i] + other.coords[i]
                       for i in range(3)])

    def __mul__(self, other):
        assert isinstance(other, (int, float))

        return Point(*[self.coords[i] * other
                       for i in range(3)])

    def __sub__(self, other):
        return self.__add__(-1 * other)

    def __rmul__(self, other):
        return self.__mul__(other)

    def __truediv__(self, other: [int, float]):
        assert other != 0
        return self.__mul__(1 / other)

    def distance(self, pt):
        return math.sqrt(sum((self.coords[i] - pt.coords[i]) ** 2
                             for i in range(3)))


class Vector:
    # vs = VectorSpace()
    def __init__(self, *args):
        if len(args) == 1:
            assert isinstance(args[0], Point)
            self.point = args[0]  # Point(x, y, z)
        elif len(args) == 3:
            assert all(map(isinstance, args, [(int, float)] * 3))
            self.point = Point(*args)

        # self.vs = vs

    def __str__(self):
        return "Vector({:.4f}, {:.4f}, {:.4f})".format(
            *self.point.coords)

    def len(self):
        return VectorSpace.initialPt.distance(self.point)

    def norm(self):
        if self.len() == 0:
            return self

        return Vector(self.point / self.len())

    def __bool__(self):
        return bool(self.point)

    def __eq__(self, other: "Vector"):
        return self.point == other.point

    def __ne__(self, other: "Vector"):
        return self.point != other.point

    def __add__(self, other: "Vector"):
        return Vector(self.point + other.point)

    def __sub__(self, other):
        return Vector(self.point - other.point)

    def __mul__(self, other):
        """
        Умножение на число, скалярное произведение векторов.
        """
        if isinstance(other, Vector):
            return sum(self.point.coords[i] * other.point.coords[i]
                       for i in range(3))
        else:
            return Vector(self.point * other)

    def __rmul__(self, other):
        assert isinstance(other, (int, float))

        return Vector(self.point * other)

    def __truediv__(self, other):
        assert isinstance(other, (int, float))

        return Vector(self.point / other)

    def __pow__(self, other):
        """
        Векторное произведение.
        """
        x1 = self.point.coords[0]
        y1 = self.point.coords[1]
        z1 = self.point.coords[2]
        x2 = other.point.coords[0]
        y2 = other.point.coords[1]
        z2 = other.point.coords[2]

        x = VectorSpace.basis[0] * (y1 * z2 - y2 * z1)
        y = VectorSpace.basis[1] * -(x1 * z2 - x2 * z1)
        z = VectorSpace.basis[2] * (y2 * x1 - y1 * x2)

        return x + y + z

    def rotate(self, x_angle: float = 0, y_angle: float = 0,
               z_angle: float = 0):
        x_angle = math.pi * x_angle / 360
        y_angle = math.pi * y_angle / 360
        z_angle = math.pi * z_angle / 360

        # Поворот вокруг оси Ox
        y_old = self.point.coords[1]
        z_old = self.point.coords[2]
        self.point.coords[1] = y_old * math.cos(x_angle) \
                               - z_old * math.sin(x_angle)
        self.point.coords[2] = y_old * math.sin(x_angle) \
                               + z_old * math.cos(x_angle)

        # Поворот вокруг оси Oy
        x_old = self.point.coords[0]
        z_old = self.point.coords[2]
        self.point.coords[0] = x_old * math.cos(y_angle) \
                               + z_old * math.sin(y_angle)
        self.point.coords[2] = x_old * -math.sin(y_angle) \
                               + z_old * math.cos(y_angle)

        # Поворот вокруг оси Oz
        x_old = self.point.coords[0]
        y_old = self.point.coords[1]
        self.point.coords[0] = x_old * math.cos(z_angle) \
                               - y_old * math.sin(z_angle)
        self.point.coords[1] = x_old * math.sin(z_angle) \
                               + y_old * math.cos(z_angle)


class VectorSpace:
    """
    Main space
    """
    # issue 13
    # issue 31
    initialPt = Point(0, 0, 0)
    basis: list[Vector] = [Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1)]

    def __init__(self, initial_point: Point, dir1: Vector, dir2: Vector, dir3: Vector):
        """
        Init for Vector Space
        :param initial_point: Точка отсчёта системы координат.
        :param dir1: Вектор 1.
        :param dir2: Вектор 2.
        :param dir3: Вектор 3.
        :return: Ничего. Эта функция просто меняет параметры VectorSpace
        """
        VectorSpace.initial_point = initial_point  # Меняет корневые параметры класса
        VectorSpace.basis = [dir1.norm(), dir2.norm(), dir3.norm()]
        # Помнится, я как-то по другому реализовывал изменение корневых параметров, но раз уж оно работает...

    # issue 33
    # TypeError: 'type' object is not subscriptable
    # Class 'type' does not define '__getitem__', so the '[]' operator cannot be used on its instances
    def __getitem__(self, item: int) -> Vector:
        """
        Получение векторов из базиса
        :param item:
        :return: Вектор
        """
        return self.basis[item]
