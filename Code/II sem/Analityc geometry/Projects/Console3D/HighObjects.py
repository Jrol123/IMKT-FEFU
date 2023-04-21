"""
Высокоуровневые объекты
Camera, Parameters, Object
"""
import math

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

    def sent_rays(self, count) -> list[LowObjects.Vector]:
        """
        Метод пускания лучей для просмотра объектов.
        Будет связан с камерой.
        :param count: Количество испускаемых лучей (всего или по-линейно?)
        """
        # Как у нас будут пускаться лучи? "По-линейно" (вычисление кол-ва линий по vfow и для каждой линии будут
        # пускаться count лучей, расположенных по fov)?
        pass


class Canvas:
    """
    Полотно отрисовки.
    :param map: Карта
    :param camera:
    """

    def draw(self) -> None:
        """
        Отрисовка (символьная, поблочная)
        :return: матрица элементов
        """

    def update(self):
        """
        Возвращает матрицу расстояний из Camera.send_rays
        """
        pass

class Console(Canvas):
    """
    Отрисовка символами матрицы
    Список символов [#, @, &, ?, j, i, ,, .]
    Конвертация матрицы расстояний в символы
    """

class Parameters:
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_norm: LowObjects.Vector):
        """

        :param pos_point:
        :param vector_norm:
        """
        self.pos_point = pos_point
        self.vector_norm = vector_norm

    # issue №29

    def scaling(self, value: float):
        """
        БАЗОВАЯ РЕАЛИЗАЦИЯ
        :param value:
        :return:
        """
        self.vector_norm *= value
        # Добавить умножение остальных параметров (вызывать scaling у подклассов?)

    def rotate(self, x_angle, y_angle, z_angle):
        """
        БАЗОВАЯ РЕАЛИЗАЦИЯ
        :param x_angle:
        :param y_angle:
        :param z_angle:
        """
        self.vector_norm = self.vector_norm.rotation_eiler(x_angle, y_angle, z_angle)

    def contains(self, item) -> LowObjects.Point:
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


class ParametersBoundedPlane(Parameters):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector,
                 alpha_1: float, alpha_2: float, width: float, length: float):
        """

        :param pos_point:
        :param vector_normal:
        :param width:
        :param length:
        """
        super().__init__(pos_point, vector_normal)
        self.vector_normal = vector_normal
        self.corner_1 = alpha_1
        self.corner_2 = alpha_2
        self.width = width
        self.length = length

        self.sub_vector_1: LowObjects.Vector
        if self.vector_normal.coords != LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 1).coords:
            self.sub_vector_1 = self.vector_normal.rotation_eiler(0, 90, 0)
            # Если не совпадает с OY — поворот по OY
        else:
            self.sub_vector_1 = vector_normal.rotation_eiler(90, 0, 0)
            # Поворот по OX
        self.sub_vector_2 = (vector_normal ** self.sub_vector_1)

    def scaling(self, value: float):
        self.width *= value
        self.length *= value

    def rotate(self, x_angle, y_angle, z_angle):
        self.vector_normal.rotation_eiler(x_angle, y_angle, z_angle)
        self.sub_vector_1.rotation_eiler(x_angle, y_angle, z_angle)
        self.sub_vector_2.rotation_eiler(x_angle, y_angle, z_angle)


class ParametersCube(Parameters):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector, alpha_1: float, alpha_2: float, width: float):
        super().__init__(pos_point, vector_normal)
        self.width = width
        self.mass_edges: list[BoundedPlane][3]
        # Реализовать инициализация массива граней через точку, смещённую по OX, Oy, OZ (выбрать)
        pass

    def move(self, move_point: LowObjects.Point):
        self.pos_point += move_point

        for edge in self.mass_edges:
        {
            edge.pos_point += move_point
        }
        pass

    def scaling(self, value):
        self.width *= value
        for edge in self.mass_edges:
        {
            edge.scaling(value)
        }
        pass

    def rotate(self, x_angle, y_angle, z_angle):
        self.vector_norm.rotation_eiler(x_angle, y_angle, z_angle)
        for edge in self.mass_edges:
        {
            edge.rotation_eiler(x_angle, y_angle, z_angle)
        }
        pass



class ParametersSphere(Parameters):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector, radius):
        super().__init__(pos_point, vector_normal)
        self.radius = radius

    def scaling(self, value: float):
        """
        САМО-ОПЕРАЦИЯ
        :param value:
        :return:
        """
        self.radius *= value


class Map:
    """
    Список объектов
    """
    objects_list: list = []

    def push(self, obj):
        """
        Метод создания объектов.

        Объекты будут сразу же создаваться тут и добавляться в список.
        :param obj:
        """
        self.objects_list.extend(obj)

    def __getitem__(self, item: int) -> Object:
        return self.objects_list[item]

    def get(self, index: int):
        """
        Явное задавание __getitem__
        :param index: номер элемента
        """
        self.__getitem__(index)

    def __iter__(self):
        return iter(self.objects_list)


