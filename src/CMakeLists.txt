add_library(opengl INTERFACE)
target_include_directories(opengl INTERFACE opengl shaders utils)

add_executable(main main.cpp)
target_link_libraries(main glad glfw glm opengl)