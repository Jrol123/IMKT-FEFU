"""
Этот пакет позволяет создавать простейшую графику в консоли в 3-х мерном пространтсве.

Список зависимостей:
    math
    numpy
    abc (abstract method)
    sys
    keyboard
    pyautogui
    configparser

Artemii Popovkin [https://github.com/Jrol123/IMKT-FEFU/]
angap4@gmail.com

# License: MIT
"""

from low_objects_lib import Point, Vector, VectorSpace, Ray, Map
from high_objects_lib import Plane, BoundedPlane, Cube, Sphere
from vision_lib import Camera, Console
from action_lib import launch

__author__ = 'Artemii Popovkin'

__version__ = "0.9.1"