class Ray:
    """

    """

    def __init__(self, init_point: LowObjects.Point, dir_vector: LowObjects.Vector):
        """
        Инициализация луча
        :param init_point:
        :param dir_vector:
        """
        self.init_point = init_point
        self.dir_vector = dir_vector

    def intersect(self, mapping: Map) -> float:
        """
        Метод определения пересечения с объектами.
        :param mapping:
        :return: Расстояние между начальной точкой и объектом.
        """
        return [iter_object.intersect(self) for iter_object in mapping]


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
        self.pos_point = pos_point
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

    def contains(self, point: LowObjects.Point) -> bool:
        """
        __contains__
        :param point:
        :return:
        """
        return self.__contains__(point)

    def intersect(self, ray: Ray) -> float or None:
        """
        Точка пересечения
        """
        # По-умолчанию должен выдавать точку в конце Draw Distance
        # В противном случае выдаёт точку объекта
        pass


class Plane(Object):
    """
    Empty
    """

    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector, parameters: Parameters):
        """
        Empty
        :param pos_point:
        :param vector_normal:
        """
        super().__init__(pos_point, vector_normal, parameters)

    # def update(self):
    #     """
    #     ????????
    #     :return:
    #     """
    #     self.pos_point = self.parameters.pos_point
    #     self.vector_normal = self.parameters.vector_norm

    def __str__(self):
        return f'Plane({self.pos_point}, {str(self.vector_normal)})'

    def function(self, point: LowObjects.Point) -> float:
        """
        Функция Plane
        :param point:
        :return:
        """
        return sum(self.vector_normal[i] * (self.pos_point[i] - point[i]) for i in range(3))

    def intersect(self, ray: Ray) -> None or float:
        """
        СМ github
        Запихнуть всё, что ниже, в функцию
        :param ray:
        :return: Точка пересечения / Точка, ближайшая к центру плоскости (зачем?)
        """
        if self.vector_normal * ray.dir_vector != 0 \
                and not (self.contains(ray.init_point)
                                            and self.contains(ray.dir_vector.pos_point)):
            t0 = (self.vector_normal * LowObjects.Vector(self.pos_point) -
                  self.vector_normal * LowObjects.Vector(ray.init_point)) / (self.vector_normal * ray.dir_vector)
            if t0 >= 0:
                return t0 * ray.dir_vector.length()

        elif self.contains(ray.init_point):
            # ???
            return 0

    def nearest_point(self) -> LowObjects.Point:
        """
        Возвращает ближайшую к центру точку
        :return: ближайшая к центру точка
        """
        pass

class BoundedPlane(ParametersBoundedPlane):
    """
    Empty
    """

    # issue №30
    def __init__(self, pos_point: LowObjects.Point, vector_normal: LowObjects.Vector,
                 alpha_1: float, alpha_2: float, width: float, height: float):
        """
        1) Находим первый побочный вектор (поворачиваем нормаль на 90 градусов по OY)
        2) Поворачиваем первый побочный вектор на alpha_1
        3) Находим второй побочный вектор с помощью векторного произведения нормали и первого побочного вектора
        4) Поворачиваем второй побочный вектор на alpha_2

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
        :param alpha_1: Поворот OX
        :param alpha_2: Поворот OY
        :param width:
        :param height:
        """
        super().__init__(pos_point, vector_normal, alpha_1, alpha_2, width, height)

        # реализация с поворотом

        # massAngle = [LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2).
        #              angle_vector(LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 0)),
        #              LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2).
        #              angle_vector(LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 1)),
        #              LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2).
        #              angle_vector(LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2))]
        # # Массив углов поворота. OX, OY, OZ
        # for i in range(0, 2 + 1):
        #     angle = vector_normal.angle_vector(LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, i))
        #     # if angle > 0:
        #     #     massAngle[i] = (massAngle[i] - angle)
        #     # else:
        #     #     massAngle[i] = (massAngle[i] + angle)
        #     massAngle[i] = (massAngle[i] - angle)
        # # scalLen = vector_normal * \
        # #           LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2)  # Скаляр между OZ и vector_normal
        # # fAngle = vector_normal.angle_vector \
        # #     (LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, 2))  # Угол между OZ и vector_normal
        # massVec = []  # массив повёрнутых векторов
        # for i in range(2 + 1):
        #     massVec.append(LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, i).rotation_eiler(*massAngle))
        #     # Вектор OZ должен совпадать.
        #     # Выдаёт бешеные векторы
        # massVec[0].rotation_eiler(*(vector_normal.angle_vector
        #                             (LowObjects.VectorSpace.__getitem__(LowObjects.VectorSpace, i))
        #                             for i in range(0, 2 + 1)))

    def function(self, point: LowObjects.Point) -> float:
        """
        Функция Bounded Plane
        :param point:
        :return:
        """
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
