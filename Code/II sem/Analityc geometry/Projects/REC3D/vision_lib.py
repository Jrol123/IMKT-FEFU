"""
Библиотека, ответственная за объекты, отвечающие за отрисовку объектов
"""
import configparser
import numpy as np
import math

from low_objects_lib import Point, Vector, Ray
from high_objects_lib import BoundedPlane

from low_objects_lib import Map

config = configparser.ConfigParser()
config.read("config.cfg")
height = int(config['SCREEN']['height'])
width = int(config['SCREEN']['width'])


class Camera:
    def __init__(self, position: Point, look_dir: Vector,
                 fov, draw_dist):
        """

        :param position: Расположение.
        :param look_dir: Направление камеры (Vector).
        :param fov: Горизонтальный угол обзора.
        :param vfov: = fov * W / H - вертикальный угол обзора
        :param draw_dist: Дистанция прорисовки.
        """
        self.pos = position
        self.look_dir = look_dir.normalize()

        self.fov = (fov / 180 * math.pi) / 2
        self.vfov = self.fov / (width / height)
        self.screen = BoundedPlane(
            self.pos + self.look_dir.point / math.tan(self.fov),
            self.look_dir, math.tan(self.fov), math.tan(self.vfov))

        """
        Видимость ограничена сферой с длиной радиуса Draw_distance
        Экран - проекция сферы на плоскость,
        зависящей от self.pos и look_dir.
        """
        self.draw_dist = draw_dist

    def send_rays(self) -> list[list[Ray]]:
        # Считаем расстояние от камеры до пересечения луча с объектами
        rays = []
        # Создаём лучи к каждому пикселю
        for i, s in enumerate(np.linspace(
                -self.screen.dv, self.screen.dv, height)):
            rays.append([])
            for t in np.linspace(-self.screen.du, self.screen.du,
                                 width):
                direction = Vector(self.screen.pos) \
                            + self.screen.v * s + self.screen.u * t

                direction = direction - Vector(self.pos)
                direction.point.coords[1] /= 15 / 48
                rays[i].append(Ray(self.pos, direction.normalize()))

        return rays

    def rotate(self, x_angle=0, y_angle=0, z_angle=0):
        self.look_dir.rotate(x_angle, y_angle, z_angle)
        self.screen.rotate(x_angle, y_angle, z_angle)
        self.screen.pos = self.pos + self.look_dir.point


# Список символов отрисовки, расположенных по "яркости"
symbols = " .:!/r(l1Z4H9W8$@"


class Canvas:
    def __init__(self, objmap: Map, camera: Camera):
        self.map = objmap
        self.cam = camera

    def update(self):
        rays = self.cam.send_rays()
        dist_matrix = []
        for i in range(height):
            dist_matrix.append([])
            for j in range(width):
                # rays[i][j].dir /= ((rays[i][j].dir * self.cam.look_dir)
                #                    / rays[height // 2][j].dir.len() ** 2)

                distances = rays[i][j].intersect(self.map)
                if all(d is None or d > self.cam.draw_dist
                       for d in distances):
                    dist_matrix[i].append(None)
                else:
                    dist_matrix[i].append(
                        min(filter(lambda x: x is not None, distances)))

        return dist_matrix


class Console(Canvas):
    def draw(self):
        dist_matrix = self.update()
        output_screen = ''
        for y in range(len(dist_matrix)):
            for x in range(len(dist_matrix[y])):
                if dist_matrix[y][x] is None:
                    output_screen += symbols[0]
                    continue

                try:
                    gradient = dist_matrix[y][x] / self.cam.draw_dist \
                               * (len(symbols) - 1)

                    output_screen += symbols[len(symbols)
                                             - round(gradient) - 1]
                except (IndexError, TypeError):
                    print(len(symbols) * dist_matrix[y][x]
                          / self.cam.draw_dist, dist_matrix[y][x])
                    raise

            output_screen += '\n'

        print(output_screen)
