"""
The main body of Engine
"""

import math
import configparser


class Coordinates:
    """
    Координаты для разных объектов, оперируемых x, y и z координатами.
    Не работает для VectorSpace.
    """

    def __init__(self, x, y, z):
        """
        Инициализация координат.
        :param x: Координаты по x
        :param y: Координаты по y
        :param z: Координаты по z
        """
        self.coords = [0, 0, 0]
        self.coords = [float(x), float(y), float(z)]
        # self.coords[0] = float(x)
        # self.coords[1] = float(y)
        # self.coords[2] = float(z)

    def __getitem__(self, item: int):
        return self.coords[item]
        # Было бы круто, если бы можно было возвращать через [0], а не через массив

    def __add__(self, other):
        # return Coordinates(self[0] + other[0],
        #                    self[1] + other[1],
        #                    self[2] + other[2])
        return Coordinates(*[self[i] + other[i] for i in range(3)])

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
        # elif isinstance(obj, (List[int], List[float])):
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

    def __init__(self, *obj: [Coordinates, Point, *int, *float]):
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
        return Vector(self[1] * vc[2] - self[2] * vc[1], -(self[0] * vc[2] - self[2] * vc[0]),
                      self[0] * vc[1] - self[1] - vc[0])  # Не сократить из-за особой формулы

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


class Camera:
    """
    Камера.
    Способна просматривать объекты с помощью "sent_rays" функции.
    """

    def __init__(self, position_point: Point, look_at_dir: [Point, Vector], fov: [int, float],
                 draw_distance: [int, float]):
        """
        Init for Camera
        :param position_point: Point
        :param fov: Горизонтальный "радиус" просмотра
        :param vfov: Вертикальный "радиус" просмотра
        :param look_at_dir: Направление взгляда. Задаётся либо с помощью точки, либо с помощью вектора
        :param draw_distance: Дистанция рисовки
        :return: Camera
        """
        self.position_point = position_point
        self.draw_distance = draw_distance
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
        Метод пускания лучей для просмотра объектов.
        Будет связан с камерой.
        :param count: Количество испускаемых лучей (всего или по-линейно?)
        """
        # Как у нас будут пускаться лучи? "По-линейно" (вычисление кол-ва линий по vfow и для каждой линии будут
        # пускаться count лучей, расположенных по fov)?
        pass


class Parameters:
    """
    Empty
    """

    def __init__(self):
        """
        :param coefficients:
        """
        pass

    def __contains__(self, item) -> Point:
        pass


class ParametersPlane(Parameters):
    """
    Empty
    """
    pass


class Object:
    """
    Any object
    """

    def __init__(self, pos_point: Point, rotation, parameters: Parameters):
        """
        object.contains (other) - bool (???)
        :param pos_point: Позиция центра объекта. Задаётся с помощью Point
        :param rotation:
        :param parameters:
        """
        self.parameters = parameters
        self.pos = pos_point


class Sphere(Object):
    """
    Empty
    """

    def __init__(self, pos_point: Point, rotation, parameters, radius, get_equation):
        super().__init__(pos_point, rotation, parameters)
        self.radius = radius
        self.parameters = parameters(get_equation)

    def __contains__(self, point):
        """

        :param point:
        :return:
        """
        pass


class Cube(Object):
    """
    Empty
    """

    def __init__(self, pos_point: Point, rotation, parameters):
        """
        Empty
        """
        super().__init__(pos_point, rotation, parameters)

class Plane(object):
    """
    Empty
    """

    def __init__(self):
        """
        Empty
        """
        super().__init__()
