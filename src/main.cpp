#include "opengl.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "fs.hpp"

int main(void)
{
    Context context(640, 480, "Hello triangle");

    Program program({
        Shader(load_file("src/shaders/triangle_vert.glsl").c_str(), GL_VERTEX_SHADER),
        Shader(load_file("src/shaders/triangle_frag.glsl").c_str(), GL_FRAGMENT_SHADER)
    });

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    program.use();

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0,0,0,1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        context.swapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
