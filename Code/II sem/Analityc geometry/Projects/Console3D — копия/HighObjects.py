"""
Высокоуровневые объекты
Plane, Sphere
"""
import configparser
import math
import sys

import numpy as np
import LowObjects as LO


class Map:
    """
    Список объектов
    """
    objects_list = []

    def push(self, *obj):
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

    def __str__(self):
        return f"Ray. \n {self.init_point}, \n {self.dir_vector} \n"


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
            self.look_at_dir = look_at_dir  # Пока-что это вектор
        else:
            TypeError("Wrong Type!")

        config = configparser.ConfigParser()
        config.read("config.cfg")
        self.height = int(config['SCREEN_PARAM']['height'])
        self.width = int(config['SCREEN_PARAM']['width'])

        self.fov = fov / 2 * math.pi / 180
        self.vfov = self.fov * (self.height / self.width)

        self.screen = BoundedPlane(self.position_point + self.look_at_dir.pos_point / math.tan(self.fov),
                                   self.look_at_dir, math.tan(self.fov),
                                   math.tan(self.vfov))  # Реализуем, если у нас look_at_dir = Vector
        # BP перпендикулярен камере

    def is_static(self):
        """
        Проверка, является ли камера "статичной", т. е. смотрит ли камера на фиксированную точку
        :return:
        """
        return isinstance(self.look_at_dir, LO.Point)

    def send_rays(self) -> list[list[Ray]]:
        """
        Лучи пускаются на экран.


        Для избавления от эффекта рыбьего глаза необходимо проецировать лучи на касательную к сфере.

        vk' = vk / cos(gamma) # нормализованный относительно v1 вектор

        cos(gamma) = cos(v1.angle.vector(vk))

        cos(gamma) = (v1 * vk) / (v1.len() * vk.len())

        vk' = (vk * v1.len() * vk.len()) / (v1 * vk)

        dk' = dk / vk' # дистанция в матрице расстояний
        """

        rays = []
        for index, param_vert in enumerate(np.linspace(-self.screen.height, self.screen.height, self.height)):
            # Пускание лучей по ширине экрана
            rays.append([])
            for param_hor in np.linspace(-self.screen.width, self.screen.width, self.width):
                dir_vector = LO.Vector(self.screen.pos_point) + \
                             self.screen.v * param_vert + self.screen.u * param_hor
                dir_vector = dir_vector - LO.Vector(self.position_point)
                dir_vector.pos_point = LO.Point(dir_vector.pos_point.x(), dir_vector.pos_point.y() / (15 / 48),
                                                dir_vector.pos_point.z())
                rays[index].append(Ray(self.position_point, dir_vector.normalize()))

        return rays


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

        :return: матрица расстояний
        """
        rays = self.camera.send_rays()
        dist_matrix = []
        for i in range(self.camera.height):
            dist_matrix.append([])
            for j in range(self.camera.width):
                # rays[i][j].dir /= ((rays[i][j].dir
                #                    * rays[self.cam.hight // 2][0].dir)
                #                    / rays[i][j].dir.len() ** 2)

                distances = rays[i][j].intersect(self.map)
                if all(d is None or d > self.camera.draw_distance
                       for d in distances):
                    dist_matrix[i].append(None)
                # elif min(filter(None, distances)
                # ) > self.cam.draw_dist:
                #     dist_matrix[i].append(None)
                else:
                    dist_matrix[i].append(
                        min(filter(lambda x: x is not None, distances)))
                    # if dist_matrix[i] is not None:
                    #     dist_matrix[i][j] *= rays[i][j].dir.len()

        return dist_matrix


class Console(Canvas):
    """
    Отрисовка символами матрицы

    Список символов [#, @, &, ?, j, i, ,, .]

    Конвертация матрицы расстояний в символы
    """
    symbols = " .:!/r(l1Z4H9W8$@"

    def draw(self):
        """

        """
        dist_matrix = self.update()
        output_screen = ''
        # min_d, max_d = min(elem for d in dist_matrix for elem in d),\
        #     max(elem for d in dist_matrix for elem in d)
        for y in range(len(dist_matrix)):
            # print(dist_matrix[y], end='')
            for x in range(len(dist_matrix[y])):
                if dist_matrix[y][x] is None:
                    output_screen += self.symbols[0]
                    # print(symbols[0], end='')
                    continue

                try:
                    gradient = dist_matrix[y][x] / self.camera.draw_distance \
                               * (len(self.symbols) - 1)

                    output_screen += self.symbols[len(self.symbols)
                                                  - round(gradient) - 1]
                    # print(symbols[len(symbols) - round(gradient) - 1],
                    #       end='')
                except (IndexError, TypeError):
                    print(len(self.symbols) * dist_matrix[y][x] / self.camera.draw_distance, dist_matrix[y][x])
                    raise

            output_screen += '\n'
            # print()

        print(output_screen)


class Parameters:
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector):
        """

        :param pos_point:
        :param vector_normal:
        """
        self.pos_point = pos_point
        self.vector_norm = vector_normal

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

    def contains(self, item) -> LO.Point:
        """
        public method
        Используется для перегрузки
        :param item:
        """
        pass

    def __contains__(self, item) -> LO.Point:
        """
        private method
        используется только для себя
        :param item:
        :return:
        """
        return self.contains(item)


class ParametersBoundedPlane(Parameters):
    def __init__(self, pos: LO.Point, vector_normal: LO.Vector,
                 u, v, du, dv):
        super().__init__(pos, vector_normal)
        self.u = u
        self.v = v
        self.width = du
        self.height = dv

    def scaling(self, value):
        self.width = self.width * value
        self.height = self.height * value

    def rotate(self, x_angle=0, y_angle=0, z_angle=0):
        self.vector_norm.rotation_eiler(x_angle, y_angle, z_angle)
        self.u.rotation_eiler(x_angle, y_angle, z_angle)
        self.v.rotation_eiler(x_angle, y_angle, z_angle)


class ParametersSphere(Parameters):
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector, radius: float):
        super().__init__(pos_point, vector_normal)
        self.radius = radius

    def function(self, point: LO.Point):
        """
        Функция сферы
        :param point:
        :return:
        """
        return (point.x() - self.pos_point.x()) ** 2 + (point.y() - self.pos_point.y()) ** 2 + (
                point.z() - self.pos_point.z()) ** 2 \
            == self.radius ** 2

    def scaling(self, value: float):
        """
        САМО-ОПЕРАЦИЯ
        :param value:
        :return:
        """
        self.radius *= value


class Object:
    """
    Any object
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector):
        """
        object.contains (other) - bool (???)
        :param pos_point: Позиция центра объекта. Задаётся с помощью Point
        :param vector_normal:
        # :param parameters:
        """
        # self.parameters = parameters
        self.pos_point = pos_point
        self.vector_normal = vector_normal

    def __contains__(self, point: LO.Point) -> bool:
        """
        Empty
        :param point:
        :return:
        """
        if self.__class__.function(self, point) == 0:
            return True
        return False

    def contains(self, point: LO.Point) -> bool:
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

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector):
        """
        Empty
        :param pos_point:
        :param vector_normal:
        """
        super().__init__(pos_point, vector_normal)

    def __str__(self):
        return f'Plane({self.pos_point}, {str(self.vector_normal)})'

    def function(self, point: LO.Point) -> float:
        """
        Функция Plane
        :param point:
        :return:
        """
        return sum(self.vector_normal[i] * (self.pos_point[i] - point[i]) for i in range(3))

    def intersect(self, ray: Ray) -> None or float:
        """
        ю
        :param ray:
        :return: Расстояние от начала камеры до точки пересечения
        """

        t0 = (self.vector_normal * LO.Vector(self.pos_point) -
              self.vector_normal * LO.Vector(ray.init_point)) / (self.vector_normal * ray.dir_vector)
        if t0 < 0:
            return None
        return t0 * ray.dir_vector.length()


