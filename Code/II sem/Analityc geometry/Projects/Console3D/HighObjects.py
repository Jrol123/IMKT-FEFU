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
        pass

    def __contains__(self, item) -> LowObjects.Point:
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

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters: Parameters):
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

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters, radius, get_equation):
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

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters):
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
