# Neko Game Engine

Neko is a 3D game engine based on SDL2 and OpenGL ES 3.0 that works on Desktop, WebGL2 and Nintendo Switch (port to Android and iOS possible) used at [SAE Institute Geneva](https://sae.swiss).

## Requirements
Because we use C++17 filesystem, you will need Ubuntu 19.10 to compile with the latest libstdc++, Visual Studio 2019 is recommended on Windows.
You also need to have python 3.8 (minimum)
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

## Drawing debug data
It's possible to draw basics shapes on the screen:
### Line
``` DebugDrawer2dLocator::get().DrawLine(p1, p2); ```

### AABB
``` DebugDrawer2dLocator::get().DrawAABB(bottomLeft, topRight); ```

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