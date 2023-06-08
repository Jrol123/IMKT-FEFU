"""
Библиотека, отвечающая за различные действия, зависящие от пользователя
"""
import sys

import keyboard
import pyautogui as pag
import math
import configparser

from vision_lib import Camera
from vision_lib import Console
from low_objects_lib import Vector
from high_objects_lib import BoundedPlane

config = configparser.ConfigParser()
config.read("config.cfg")

sensitivity = float(config['PLAYER']['sensitivity'])
speed = float(config['PLAYER']['speed'])

r_height = int(config['R_SCREEN']['height'])
r_width = int(config['R_SCREEN']['width'])
border = 2


class Events:
    """
    Стек событий
    """
    event_data = {}  # Множество событий

    @classmethod
    def add(cls, event: str):
        """
        Добавление событий по названию.

        Event.add("OnRender")
        function(screen):
            screen.update()

        Event.handle("OnRender", function)
        """
        cls.event_data[event] = []

    @classmethod
    def handle(cls, event: str, function: type(add)):
        """
        "Бронирует" функцию function на какое-то событие event.
        Хранение функций, соответствующих событию (списку событий).

        :param event:
        :param function:
        :return:
        """
        cls.event_data[event].append(function)

    @classmethod
    def remove(cls, event: str, function: type(add)):
        for i in range(len(cls.event_data[event])):
            if cls.event_data[event][i] is function:
                del cls.event_data[event][i]
                break

    @classmethod
    def __getitem__(cls, item):
        return cls.event_data[item]

    @classmethod
    def __iter__(cls):
        return iter(cls.event_data.keys())

    @classmethod
    def trigger(cls, event, *args):
        """
        Обрабатываются функции,
        которые исполняются в соответствии с стеком событий.


        sc1 = Canvas()
        Trigger.trigger("OnRender", sc1)
        """
        try:
            for i in range(len(cls.event_data[event])):
                called = cls.event_data[event][i](*args)
                if called is not None:
                    return called
        except KeyError:
            print("Something went wrong:", end=' ')
            print(cls.event_data[event])


def move_forward(cam: Camera):
    # Если направление обзора камеры не направлено вертикально вверх или вниз
    if cam.look_dir != Vector(0, 1, 0) \
            and cam.look_dir != Vector(0, -1, 0):
        tmp = cam.look_dir  # Проекция вектора направления обзора на плоскость, параллельную земле
        tmp.point.coords[1] = 0
        tmp = tmp.normalize()
        cam.pos = cam.pos + tmp.point * speed
        cam.screen.pos = cam.pos + cam.look_dir.point

    # Если направление обзора камеры направлено вертикально вверх или вниз
    else:
        tmp = cam.screen.v
        tmp.point.coords[1] = 0
        tmp = tmp.normalize()
        cam.pos = cam.pos - tmp.point * speed  # Гениальность
        cam.screen.pos = cam.pos + cam.look_dir.point

        # cam.pos = cam.pos - cam.screen.u.point * speed
        # cam.screen.pos = cam.pos - cam.screen.u.point

    return cam


def move_backward(cam: Camera):
    if cam.look_dir != Vector(0, 1, 0) \
            and cam.look_dir != Vector(0, -1, 0):
        tmp = cam.look_dir
        tmp.point.coords[1] = 0
        tmp = tmp.normalize()
        cam.pos = cam.pos - tmp.point * speed
        cam.screen.pos = cam.pos + cam.look_dir.point
    else:
        tmp = cam.screen.v
        tmp.point.coords[1] = 0
        tmp = tmp.normalize()
        cam.pos = cam.pos + tmp.point * speed  # Гениальность
        cam.screen.pos = cam.pos + cam.look_dir.point

        # cam.pos = cam.pos + cam.screen.u.point * speed
        # cam.screen.pos = cam.pos + cam.screen.u.point

    return cam


def move_left(cam: Camera):
    tmp = cam.screen.u
    # tmp.point.coords[1] = 0
    # tmp = tmp.norm()
    cam.pos = cam.pos - tmp.point * speed
    cam.screen.pos = cam.pos + cam.look_dir.point
    return cam


def move_right(cam: Camera):
    tmp = cam.screen.u
    # tmp.point.coords[1] = 0
    # tmp = tmp.norm()
    cam.pos = cam.pos + tmp.point * speed
    cam.screen.pos = cam.pos + cam.look_dir.point
    return cam


def move_to_viewpoint(cam: Camera):
    cam.pos = cam.pos + cam.look_dir.point * speed
    cam.screen.pos = cam.pos + cam.look_dir.point
    return cam


