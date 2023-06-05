"""
Низкоуровневые объекты

Coordinates, Point, Vector, Vector space
"""

import math

Round_Num = 5


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

    def distance(self, other) -> float:
        """
        Расстояние между self и other
        :param other: Точка или координаты
        :return: Расстояние между точками
        """
        if isinstance(other, Point):
            return math.sqrt(sum([(self.coords[i] - other.coords[i]) ** 2 for i in range(0, 2 + 1)]))
        elif isinstance(other, Coordinates) or isinstance(other, list):
            return math.sqrt(sum([(self.coords[i] - other[i]) ** 2 for i in range(0, 2 + 1)]))

    def __str__(self):
        return f"Point({self[0]}, {self[1]}, {self[2]})"


class Vector(Coordinates):
    """
    Vector class
    """

    def __init__(self, pos_point: Point, *obj):
        # : [Coordinates, Point, *int, *float] TypeError: Value after * must be an iterable, not type
        # issue №22
        """
        Инициализация вектора
        :param pos_point:
        :param obj: Координаты, точка или список float
        """
        self.pos_point = pos_point
        if len(obj) == 1:
            if isinstance(obj[0], Point):
                super().__init__(obj[0][0], obj[0][1], obj[0][2])
            elif isinstance(obj[0], Coordinates):
                super().__init__(*obj[0])
            else:
                raise TypeError("Wrong type !")
        elif len(obj) == 3:
            if isinstance(obj[0], (int, float)) and isinstance(obj[1], (int, float)) and isinstance(obj[2],
                                                                                                    (int, float)):
                super().__init__(round(obj[0], Round_Num), round(obj[1], Round_Num), round(obj[2], Round_Num))
            else:
                raise TypeError("Wrong type !")
        elif len(obj) == 0:
            self.pos_point = Point(0, 0, 0)
            super().__init__(pos_point[0], pos_point[1], pos_point[2])
        else:
            raise TypeError("Wrong length !")

    def rotation_eiler(self, alpha: float, beta: float, gamma: float, stat_radians=False):
        """

        :param alpha: поворот по OX
        :param beta: поворот по OY
        :param gamma: поворот по OZ
        :param stat_radians: используются ли радианы
        :return: Вектор, получаемый в результате поворота
        """
        x = self[0]
        y = self[1]
        z = self[2]
        if not stat_radians:
            alpha = math.radians(alpha)
            beta = math.radians(beta)
            gamma = math.radians(gamma)
        a = math.cos(alpha)
        b = math.sin(alpha)
        c = math.cos(beta)
        d = math.sin(beta)
        e = math.cos(gamma)
        f = math.sin(gamma)
        return Vector(self.pos_point, e * c * x + e * b * d * y + e * a * d * z - a * f * y + b * f * z,
                      c * f * x + b * d * f * y + a * d * f * z + e * a * y - e * b * z,
                      -d * x + b * c * y + a * c * z)

    def rotation_vector(self, alpha: float, other, stat_radians=False):
        """
        Поворот относительно другого вектора, лежащего в плоскости, в которой необходимо повернуть вектор.
        :param alpha:
        :param other:
        :param stat_radians:
        :return:
        """
        if not stat_radians:
            alpha = math.radians(alpha)
        a = math.cos(alpha)
        b = math.sin(alpha)

        # v' = cos(alpha) * v + sin(alpha) * w x v + (1 - cos(alpha)) * (w * v) * w
        return a * self + b * (other ** self) + (1 - a) * (other * self) * other

    def angle_vector(self, other) -> float:
        """
        Вычисление абсолютного угла между векторами.
        :param other:
        :return:
        """
        print(self * other)
        print(math.acos(0))  # 1.5
        return math.acos(self * other)

    def __add__(self, other):
        if isinstance(other, Vector):
            return Vector(self.pos_point, *(self.coords[i] + other.coords[i] for i in range(0, 2 + 1)))
        else:
            TypeError("Wrong type !")

    def sum_vector(self, other):
        """
        __add__
        :param other:
        :return:
        """
        return self.__add__(other)

    def __mul__(self, other):
        """
        Скалярное произведение
        :param other:
        :return: Float
        """
        if isinstance(other, Vector):
            return sum([self[i] * other[i] for i in range(0, 2 + 1)])
        elif isinstance(other, float):
            return Vector(self.pos_point, *(self[i] * other for i in range(0, 2 + 1)))

    def __pow__(self, vc):
        """
        Векторное произведение
        :param vc:
        :return: Вектор, являющийся результатом векторного произведения двух векторов
        """
        return Vector(self.pos_point, self[1] * vc[2] - self[2] * vc[1], - (self[0] * vc[2] - self[2] * vc[0]),
                      self[0] * vc[1] - self[1] * vc[0])  # Не сократить из-за особой формулы

    def __sub__(self, other):
        """
        Разница векторов
        :param other:
        :return: Vector
        """
        x = self.coords[0] - other.coords[0]
        y = self.coords[1] - other.coords[1]
        z = self.coords[2] - other.coords[2]
        return Vector(self.pos_point, Coordinates(x, y, z))

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
        Нормализация вектора
        :return: Нормализованный вектор
        """
        len_vector = self.length()
        if round(len_vector, Round_Num) == 1:
            return self
        return Vector(self.pos_point, *(self[i] / len_vector for i in range(0, 2 + 1)))

    def length(self) -> float:
        """
        Высчитывает длину вектора
        :return: длина вектора
        """
        return VectorSpace.initialPt.distance(self.coords)

    def __str__(self) -> str:
        return f"Vector({self[0]}, {self[1]}, {self[2]})"


class VectorSpace:
    """
    Main space
    """
    # issue 13
    # issue 31
    initialPt = Point(0, 0, 0)
    basis: list[Vector] = [Vector(initialPt, 1, 0, 0), Vector(initialPt, 0, 1, 0), Vector(initialPt, 0, 0, 1)]

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
