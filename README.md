# Neko Game Engine

Neko is a 3D game engine based on SDL2 and OpenGL ES 3.0 that works on Desktop, WebGL2 and Nintendo Switch (port to Android and iOS possible) used at [SAE Institute Geneva](https://sae.swiss).

## Requirements
Because we use C++17 filesystem, you will need Ubuntu 19.10 to compile with the latest libstdc++, Visual Studio 2019 is recommended on Windows.
You also need to have [python 3.8](https://www.python.org/downloads/windows/). Don't forget to add to the the variable PATH.  You also need to have the [VulkanSDK installed](https://vulkan.lunarg.com/). After installing Vulkan you'll need to retart your computer.
## Disclaimer
This repos has been specifically made to create a custom 2D physics engine as a school project and is not intended for the development of a game.

## Libraries used
- SDL2
- GLAD
- Box2D
- googletest
- taskflow
- imgui
- sole uuid
- xxhash
- std_image

## Installation steps
1. Clone the repos
2. Launch CMake. 
3. Set the source code's path where you clone the project
4. Set the build into a folder NekoEngine/Build
5. Press "Configure" and select the version of visual studio you're using (Visual Studio 2019 is recommended). Click "Finish".
6. Once the configuration is done, click on "Generate".
7. When it's finish you can open the project
8. To check that everything is working, select main/physics_engine2d as the launching project and start the project.

## Objectives 
The physics engine must simulate a 2d rigid physics. Their must be:
 - Different type of body (static, dynamic, kinematic)
 - Collision/Trigger (box, circle, polygon)
 - Bounding volume implementation (AABB)
 - Space Partitioning (QuadTree)
 - Position and velocity correction after a collision
 - RayCasting
 - Explosion effect 
 
 To do so, every files in externals/physics can and must be modified. You can also create your own files.

Every test in test_physics must succeed and a custom test must be created to display a specific feature of the physics engine.

## Tests
You can find the google tests in test/test_physics.cpp, they cover vector, matrix and aabb. 

Here is the list of individual test that can be access through the main project physics_engine.
### 01 Rigidbody Gravity
This test instantiate one rigidbody in the center of the windows with a body. The expected result is that the body should 
fall down.

### 02 Quadtree
This test is here to visualize the use of the quadTree. The quadtree is drawn in grey.

### 03 Simple collision
The expected behavior is to see the circle fall, hit the box then completely stop moving. The box object should never
move as it's a static object.

### 04 Restitution
Their is 4 ball each with a given restitution (1, 0.66, 0.33, 0) falling on the same box collider with a restitution of 1. 
It's expected that the most left ball never stop bouncing while the ball to the right never bounce. 

## Update the repo
To update the repos you must add an upstream with this repos https://github.com/Surue/NekoEngine
```$git add remote upstream https://github.com/Surue/NekoEngine.git``` (this must be done only once)

Every time you wish to update the repos :
1. ```$git fetch upstream develop```
2. ```$git pull upstream develop```

## Drawing debug data
It's possible to draw basics shapes on the screen using the following functions. Every one of them accept an optional 
to set a specific color.
### Line
``` DebugDrawer2dLocator::get().DrawLine(p1, p2); ```

### Vector
``` DebugDrawer2dLocator::get().DrawVector(p1, direction, length); ```

### AABB
``` DebugDrawer2dLocator::get().DrawAABB(bottomLeft, topRight); ```

### Box
``` DebugDrawer2dLocator::get().DrawBox(center, extent); ```

### Circle
``` DebugDrawer2dLocator::get().DrawCircle(center, radius); ```

### Add new drawing function
To add a new function:
1. Add an abstract function in DebugDrawer2dInterface (in debug_drawer_2d.h)
2. Override it in DebugDrawer2d and NullDebugDrawer2d (int debug_drawer_2d.h)
3. Draw stuff only using line by calling ``` lineRenderer_.DrawLine(Line(p1, p2)) ```

## FAQ
Q. How can I know my Python's version? \
A. Open a console/terminal and enter ```python --version```
