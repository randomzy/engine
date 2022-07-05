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
#include "mouseEvents.hpp"

template<typename T>
T linear_map(T const & in, T const & in_low, T const & in_high, T const & out_low, T const & out_high)
{
    return (out_high - out_low)*(in - in_low)/(in_high - in_low) + out_low;
}

int main(void)
{
    const int width = 1280;
    const int height = 720;
    const std::string name = "Hello interactive triangle";
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    program.use();

    float theta = glm::radians(0.f);
    float phi = glm::radians(0.f);
    float rad = 1.f;

    auto proj = glm::perspective(30.f, float(640)/480, 0.0f, 100.f);

    glm::vec3 eye(
        rad * glm::cos(theta) * glm::sin(phi),
        rad * glm::sin(theta) * glm::sin(phi),
        rad * glm::cos(phi)
    );

    auto view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

    GLint uniP = glGetUniformLocation(program.getHandle(), "p");
    GLint uniV = glGetUniformLocation(program.getHandle(), "v");
    glUniformMatrix4fv(uniP, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(uniV, 1, GL_FALSE, glm::value_ptr(view));

    window.setEventCallback([&](Event && event){
        std::cout << event.toString() << std::endl;

        if (typeid(event) == typeid(MouseMovedEvent)) {
            MouseMovedEvent * mouse_event = static_cast<MouseMovedEvent*>(&event);
            theta = linear_map(mouse_event->getX()- width/2.f, -width/2.f, width/2.f, -glm::pi<float>(), glm::pi<float>());
            phi = linear_map(mouse_event->getY()- height/2.f, -height/2.f, height/2.f, -glm::pi<float>(), glm::pi<float>());
            std::cout << theta << " " << phi << std::endl;
            
            eye = glm::vec3(
                rad * glm::cos(theta) * glm::sin(phi),
                rad * glm::sin(theta) * glm::sin(phi),
                rad * glm::cos(phi)
            );

            view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
            glUniformMatrix4fv(uniV, 1, GL_FALSE, glm::value_ptr(view));

            event.handled = true;
        }

    });

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0,0,0,1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }

    return 0;
}