class BoundedPlane(ParametersBoundedPlane):
    """
    Empty
    """

    # issue №30
    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector, width, height):
        """

        :param pos_point:
        :param vector_normal:
        :param width:
        :param height:
        """
        y_dir = LO.VectorSpace.basis[1]
        if vector_normal.pos_point == y_dir.pos_point \
                or vector_normal.pos_point == -1 * y_dir.pos_point:
            _dir = LO.VectorSpace.basis[0]

        u = (vector_normal ** y_dir).normalize()
        v = (vector_normal ** u).normalize()

        super().__init__(pos_point, vector_normal, u, v, width, height)

    def __str__(self):
        return f'Plane({self.pos_point}, {self.vector_norm},' \
               f' du={self.width}, dv={self.height})'

    def in_boundaries(self, pt: LO.Point) -> bool:
        """
        Проверка координат точки на соответствие границам плоскости.

        :param pt: Точка
        :return:
        """
        corner = self.u * self.width + self.v * self.height
        delta_x, delta_y, delta_z = corner.point.coords
        # print('This is here', corner.point)
        return abs(pt.coords[0] - self.pos_point.coords[0]) <= abs(delta_x) \
            and abs(pt.coords[1] - self.pos_point.coords[1]) <= abs(delta_y) \
            and abs(pt.coords[2] - self.pos_point.coords[2]) <= abs(delta_z)

    def contains(self, pt: LO.Point, eps=1e-6) -> bool:
        if self.in_boundaries(pt):
            return abs(self.vector_norm * LO.Vector(pt - self.pos_point)) < eps

        return False

    def intersect(self, ray: Ray) -> float or None:
        """

        :param ray:
        :return:
        """
        if self.vector_norm * ray.dir_vector != 0:
            if self.contains(ray.init_point):
                return 0

            t0 = (self.vector_norm * LO.Vector(self.pos_point) -
                  self.vector_norm * LO.Vector(ray.init_point)) / (self.vector_norm * ray.dir_vector)
            int_pt = ray.dir_vector.pos_point * t0 + ray.init_point
            if t0 >= 0 and self.in_boundaries(int_pt):
                return int_pt.distance(ray.init_point)

        elif self.vector_norm * LO.Vector(ray.dir_vector.pos_point
                                          + ray.init_point - self.pos_point) == 0:
            # Проекции вектора из точки центра плоскости
            # к точке начала вектора v на направляющие вектора плоскости
            r_begin = LO.Vector(ray.init_point - self.pos_point)
            # Если начало вектора совпадает с центром плоскости
            if r_begin.length() == 0:
                return 0

            begin_pr1 = r_begin * self.u * self.width / r_begin.length()
            begin_pr2 = r_begin * self.v * self.height / r_begin.length()
            if abs(begin_pr1) <= 1 and abs(begin_pr2) <= 1:
                return 0

            # Проекции вектора из точки центра плоскости
            # к точке конца вектора v на направляющие вектора плоскости
            r_end = r_begin + ray.dir_vector
            if r_end.len() == 0:
                if abs(begin_pr1) > 1 or abs(begin_pr2) > 1:
                    if begin_pr1 > 1:
                        begin_pr1 -= 1
                    elif begin_pr1 < -1:
                        begin_pr1 += 1

                    if begin_pr2 > 1:
                        begin_pr2 -= 1
                    elif begin_pr2 < -1:
                        begin_pr2 += 1

                    return begin_pr1 * self.width + begin_pr2 * self.height

                return 0

            def find_point(ray1: Ray, ray2: Ray):
                """
                для прямой (луча) ray1
                x = t * ux + x0
                y = t * uy + y0
                z = t * uz + z0

                для прямой ray2
                x = s * vx + xr
                y = s * vy + yr
                z = s * vz + zr

                Поиск через x:
                t0 * ux + x0 = s0 * vx + xr
                s0 = (t0 * ux + x0 - xr) / vx

                t0 * uy + y0 = (t0 * ux + x0 - xr) * vy / vx + yr
                t0 * (uy - ux * vy / vx) = (x0 - xr) * vy / vx + yr - y0
                t0 = ((x0 - xr) * vy / vx + yr - y0) / (uy - ux * vy/vx)

                через y:
                s0 = (t0 * uy + y0 - yr) / vy

                to * ux + x0 = (t0 * uy + y0 - yr) * vx / vy + xr
                t0 * (ux - uy * vx / vy) = (y0 - yr) * vx / vy + xr - x0
                t0 = ((y0 - yr) * vx / vy + xr - x0) / (ux - uy * vx/vy)

                через z:
                t0 * uz + z0 = s0 * vz + zr
                s0 = (t0 * uz + z0 - zr) / vz

                t0 * uy + y0 = (t0 * uz + z0 - zr) * vy / vz + yr
                t0 * (uy - uz * vy / vz) = (z0 - zr) * vy / vz + yr - y0
                t0 = ((z0 - zr) * vy / vz + yr - y0) / (uy - uz * vy/vz)

                :param ray1:
                :param ray2:
                :return:
                """
                if ray1.dir_vector.point.coords[0] != 0:
                    x0 = ray1.init_point.coords[0]
                    y0 = ray1.init_point.coords[1]
                    xr = ray2.init_point.coords[0]
                    yr = ray2.init_point.coords[1]
                    vx = ray1.dir_vector.pos_point.coords[0]
                    vy = ray1.dir_vector.pos_point.coords[1]
                    ux = ray2.dir_vector.pos_point.coords[0]
                    uy = ray2.dir_vector.pos_point.coords[1]

                    t1 = ((x0 - xr) * vy / vx + yr - y0) \
                         / (uy - ux * vy / vx)
                    s1 = (t1 * ux + x0 - xr) / vx
                    return t1, s1

                elif ray1.dir_vector.pos_point.coords[1] != 0:
                    x0 = ray1.init_point.coords[0]
                    y0 = ray1.init_point.coords[1]
                    xr = ray2.init_point.coords[0]
                    yr = ray2.init_point.coords[1]
                    vx = ray1.dir_vector.pos_point.coords[0]
                    vy = ray1.dir_vector.pos_point.coords[1]
                    ux = ray2.dir_vector.pos_point.coords[0]
                    uy = ray2.dir_vector.pos_point.coords[1]
                    t1 = ((y0 - yr) * vx / vy + xr - x0) \
                         / (ux - uy * vx / vy)
                    s1 = (t0 * uy + y0 - yr) / vy
                    return t1, s1

                elif ray1.dir_vector.pos_point.coords[2] != 0:
                    z0 = ray1.init_point.coords[2]
                    y0 = ray1.init_point.coords[1]
                    zr = ray2.init_point.coords[2]
                    yr = ray2.init_point.coords[1]
                    vz = ray1.dir_vector.pos_point.coords[2]
                    vy = ray1.dir_vector.pos_point.coords[1]
                    uz = ray2.dir_vector.pos_point.coords[2]
                    uy = ray2.dir_vector.pos_point.coords[1]
                    t1 = ((z0 - zr) * vy / vz + yr - y0) / (
                            uy - uz * vy / vz)
                    s1 = (t0 * uz + z0 - zr) / vz
                    return t1, s1

            if abs(begin_pr1) > self.width:
                if self.u * ray.dir_vector == 0:
                    return None

                sign = 1 if begin_pr1 > 0 else -1
                t0, s0 = find_point(
                    Ray(sign * self.width * self.u.point + self.pos_point,
                        self.height * self.v), ray)
                if s0 >= 0 and abs(t0) <= 1:
                    return s0 * ray.dir_vector.length()

            elif abs(begin_pr2) > self.height:
                if self.v * ray.dir_vector == 0:
                    return None

                sign = 1 if begin_pr2 > 0 else -1
                t0, s0 = find_point(
                    Ray(sign * self.height * self.v.point + self.pos_point,
                        self.width * self.u), ray)
                if s0 >= 0 and abs(t0) <= 1:
                    return s0 * ray.dir_vector.length()

            """
            # Ограничение вектора плоскостью
            def value_limit(value, lim):
                if value < -lim:
                    value = -lim
                elif value > lim:
                    value = lim

                return value

            begin_pr1 = value_limit(begin_pr1, self.width)
            begin_pr2 = value_limit(begin_pr2, self.height)
            end_pr1 = value_limit(end_pr1, self.width)
            end_pr2 = value_limit(end_pr2, self.height)

            r_begin = self.u * begin_pr1 + self.v * begin_pr2 \
                      + Vector(self.pos)
            r_end = self.u * end_pr1 + self.v * end_pr2 \
                    + Vector(self.pos)
            # Вектор v, ограниченный плоскостью
            v_tmp = r_end - r_begin - Vector(ray.inpt)
            return Plane(self.pos, self.vector_norm).intersect(
                Ray(v_tmp, r_begin.point))
            """

    def nearest_point(self, *pts: LO.Point) -> LO.Point:
        """
        Строим два перпендикуляра от точки к плоскости,
         и от этого перпендикуляра до ребра плоскости.
        Если ближайшая точка на плоскости - вершина,
        то строим три перпендикуляра, первый к плоскости,
        второй от первого к первой границе
        (продолжению прямой, содержащей границу плоскости),
        третий - от второго перпендикуляра до второй границы плоскости.

        :param pts:
        :return:
        """
        r_min = sys.maxsize
        min_pt = LO.VectorSpace.initialPt
        r = 0
        for pt in pts:
            r_begin = LO.Vector(pt - self.pos_point)
            # Если начало вектора совпадает с центром плоскости
            if r_begin.length() == 0:
                return pt

            projection1 = r_begin * self.vector_norm / r_begin.length()
            projection2 = r_begin * self.u * self.width / r_begin.length()
            projection3 = r_begin * self.v * self.height / r_begin.length()
            sign = lambda x: 1 if x > 0 else -1
            if abs(projection2) <= 1 and abs(projection3) <= 1:
                r = projection1 * self.vector_norm.length()
            elif abs(projection2) > 1 and abs(projection3) > 1:
                proj2 = projection2 - sign(projection2)
                proj3 = projection3 - sign(projection3)
                r = self.vector_norm * -projection1 + self.u * proj2 \
                    + self.v * proj3 + LO.Vector(pt)
                r = r.len()
            elif abs(projection2) > 1:
                proj2 = projection2 - sign(projection2)
                r = self.vector_norm * -projection1 + self.u * proj2 \
                    + LO.Vector(pt)
                r = r.len()
            elif abs(projection3) > 1:
                proj3 = projection3 - sign(projection3)
                r = self.vector_norm * -projection1 + self.v * proj3 \
                    + LO.Vector(pt)
                r = r.len()

            if r < r_min:
                r_min = r
                min_pt = pt

        return min_pt


