"""
Различные объекты, нужные лишь для взаимодействия с графикой, объектами и т. д.

Camera, Canvas, Ray,  Console, Event
"""
import configparser
import numpy as np
import math
import LowObjects as LO
import HighObjects as HO


class Map:
    """
    Список объектов
    """
    objects_list: list = []

    def push(self, obj):
        """
        Метод создания объектов.

        Объекты будут сразу же создаваться тут и добавляться в список.

        Или можно сразу же их здесь и создавать, кстати.
        :param obj:
        """
        self.objects_list.extend(obj)

    def __getitem__(self, item: int):
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
    Empty
    """

    def __init__(self, init_point: LO.Point, dir_vector: LO.Vector):
        """
        Инициализация луча
        :param init_point:
        :param dir_vector:
        """
        self.init_point = init_point
        self.dir_vector = dir_vector

    def intersect(self, mapping: Map) -> list[float]:
        """
        Метод определения пересечения с объектами.
        :param mapping: "Пространство", внутри которого мы будем искать пересечения.
        :return: Расстояния между начальной точкой и объектами, через которые пройдёт луч.
        """
        return [iter_object.intersect(self) for iter_object in mapping]


class Camera:
    """
    Камера.
    Способна просматривать объекты с помощью "sent_rays" функции.
    """

    def __init__(self, position_point: LO.Point, look_at_dir: [LO.Point, LO.Vector],
                 fov: [int, float], draw_distance: [int, float]):
        """
        Инициализация камеры.
        :param position_point: Point
        :param fov: Горизонтальный "радиус" просмотра. Задаётся в радианах
        :param vfov: Вертикальный "радиус" просмотра
        :param look_at_dir: Направление взгляда. Задаётся либо с помощью точки, либо с помощью вектора.
        При точке мы ВСЕГДА смотрим на точку. При векторе мы ВСЕГДА смотрим только в направлении вектора
        :param draw_distance: Дистанция рисовки
        :param block_size: Размер блоков. Исчисляется в пикселях
        :return: Camera
        """
        self.position_point = position_point
        self.draw_distance = draw_distance

        # Разобраться с тем, когда у нас look_at, а когда look_dir

        if isinstance(look_at_dir, LO.Point) or isinstance(look_at_dir, LO.Vector):
            self.look_at_dir = look_at_dir # Пока-что это вектор
        else:
            TypeError("Wrong Type!")

        config = configparser.ConfigParser()
        config.read("config.cfg")
        self.height = int(config['SCREEN_PARAM']['height'])
        self.width = int(config['SCREEN_PARAM']['width'])

        self.fov = fov * math.pi / 180
        self.vfov = fov * (self.height / self.width)

        self.screen = HO.BoundedPlane(position_point + look_at_dir.coords, look_at_dir, 0, 0,
                                      math.tan(self.vfov), math.tan(self.fov),) # Реализуем, если у нас look_at_dir = Vector

    def is_static(self):
        """
        Проверка, является ли камера "статичной", т. е. смотрит ли камера на фиксированную точку
        :return:
        """
        return isinstance(self.look_at_dir, LO.Point)

    def sent_rays(self) -> list[list[Ray]]:
        """
        Лучи пускаются на экран.


        Для избавления от эффекта рыбьего глаза необходимо проецировать лучи на касательную к сфере.

        vk' = vk / cos(gamma) # нормализованный относительно v1 вектор

        cos(gamma) = cos(v1.angle.vector(vk))

        cos(gamma) = (v1 * vk) / (v1.len() * vk.len())

        vk' = (vk * v1.len() * vk.len()) / (v1 * vk)

        dk' = dk / vk' # дистанция в матрице расстояний
        """



class Canvas:
    """
    Полотно отрисовки.
    :param map: Карта
    :param camera:
    """

    def __init__(self, map: Map, camera: Camera):
        self.map = map
        self.camera = camera

    def update(self):
        """
        Возвращает матрицу расстояний из Camera.send_rays
        """
        rays = self.camera.sent_rays()
        distances_matrix = []
        for i in range(int(self.camera.screen.width)):
            distances_matrix.append([])
            for j in range(int(self.camera.screen.height)):
                distances = rays[i][j].intersect(self.map)
                if all(distance is None or distance > self.camera.draw_distance for distance in distances):
                    distances_matrix[i].append(None)
                else:
                    distances_matrix[i].append(min(filter(lambda x: x is not None, distances)))  # фильтр None-ов


class Console(Canvas):
    """
    Отрисовка символами матрицы

    Список символов [#, @, &, ?, j, i, ,, .]

    Конвертация матрицы расстояний в символы
    """

    def __init__(self):
        pass

    def draw(self):
        """
        Отрисовка по матрице расстояний
        :return:
        """
