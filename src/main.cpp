#include "glm/ext/vector_float3.hpp"
#include "opengl.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "window.hpp"
#include "fs.hpp"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
    const int width = 1280;
    const int height = 720;
    const std::string name = "Hello triangle still";
    Window window(width, height, name);

    Program program({
        Shader(load_file("src/shaders/triangle_vert.glsl").c_str(), GL_VERTEX_SHADER),
        Shader(load_file("src/shaders/triangle_frag.glsl").c_str(), GL_FRAGMENT_SHADER)
    });

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    program.use();

    auto proj = glm::mat4(1.f);
    auto view = glm::mat4(1.f);

    GLint uniP = glGetUniformLocation(program.getHandle(), "p");
    GLint uniV = glGetUniformLocation(program.getHandle(), "v");
    glUniformMatrix4fv(uniP, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(uniV, 1, GL_FALSE, glm::value_ptr(view));

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0,0,0,1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }

    return 0;
}
