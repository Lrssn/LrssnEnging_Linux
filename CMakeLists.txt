cmake_minimum_required(VERSION 3.12)
project(OpenGL_Linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OpenGL_Linux
        camera.cpp
        camera.h
        main.cpp
        mesh.cpp
        mesh.h
        model.cpp
        model.h
        player.cpp
        player.h
        shader.cpp
        shader.h
        terrainCreator.cpp
        terrainCreator.h
        texture.cpp
        texture.h
        window.cpp
        window.h
		controller.cpp
		controller.h
		GameObjectContainer.cpp
		GameObjectContainer.h)