class Sphere(ParametersSphere):
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector, radius):
        super().__init__(pos_point, vector_normal, radius)

    def intersect(self, ray: Ray):
        """
        Метод нахождения точки пересечения с лучем

        По-умолчанию должен выдавать точку в конце Draw Distance

        В противном случае выдаёт точку объекта


        x = x0 + t*vx

        y = y0 + t*vy

        z = z0 + t*zy


        (x-xs)**2 + (y-ys)**2 + (z-zs)**2 = R**2

        После поставления получится квадратное уравнение, с коэф-ами a, b и c.


        В блоке if-elif происходит проверка, какая из двух точек пересечения ближе к начальной точке луча.
        Если t1 ближе, чем t2, то возвращается расстояние до t1, иначе возвращается расстояние до t2.

        :param ray:
        :return:
        """
        a = ray.dir_vector * ray.dir_vector

        b = 2 * (ray.dir_vector * LO.Vector(ray.init_point - self.pos_point))

        c = (ray.init_point.x() - self.pos_point.x()) ** 2 + \
            (ray.init_point.y() - self.pos_point.y()) ** 2 + \
            (ray.init_point.z() - self.pos_point.z()) ** 2 - \
            self.radius ** 2

        discriminant = b ** 2 - 4 * a * c

        if discriminant > 0:  # Пересечение в двух местах
            t1 = (-b + math.sqrt(discriminant)) / (2 * a)
            t2 = (-b + math.sqrt(discriminant)) / (2 * a)
            # Смотрим пересечение с поверхностью
            # Выбираем минимальный положительный
            if t2 < 0 <= t1 or 0 < t1 <= t2:
                return t1 * ray.dir_vector.length()
            elif t1 < 0 <= t2 or 0 < t2 <= t1:
                return t2 * ray.dir_vector.length()

        elif discriminant == 0:
            t0 = -b / (2 * a)
            if t0 >= 0:
                return t0 * ray.dir_vector.length()