def move_from_viewpoint(cam: Camera):
    cam.pos = cam.pos - cam.look_dir.point * speed
    cam.screen.pos = cam.pos + cam.look_dir.point
    return cam


Events.add("w")
Events.add("s")
Events.add('a')
Events.add('d')
Events.handle('w', move_forward)
Events.handle('s', move_backward)
Events.handle('a', move_left)
Events.handle('d', move_right)


class Spectator(Camera):
    Events.add('shift + w')
    Events.add('shift + s')
    Events.handle('shift + w', move_to_viewpoint)
    Events.handle('shift + s', move_from_viewpoint)


class Player(Camera):
    pass


def launch(console: Console, camera_type: str = 'spectator'):
    """
    Функция, запускающая бесконечный цикл,
    в котором будут регистрироваться все действия пользователя
    (нажатие клавиш и перемещение мыши).

    :param console: Консоль
    :type console: Console
    :param camera_type: тип камеры ('spectator' или 'player')
    :type camera_type: str
    :ivar init_camera: Начальное положение камеры.
    :type init_camera: Spectator
    """
    assert camera_type in ('spectator', 'player')
    if camera_type == 'spectator':
        temp = console.cam
        console.cam = Spectator(temp.pos, temp.look_dir,
                                temp.fov * 360 / math.pi, temp.draw_dist)  # конвертация в градусы
        del temp
        init_camera = console.cam

        def close_console():
            """
            Закрытие консоли

            """
            print("Work was stopped with exit code 1")
            sys.exit()
            # raise SystemExit("Work was stopped with exit code 1")

        def reset_camera():
            """
            Перевод камеры в начальное положение

            """
            # Почему-то работает только с поворотом камеры. И то не всегда
            console.cam = init_camera
            pag.moveTo(pag.size()[0] // 2, pag.size()[1] // 2)  # центр экрана
            console.draw()

        def mv1(action: str):
            """
            Функция — триггер

            :param action: ключевое слово
            :type action: str

            """
            console.cam = Events.trigger(action, console.cam)
            console.draw()

        # Назначение клавиш
        keyboard.add_hotkey('ctrl+q', close_console)
        keyboard.add_hotkey('r', reset_camera)
        keyboard.add_hotkey('w', lambda: mv1('w'))
        keyboard.add_hotkey('s', lambda: mv1('s'))
        keyboard.add_hotkey('a', lambda: mv1('a'))
        keyboard.add_hotkey('d', lambda: mv1('d'))
        keyboard.add_hotkey('shift+w', lambda: mv1('shift + w'))
        keyboard.add_hotkey('shift+s', lambda: mv1('shift + s'))

        pag.moveTo(pag.size()[0] // 2, pag.size()[1] // 2)  # центр экрана
        pag.click()
        curr_pos = pag.position()

        # Поворот камеры с помощью мыши
        while True:
            something_happened = False
            new_pos = pag.position()

            if new_pos != curr_pos:
                something_happened = True
                difference = [(new_pos[0] - curr_pos[0]) * sensitivity,
                              (new_pos[1] - curr_pos[1]) * sensitivity]
                difference[0] /= (pag.size()[0] // 2)  # x
                difference[1] /= (pag.size()[1] // 2)  # y
                t, s = difference

                console.cam.look_dir = t * console.cam.screen.u \
                                       + s * console.cam.screen.v \
                                       + Vector(console.cam.screen.pos) \
                                       - Vector(console.cam.pos)
                console.cam.look_dir = console.cam.look_dir.normalize()

                console.cam.screen = BoundedPlane(
                    console.cam.pos + console.cam.look_dir.point,
                    console.cam.look_dir,
                    console.cam.screen.du, console.cam.screen.dv)

                curr_pos = new_pos
                # pag.PAUSE = 0.15

            # Проверка на событие. Если событие произошло — перерисовать
            if something_happened:
                console.draw()

            # Проверка на границы экрана
            if (new_pos[0] in (0, 1, r_height - border, r_height) or new_pos[1] in (0, 1, r_width - border, r_width)) or \
                    (new_pos[0] in (0, 1, 0 + border, 0) or new_pos[1] in (0, 1, 0 + border, 0)):
                pag.moveTo(pag.size()[0] // 2, pag.size()[1] // 2)
                curr_pos = pag.position()

    else:
        # Здесь должно быть присвоение к классу Player,
        # и перемещение камеры в соответствии с ограничениями
        # (отсутствия возможности проходить сквозь объекты),
        # но времени на раскачку нет
        pass
