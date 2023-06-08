"""
Рабочее пространство
"""
# from low_objects_lib import Point, Vector, Map
# from vision_lib import Camera, Console
# from high_objects_lib import BoundedPlane, Plane, Sphere, Cube
# from action_lib import launch
from __init__ import Point, Vector, Map, Camera, Console, Plane, BoundedPlane, Sphere, Cube, launch


cam = Camera(Point(-2, 0, 0), Vector(1, 0, 0), 90, 20)

map1 = Map()
# map1.append(Sphere(Point(1, 0.5, 0), Vector(0, 0, 1), 0.8))
# map1.append(Sphere(Point(1, 0.5, -2), Vector(0, 10, 0), 0.8))
# map1.append(Sphere(Point(1, 0.5, -4), Vector(0, 1, 0), 0.8))
map1.append(Cube(Point(10, 0, 0), Vector(1, 0, 0), 1/2))
map1.append(Sphere(Point(2, 0, 0), Vector(1, 0, 0), 1))
map1.append(BoundedPlane(Point(12, 0, 8), Vector(-1, 0, 0), 2, 2))

cons = Console(map1, cam)
# cons.map[0].pr.rotate(45, 0, 0)
cons.map[0].pr.scaling(2)
print(*cons.map[0].edges, sep='\n')  # Статус куба

launch(cons)
