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

    # issue №29

    def contains(self, item):
        """
        public method
        Используется для перегрузки
        :param item:
        """
        pass

    def __contains__(self, item) -> LowObjects.Point:
        """
        private method
        используется только для себя
        :param item:
        :return:
        """
        return self.contains(item)


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

    def __init__(self, pos_point: LowObjects.Point, vector_norm: LowObjects.Vector,
                 alpha_1: float, alpha_2: float, width: float, length: float):
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


class ParametersSphere(Parameters):
    """
    Empty
    """
    pass


class Object:
    """
    Any object
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector, parameters: Parameters):
        """
        object.contains (other) - bool (???)
        :param pos_point: Позиция центра объекта. Задаётся с помощью Point
        :param vector_normal:
        :param parameters:
        """
        self.parameters = parameters
        self.pos = pos_point
        self.vector_normal = vector_normal

    def __contains__(self, point: LowObjects.Point) -> bool:
        """
        Empty
        :param point:
        :return:
        """
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


class Sphere(Object):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, rotation, parameters, radius, get_equation):
        super().__init__(pos_point, rotation, parameters)
        self.radius = radius
        # self.parameters = parameters(get_equation)


class Cube(Object):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal, parameters):
        """
        Empty
        """
        super().__init__(pos_point, vector_normal, parameters)


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


class BoundedPlane(Plane):
    """
    Empty
    """

    # issue №30
    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector,
                 alpha_1: float, alpha_2: float, width: float, height: float):
        """
        1) определить наименьший угол между OX / OY / OZ и нормалью
        2) повернуть "vs" так, чтобы OX / OY / OZ совпадали с нормалью
        3) повернуть оставшиеся 2 координаты по 2-м углам.
        4) домножить 2 координаты на width и height

        ИЛИ

        1) сопоставить всю систему "vs" с нормалью, где OZ = vector_normal
        2) Прокрутить OX на alpha_1, OY на alpha_2
        3) Умножить OX на width, OY на height

        ИЛИ

        1) На вход получается точка, нормаль, направляющий вектор и угол
            1.1) Направляющий вектор должен быть нормализован и лежать на плоскости
        2) Строим правую тройку векторов. Можно сразу же умножать вектора на длину и ширину
        3) Поворачиваем побочный вектор на alpha
        Стоп, а это не просто улучшенная версия моего способа??

        Список проблем:
            1) Если работать с "наименьшим углом", то как определить, какую штуку на что прокручивать + умножение?
            2) Если работать с OZ = vector_normal, то нужно понять, в какую сторону поворачивать
        Доп:
            1) учесть, что угол между "побочными" векторами может быть не прямым (ромбы) =>
            2) поворот идёт сразу по всем осям (и относительно осей) => разбить поворот на 3 части (OX, OY, OZ).
               Можно поворачивать по-очереди.

        :param pos_point:
        :param vector_normal:
        :param alpha_1:
        :param alpha_2:
        :param width:
        :param height:
        """
        super().__init__(pos_point, vector_normal)

    def function(self, point: LowObjects.Point) -> float:
        """
        Функция Bounded Plane
        :param point:
        :return:
        """
        pass
