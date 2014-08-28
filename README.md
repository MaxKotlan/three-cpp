three.cpp
=========

### Status
[![Build Status](https://travis-ci.org/elwinarens/three_cpp.svg)](https://travis-ci.org/elwinarens/three_cpp)

#### A port of three.js to C++ #####

[three.js](http://mrdoob.github.com/three.js/) is a popular and accessible 3D library (credits to the three.js authors for the original library and to jdduke for the initial port to C++). The goal with three.cpp is to fully implement the relevant portions of the library in C++11, up to and including revision 65.

## Usage ##

three.cpp can be compile into a static or dynamic library.

### Setup ###
* `git clone git://github.com/elwinarens/three_cpp`
* `cd three_cpp`
* `mkdir build`
* `cd build`
* `cmake ../`
* `make` (or compile generated .sln with VC)

This generates the static library `three.{a/lib}` in **three_cpp/lib**, or the dynamic library `three.{dylib/so/dll}` in **three_cpp/bin**, dependent on the `THREE_LIBRARY_STATIC` CMake flag.  Any code using the library should define `THREE_DYN_LINK` if the library is dynamic.

cmake-gui is useful if you need to configure SDL/GLEW path dependencies when compiling.


## Examples ##

Reviewing the examples in **three_cpp/examples** is probably the best way to learn how to use the library. Examples are built by default using the project files generated from CMake. To disable (assuming you're in **three_cpp/build**:

* `cmake ../ -DBUILD_THREE_EXAMPLES:BOOL=OFF`

Binaries are placed in **three_cpp/bin**.

## Sample code ##

This code creates a renderer, scene and camera, adds the camera and cube to the scene, then starts the rendering loop.

```c++

void scene() {

  using namespace three;

  auto renderer = GLRenderer::create();

  auto camera = PerspectiveCamera::create(
    75, renderer->width() / renderer->height(), 1, 10000
  );
  camera->position.z = 1000;

  auto scene = Scene::create();

  auto geometry = CubeGeometry::create( 200, 200, 200 );
  auto material = MeshBasicMaterial::create(
    Material::Paramaters().add( "color", Color(0xff0000) )
                          .add( "wireframe", true )
  );

  auto mesh = Mesh::create( geometry, material );
  scene->add( mesh );

  anim::gameLoop( [&]( float dt ) {

    mesh->rotation.x += 0.1f * dt;
    mesh->rotation.y += 0.2f * dt;

    renderer->render( *scene, *camera );

  } );

}

```

## Working examples ##

<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_custom_attributes_particles.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_custom_attributes_particles2.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_custom_attributes_particles3.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_geometry_hierarchy.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_geometry_hierarchy2.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_geometry_minecraft.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_lines_colors.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_lines_cubes.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_lines_sphere.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_particles_billboards.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_particles_billboards_colors.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_particles_random.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_particles_sprites.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_shader.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_shader2.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_shader_lava.png">
<img src="https://raw.github.com/jdduke/three_cpp/master/data/thumbs/webgl_test_memory.png">

## Status ##

This is very much a pre-alpha, early stages project: half-finished at best, with myriad TODO's and the like littered throughout. It's not pretty; effort was made to preserve the style/syntax/structure of the original library while not completely obviating the merits of native code . To be sure, this is as direct a port as possible; you will find things like public member variables, tight coupling and likely other code snippets that may or may not go against all you have come to believe in.  C++ is *not* Javascript.

* **Core** - 75% complete?
    * TODO: Morph targets, shadows, plugin support
* **Extras** - 5-10% complete?
    * TODO: Pretty much everything
* **Examples** - 25% complete?
    * TODO: Examples involving morph targets and/or model/json importing

### Performance ##
For the examples that have been ported, perf is anywhere from 2x-12x that of
three.js + WebGL on the latest Chrome version, averaging 4-5x, on my i7, GT 650m laptop (vsync disabled on both, of course). No thorough profiling or meaningful optimization has been done, and the graphics path is more or less identical to
that found in three.js.

TODO: Test with GLES (Android/iOS/NACL)

## Dependencies ##
* CMake
* SDL and GLEW for the examples (included for both MSVC and MinGW)
    * At the moment, these are required to build the library; this dependency will be optional in the future.

## Supported Platforms ##

You'll need a modern C++11 compiler:
* >= Clang 3.4
* >= GCC 4.8
* MSVC 2013

Implemented functionality tested via examples, and working on:
* Mint 13 with GCC 4.6.3
* Win 7 with both MSVC 2013 and MinGW (GCC 4.8 and 4.7)
* OSX with GCC 4.7.2 and Clang 3.1


## Troubleshooting ##

* Why is it complaining about SDL on 64-bit Win builds?
    * CMake is likely pulling in 32-bit libraries. You can manually change the *${SDL_LIBRARY}* and *${SDLMAIN_LIBRARY}* CMake variables to refer to the proper libraries; simply change the **lib** directory reference to **lib64** if using the provided SDL implementation in **externals**.
