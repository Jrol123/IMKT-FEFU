"""
Высокоуровневые объекты
Plane, Sphere
"""
import math
import numpy as np
import LowObjects as LO
import UtilityObjects as UO


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
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector,
                 alpha_1: float, alpha_2: float, width: float, height: float, *delta_coords):
        """

        :param pos_point: Центр BP
        :param vector_normal: нормаль BP
        :param width: ширина BP
        :param height: высота BP
        """
        super().__init__(pos_point, vector_normal)
        self.vector_normal = vector_normal
        self.width = width
        self.height = height

        sub_normal = LO.Vector(pos_point, *(vector_normal.coords[i] + delta_coords[i] for i in range(0, 2 + 1))) \
            .normalize()

        self.sub_vector_1 = vector_normal ** sub_normal
        self.sub_vector_2 = vector_normal ** self.sub_vector_1

        self.sub_vector_1 = self.sub_vector_1.rotation_vector(alpha_1, self.vector_normal)
        # Поворачивает "влево" при alpha > 0 | [0, 1, 0] (alpha = 90) => [-1, 0, 0]
        self.sub_vector_2 = self.sub_vector_2.rotation_vector(alpha_1 + alpha_2, self.vector_normal)

        # self.sub_vector_1: LO.Vector
        # if self.vector_normal.coords != LO.VectorSpace.__getitem__(LO.VectorSpace, 1).coords:
        #     self.sub_vector_1 = self.vector_normal.rotation_eiler(0, 90, 0)
        #     # Если не совпадает с OY — поворот по OY
        # else:
        #     self.sub_vector_1 = vector_normal.rotation_eiler(90, 0, 0)
        #     # Поворот по OX
        # self.sub_vector_2 = (vector_normal ** self.sub_vector_1)

    def scaling(self, value: float):
        self.width *= value
        self.height *= value

    def rotate(self, x_angle, y_angle, z_angle):
        self.vector_normal = self.vector_normal.rotation_eiler(x_angle, y_angle, z_angle)
        self.sub_vector_1 = self.sub_vector_1.rotation_eiler(x_angle, y_angle, z_angle)
        self.sub_vector_2 = self.sub_vector_2.rotation_eiler(x_angle, y_angle, z_angle)


# class ParametersCube(Parameters):
#     """
#     Empty
#     """
#
#     def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector, alpha_1: float, alpha_2: float,
#                  width: float):
#         super().__init__(pos_point, vector_normal)
#         self.width = width
#         self.mass_edges: list[BoundedPlane][3]
#         # Реализовать инициализация массива граней через точку, смещённую по OX, Oy, OZ (выбрать)
#         pass
#
#     def move(self, move_point: LO.Point):
#         pass
#         # self.pos_point += move_point
#         #
#         # for edge in self.mass_edges:
#         # {
#         #     edge.pos_point += move_point
#         # }
#
#     def scaling(self, value):
#         pass
#         # self.width *= value
#         # for edge in self.mass_edges:
#         # {
#         #     edge.scaling(value)
#         # }
#
#     def rotate(self, x_angle, y_angle, z_angle):
#         pass
#         # self.vector_norm.rotation_eiler(x_angle, y_angle, z_angle)
#         # for edge in self.mass_edges:
#         # {
#         #     edge.rotation_eiler(x_angle, y_angle, z_angle)
#         # }


class ParametersSphere(Parameters):
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector, radius):
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

    def intersect(self, ray: UO.Ray) -> float or None:
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

    def intersect(self, ray: UO.Ray) -> None or float:
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
    def __init__(self, pos_point: LO.Point, vector_normal: LO.Vector,
                 alpha_1: float, alpha_2: float, width: float, height: float, *delta_coords):
        """

        :param pos_point:
        :param vector_normal:
        :param alpha_1: Поворот OX
        :param alpha_2: Поворот OY
        :param width:
        :param height:
        """
        super().__init__(pos_point, vector_normal, alpha_1, alpha_2, width, height, *delta_coords)

    def function(self, point: LO.Point) -> float:
        """
        Функция Bounded Plane
        :param point:
        :return:
        """
        pass

    def intersect(self, ray: UO.Ray) -> None or float:
        """

        :param ray:
        """


class Sphere(Object):
    """
    Empty
    """

    def __init__(self, pos_point: LO.Point, rotation, parameters, radius, get_equation):
        super().__init__(pos_point, rotation, parameters)
        self.radius = radius
        # self.parameters = parameters(get_equation)

    def intersect(self, ray: UO.Ray):
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

# class Cube(Object):
#     """
#     Empty
#     """
#
#     def __init__(self, pos_point: LO.Point, vector_normal, parameters):
#         """
#         Empty
#         """
#         super().__init__(pos_point, vector_normal, parameters)
