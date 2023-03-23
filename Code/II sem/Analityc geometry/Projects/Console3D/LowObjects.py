"""
Низкоуровневые объекты
Coordinates, Point, Vector, Vector space
"""

import math


class Coordinates:
    """
    Координаты для разных объектов, оперируемых x, y и z координатами.
    Не используется для VectorSpace.
    """

    def __init__(self, x, y, z):
        """
        Инициализация координат.
        :param x: Координаты по x
        :param y: Координаты по y
        :param z: Координаты по z
        """
        self.coords = [float(x), float(y), float(z)]

    def x(self):
        return self.coords[0]

    def y(self):
        return self.coords[1]

    def z(self):
        return self.coords[2]

    # Это, скорее, шуточные команды, относящиеся к нижнему комментарию
    # issue 16

    def __getitem__(self, item: int):
        return self.coords[item]
        # Было бы круто, если бы можно было возвращать через [0], а не через массив

    def __truediv__(self, other):
        """
        Деление векторов
        :param other:
        :return: Vector
        """
        assert other != 0
        return self * (1 / other)

    def __add__(self, other):
        return self.__class__(*[self[i] + other[i] for i in range(3)])

    def __sub__(self, other):
        return self + (-1 * other)

    def __mul__(self, other: (int, float)):
        if isinstance(other, (int, float)):
            return self.__class__(*[self[i] * other for i in range(3)])
        elif isinstance(other, Coordinates):
            return self.__class__(*[self[i] * other[i] for i in range(3)])
        else:
            TypeError("Wrong Type!")

    def __rmul__(self, other):
        return self * other


class Point(Coordinates):
    """
    Point class
    """

    def __init__(self, *obj):
        if isinstance(obj[0], Coordinates):
            super().__init__(*obj[0])
        # elif isinstance(obj, (List[int], List[float])):
        elif isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2], (int, float)):
            super().__init__(obj[0], obj[1], obj[2])

    def distance(self, other):
        """
        Distance between the self, and the other
        :param other: some other point
        :return: distance between points
        """
        if isinstance(other, Point):
            return math.sqrt(sum([(self.coords[i] - other.coords[i]) ** 2 for i in range(0, 2 + 1)]))
        elif isinstance(other, Coordinates):
            return math.sqrt(sum([(self.coords[i] - other[i]) ** 2 for i in range(0, 2 + 1)]))

    # def __add__(self, other):
    #     """
    #     Сумма двух точек.
    #     Суммируется по координатам.
    #     :param other: Другая точка.
    #     :return: Точка с координатами, равными сумме двух предыдущих координат.
    #     """
    #     return Point(super().__add__(other))
    #
    # def __sub__(self, other):
    #     """
    #     subtraction of two points
    #     :parameter other:
    #     :return:
    #     """
    #     return Point(super().__sub__(other.coords))
    #
    # def __mul__(self, num):
    #     """
    #     multiplication point by num
    #     :param num:
    #     :return:
    #     """
    #     return Point(super().__mul__(self.coords * num))
    #
    # def __truediv__(self, obj):
    #     """
    #     div point by num
    #     :param num:
    #     :return:
    #     """
    #     assert obj != 0
    #     return self * (1 / obj)

    def __str__(self):
        return f"Point({self[0]}, {self[1]}, {self[2]})"


class Vector(Coordinates):
    """
    Vector class
    """

    def __init__(self, *obj):
        # : [Coordinates, Point, *int, *float] TypeError: Value after * must be an iterable, not type
        # issue №22
        """
        Initialization of vector
        :param obj: Either a Coordinates, Point or a list of float
        """
        if len(obj) == 1:
            if isinstance(obj[0], Point):
                super().__init__(obj[0][0], obj[0][1], obj[0][2])
            elif isinstance(obj[0], Coordinates):
                super().__init__(*obj[0])
            else:
                raise TypeError("Wrong type")
        elif len(obj) == 3:
            if isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2],
                                                                                                    (int, float)):
                super().__init__(obj[0], obj[1], obj[2])
            else:
                raise TypeError("Wrong type !")
        else:
            raise TypeError("Wrong type !")

    # def __add__(self, other):
    #     """
    #     Sum of the self-vector and other vector
    #     :param other: second vector
    #     """
    #     return Vector(super().__add__(other.coords))

    def __mul__(self, vc):
        """
        Скалярное произведение
        :param vc:
        :return: Float
        """
        return sum([self[i] * vc[i] for i in range(0, 2 + 1)])

    def __pow__(self, vc):
        """
        Векторное произведение
        :param vc:
        :return: Returns vector, as the result of vector multiplying
        """
        return Vector(self[1] * vc[2] - self[2] * vc[1], - (self[0] * vc[2] - self[2] * vc[0]),
                      self[0] * vc[1] - self[1] - vc[0])  # Не сократить из-за особой формулы

    # def __sub__(self, other):
    #     """
    #     Разница векторов
    #     :param other:
    #     :return: Vector
    #     """
    #     return Vector(super().__add__(other.coords * -1))

    # def __truediv__(self, other):
    #     """
    #     Деление векторов
    #     :param other:
    #     :return: Vector
    #     """
    #     assert other != 0
    #     return self * (1 / other)

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
        return VectorSpace.initialPt.distance(self.coords)

    def __str__(self):
        return f"Vector({self[0]}, {self[1]}, {self[2]})"


class VectorSpace:
    """
    Main space
    """
    # issue 13
    initialPt = Point(0, 0, 0)
    basis = [Vector(Point(1, 0, 0)), Vector(Point(0, 1, 0)), Vector(Point(0, 0, 1))]

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
        VectorSpace.basis = [dir1.normalize(), dir2.normalize(), dir3.normalize()]
        # Помнится, я как-то по другому реализовывал изменение корневых параметров, но раз уж оно работает...
