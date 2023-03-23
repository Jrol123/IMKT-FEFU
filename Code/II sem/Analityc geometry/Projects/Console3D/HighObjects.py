"""
Высокоуровневые объекты
Camera, Parameters, Object
"""

import LowObjects
import configparser


class Camera:
    """
    Камера.
    Способна просматривать объекты с помощью "sent_rays" функции.
    """

    def __init__(self, position_point: LowObjects.Point, look_at_dir: [LowObjects.Point, LowObjects.Vector],
                 fov: [int, float], draw_distance: [int, float]):
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
        if isinstance(look_at_dir, LowObjects.Point):
            pass
        elif isinstance(look_at_dir, LowObjects.Vector):
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
        self.coefficients = 1
        pass

    def __contains__(self, item) -> LowObjects.Point:
        """

        :param item:
        :return:
        """
        pass

    def intersect(self):
        """

        :return:
        """


class ParametersPlane(Parameters):
    """
    Empty
    """
    pass


class ParametersCube(Parameters):
    """
    Empty
    """
    pass


class ParametersBoundedPlane(Parameters):
    """
    Empty
    """
    def __init__(self, pos_point: LowObjects.Point, vector_norm: LowObjects.Vector, width: float, length: float):
        """

        :param pos_point:
        :param vector_norm:
        :param width:
        :param length:
        """
        self.pos_point = pos_point
        self.vector_norm = vector_norm
        self.width = width
        self.length = length

    def function:


class ParametersSphere(Parameters):
    """
    Empty
    """
    pass


class Object:
    """
    Any object
    """

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters: Parameters):
        """
        object.contains (other) - bool (???)
        :param pos_point: Позиция центра объекта. Задаётся с помощью Point
        :param rotation:
        :param parameters:
        """
        self.parameters = parameters
        self.pos = pos_point
        self.rotation = rotation

    def __contains__(self, point: LowObjects.Point) -> bool:
        """
        Empty
        :param point:
        :return:
        """
        # По-умолчанию должен выдавать False
        if self.__class__.function(self, point) == 0:
            return True
        return False

    def intersect(self):
        """
        Empty
        """
        # По-умолчанию должен выдавать точку в конце Draw Distance
        # В противном случае выдаёт точку объекта
        pass


class Sphere(Object, ParametersSphere):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters, radius, get_equation):
        super().__init__(pos_point, rotation, parameters)
        self.radius = radius
        # self.parameters = parameters(get_equation)


class Cube(Object, ParametersCube):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters):
        """
        Empty
        """
        super().__init__(pos_point, rotation, parameters)


class Plane(Object):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector):
        """
        Empty
        :param pos_point:
        :param vector_normal:
        """
        self.pos_point = pos_point
        self.vector_normal = vector_normal

    def function(self, point: LowObjects.Point) -> float:
        """
        Функция Plane
        :param point:
        :return:
        """
        return sum(self.vector_normal[i] * (self.pos_point[i] - point[i]) for i in range(3))


class BoundedPlane(Plane, ParametersBoundedPlane):
    """
    Empty
    """

    def __init__(self, pos_point):
        pass

    def function(self, point: LowObjects.Point) -> float:
        """
        Функция Bounded Plane
        :param point:
        :return:
        """
        return sum(self.vector_normal[i] * (self.pos_point[i] - point[i]) for i in range(3))
