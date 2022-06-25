add_library(opengl STATIC 
    window/window.cpp)
target_include_directories(opengl PUBLIC opengl shaders utils window)
target_link_libraries(opengl glad glfw glm)

add_executable(main main.cpp)
target_link_libraries(main opengl)