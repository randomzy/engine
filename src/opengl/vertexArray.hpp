#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glm/ext/vector_float4.hpp"
#include "opengl.hpp"
#include <limits>
#include <memory>
#include <vector>
#include <creatable.h>

// TOOD: use concept here
template<typename T>
class ScopedBind
{
public:
    ScopedBind(T const & bindable)
        : m_bindable(&bindable)
    {
        m_bindable->bind();
    }
    ScopedBind(std::shared_ptr<T> bindable)
        : m_sp_bindable(bindable)
    {
        m_sp_bindable->bind();
    }
    ~ScopedBind()
    {
        if (m_bindable)
            m_bindable->unbind();
        if (m_sp_bindable)
            m_sp_bindable->unbind();
    }
private:
    T const * m_bindable = nullptr;
    std::shared_ptr<T> m_sp_bindable;
};

enum class GLSLDatatype
{
    Bool,
    Int,
    Uint,
    Float,
    Double,

    Vec2,
    Vec3,
    Vec4,

    BVec2,
    BVec3,
    BVec4,

    IVec2,
    IVec3,
    IVec4,

    UVec2,
    UVec3,
    UVec4,

    DVec2,
    DVec3,
    DVec4,

    Mat2,
    Mat3,
    Mat4,

    Mat2x3,
    Mat2x4,

    Mat3x2,
    Mat3x4,

    Mat4x2,
    Mat4x3,
};

constexpr GLenum GLSLDatatypeToGLType(GLSLDatatype datatype)
{
    switch (datatype)
    {
        case GLSLDatatype::Float:   
        case GLSLDatatype::Vec2:    
        case GLSLDatatype::Vec3:    
        case GLSLDatatype::Vec4:    return GL_FLOAT;
        case GLSLDatatype::Int:     
        case GLSLDatatype::IVec2:   
        case GLSLDatatype::IVec3:   
        case GLSLDatatype::IVec4:   return GL_INT;
        case GLSLDatatype::Uint:    
        case GLSLDatatype::UVec2:   
        case GLSLDatatype::UVec3:   
        case GLSLDatatype::UVec4:   return GL_UNSIGNED_INT;
        case GLSLDatatype::Bool:    
        case GLSLDatatype::BVec2:   
        case GLSLDatatype::BVec3:   
        case GLSLDatatype::BVec4:   return GL_BOOL;
        case GLSLDatatype::Mat2:    
        case GLSLDatatype::Mat3:    
        case GLSLDatatype::Mat4:    
        case GLSLDatatype::Mat2x3:  
        case GLSLDatatype::Mat2x4:  
        case GLSLDatatype::Mat3x2:  
        case GLSLDatatype::Mat3x4:  
        case GLSLDatatype::Mat4x2:  
        case GLSLDatatype::Mat4x3:  return GL_FLOAT;
        default:                    return GL_INVALID_ENUM; 
    }
}

