Advanced Graphics Coursework: Daniel Abraham 220392033

HeightMaps:
Created two heightmaps
Created HeightMapSceneNode header and C++ files to add them to SceneGraph and set up shader uniforms
HeightMaps have different sizes and different textures
Uses TexturedVertex-Course and TerrainFragment and Terrain2Fragment shaders
Second heightmap is a satellite of first heightmap(rotates around the first map). Created SatelliteSceneNode header and CPP files to implement rotation logic
Uses splatmap to assign textures
Water texture moves using shader logic
Sun light(direction) using shader logic

FireFlies:
FireFly header and CPP files created to make point lights with mesh as part of SceneGraph
Added 25 fireflies to each heightmap (as their child in SceneGraph)and added fragment shader logic to reflect the light
FireFlies move randomly about the scene based on their parent movement

Skymap:
Skymap added and is seamless, moving with the camera

Water:
Added water to the second height map which reflects skymap as well as light emitted by fireflies
Added WaterSceneNode to implement the water in SceneNode and to set the shader uniforms

CubeRobot:
Added CubeRobot and made changes to its update to move it. It is a child of the second heightmap

Skeletal Mesh:
Added a skeletal mesh with its animation to the first heightmap.
Skeletal mesh reflects sun light and fireflies(fireflies reflection is very subtle)

Camera
Automated camera 
Chaged camera cpp and header files
Automated camera can be stopped by pressing 3.