constexpr GLsizei GLSLDatatypeToSize(GLSLDatatype datatype)
{
     switch (datatype)
    {
        case GLSLDatatype::Float:   return sizeof(GLfloat);
        case GLSLDatatype::Vec2:    return sizeof(GLfloat) * 2;
        case GLSLDatatype::Vec3:    return sizeof(GLfloat) * 3;
        case GLSLDatatype::Vec4:    return sizeof(GLfloat) * 4;
        case GLSLDatatype::Int:     return sizeof(GLint);
        case GLSLDatatype::IVec2:   return sizeof(GLint) * 2;
        case GLSLDatatype::IVec3:   return sizeof(GLint) * 3;
        case GLSLDatatype::IVec4:   return sizeof(GLint) * 4;
        case GLSLDatatype::Uint:    return sizeof(GLuint);
        case GLSLDatatype::UVec2:   return sizeof(GLuint) * 2;
        case GLSLDatatype::UVec3:   return sizeof(GLuint) * 3;
        case GLSLDatatype::UVec4:   return sizeof(GLuint) * 4;
        case GLSLDatatype::Bool:    return sizeof(GLboolean);
        case GLSLDatatype::BVec2:   return sizeof(GLboolean) * 2;
        case GLSLDatatype::BVec3:   return sizeof(GLboolean) * 3;
        case GLSLDatatype::BVec4:   return sizeof(GLboolean) * 4;
        case GLSLDatatype::Mat2:    return sizeof(GLfloat) * 2 * 2;
        case GLSLDatatype::Mat3:    return sizeof(GLfloat) * 3 * 3;
        case GLSLDatatype::Mat4:    return sizeof(GLfloat) * 4 * 4;
        case GLSLDatatype::Mat2x3:  return sizeof(GLfloat) * 3 * 2;
        case GLSLDatatype::Mat2x4:  return sizeof(GLfloat) * 4 * 2;
        case GLSLDatatype::Mat3x2:  return sizeof(GLfloat) * 2 * 3;
        case GLSLDatatype::Mat3x4:  return sizeof(GLfloat) * 4 * 3;
        case GLSLDatatype::Mat4x2:  return sizeof(GLfloat) * 2 * 4;
        case GLSLDatatype::Mat4x3:  return sizeof(GLfloat) * 3 * 4;
        default:                    return GL_INVALID_ENUM; 
    }
}

constexpr GLsizei GLSLDatatypeToCount(GLSLDatatype datatype)
{
     switch (datatype)
    {
        case GLSLDatatype::Float:   return 1;
        case GLSLDatatype::Vec2:    return 2;
        case GLSLDatatype::Vec3:    return 3;
        case GLSLDatatype::Vec4:    return 4;
        case GLSLDatatype::Int:     return 1;
        case GLSLDatatype::IVec2:   return 2;
        case GLSLDatatype::IVec3:   return 3;
        case GLSLDatatype::IVec4:   return 4;
        case GLSLDatatype::Uint:    return 1;
        case GLSLDatatype::UVec2:   return 2;
        case GLSLDatatype::UVec3:   return 3;
        case GLSLDatatype::UVec4:   return 4;
        case GLSLDatatype::Bool:    return 1;
        case GLSLDatatype::BVec2:   return 2;
        case GLSLDatatype::BVec3:   return 3;
        case GLSLDatatype::BVec4:   return 4;
        case GLSLDatatype::Mat2:    return 2;
        case GLSLDatatype::Mat3:    return 3;
        case GLSLDatatype::Mat4:    return 4;
        case GLSLDatatype::Mat2x3:  return 3;
        case GLSLDatatype::Mat2x4:  return 4;
        case GLSLDatatype::Mat3x2:  return 2;
        case GLSLDatatype::Mat3x4:  return 4;
        case GLSLDatatype::Mat4x2:  return 2;
        case GLSLDatatype::Mat4x3:  return 3;
        default:               return GL_INVALID_ENUM; 
    }
}

struct AttribElement
{
    AttribElement(std::string const & name, GLuint index, GLSLDatatype datatype, bool normalized, GLsizei stride, int offset)
        : name(name)
        , index(index)
        , normalized(normalized)
        , stride(stride)
        , offset((GLvoid*)(offset))
        , datatype(datatype)
        {}
    std::string  name;
    GLuint       index;
 	GLboolean    normalized;
 	GLsizei      stride;
 	GLvoid *     offset;
    GLSLDatatype datatype;
};

class DataLayout
{
public:
    DataLayout(std::initializer_list<AttribElement> layout)
        : m_layout(layout)
    {
        if (layout.size()) {
            auto first = layout.begin();
            for (auto it = first + 1; it < layout.end(); it++) {
                assert(it->stride == first->stride);
            }
        }
    };
    auto begin() { return m_layout.begin(); }
    auto end() { return m_layout.end(); }
    auto begin() const { return m_layout.cbegin();}
    auto end() const { return m_layout.cend();}
private:
    std::vector<AttribElement> m_layout;
};

class VertexBuffer : public Creatable<VertexBuffer>
{
public:
    VertexBuffer(DataLayout layout, size_t size)
        : m_layout(layout)
    {
        glCreateBuffers(1, &m_vbo);
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }
    VertexBuffer(DataLayout layout, void * data, size_t size)
        : m_layout(layout)
    {
        glCreateBuffers(1, &m_vbo);
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    ~VertexBuffer()
    {
        glDeleteBuffers(1, &m_vbo);
    }
    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    }
    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void setData(void * data, size_t size,  size_t offset = 0)
    {
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }
    DataLayout const & getDataLayout() const
    {
        return m_layout;
    }
private:
    GLuint m_vbo;
    DataLayout m_layout;
};

class IndexBuffer : public Creatable<IndexBuffer>
{
public:
    using index_type = GLuint;
    static constexpr GLenum gl_type = GL_UNSIGNED_INT;
    
    IndexBuffer(index_type * indices, size_t count)
        : m_count(count)
    {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(index_type) * m_count, indices, GL_STATIC_DRAW);
    }
    ~IndexBuffer()
    {
        glDeleteBuffers(1, &m_ibo);
    }
    size_t count() const
    {
        return m_count;
    }
    void bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
    void unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
private:
    GLuint m_ibo;
    size_t m_count;
};

class VertexArray : public Creatable<VertexArray>
{
public:
    VertexArray()
    {
        glCreateVertexArrays(1, &m_vao);
    }
    ~VertexArray()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
    {
        m_indexBuffer = indexBuffer;
        ScopedBind<VertexArray> scopedBind(*this);
        indexBuffer->bind();
    }
    // TODO: attrib array for all shader datatypes
    void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
    {
        m_vertexBuffers.push_back(vertexBuffer);

        ScopedBind<VertexArray> scopedBind(*this);
        vertexBuffer->bind();

        const auto & layout = vertexBuffer->getDataLayout();
        for (const auto & element : layout) {
            switch (element.datatype) {
                case GLSLDatatype::Float:
                case GLSLDatatype::Vec2:
                case GLSLDatatype::Vec3:
                case GLSLDatatype::Vec4:
                    glEnableVertexAttribArray(element.index);
                    glVertexAttribPointer(
                        element.index,
                        GLSLDatatypeToCount(element.datatype),
                        GLSLDatatypeToGLType(element.datatype),
                        element.normalized,
                        element.stride,
                        element.offset
                    );
                case GLSLDatatype::Int:
                case GLSLDatatype::IVec2:
                case GLSLDatatype::IVec3:
                case GLSLDatatype::IVec4:
                case GLSLDatatype::Uint:
                case GLSLDatatype::UVec2:
                case GLSLDatatype::UVec3:
                case GLSLDatatype::UVec4:
                case GLSLDatatype::Bool:
                case GLSLDatatype::BVec2:
                case GLSLDatatype::BVec3:
                case GLSLDatatype::BVec4:

                case GLSLDatatype::Double:
                case GLSLDatatype::DVec2:
                case GLSLDatatype::DVec3:
                case GLSLDatatype::DVec4:

                case GLSLDatatype::Mat2:
                case GLSLDatatype::Mat3:
                case GLSLDatatype::Mat4:
                case GLSLDatatype::Mat2x3:
                case GLSLDatatype::Mat2x4:
                case GLSLDatatype::Mat3x2:
                case GLSLDatatype::Mat3x4:
                case GLSLDatatype::Mat4x2:
                case GLSLDatatype::Mat4x3: ;
            }
        }
    }
    void bind() const
    {
        glBindVertexArray(m_vao);
    }
    void unbind() const
    {
        glBindVertexArray(0);
    }
private:
    GLuint m_vao;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

#endif /* VERTEXARRAY_HPP */
