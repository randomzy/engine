#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glm/ext/vector_float4.hpp"
#include "opengl.hpp"
#include <limits>
#include <memory>
#include <vector>

// TOOD: use concept here
template<typename T>
class ScopedBind
{
public:
    ScopedBind(T const & bindable)
        : m_bindable(bindable)
    {
        m_bindable.bind();
    }
    ~ScopedBind()
    {
        m_bindable.unbind();
    }
private:
    T const & m_bindable;
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
        default:               return GL_INVALID_ENUM; 
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
    AttribElement(GLuint index, GLSLDatatype datatype, bool normalized, GLsizei stride, int offset)
        : m_index(index)
        , m_size(GLSLDatatypeToSize(datatype))
        , m_type(GLSLDatatypeToGLType(datatype))
        , m_normalized(normalized)
        , m_stride(stride)
        , m_offset((GLvoid*)(offset))
        , m_datatype(datatype)
        {}

    GLuint       m_index;
 	GLint        m_size;
 	GLenum       m_type;
 	GLboolean    m_normalized;
 	GLsizei      m_stride;
 	GLvoid *     m_offset;
    GLSLDatatype m_datatype;
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
                assert(it->m_stride == first->m_stride);
            }
        }
    };
private:
    std::vector<AttribElement> m_layout;
};

class VertexBuffer
{
public:
    VertexBuffer(DataLayout layout, size_t count)
        : m_layout(layout)
    {
        glCreateBuffers(1, &m_vbo);
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferData(GL_ARRAY_BUFFER, count, nullptr, GL_DYNAMIC_DRAW);
    }
    VertexBuffer(DataLayout layout, void * data, size_t count)
        : m_layout(layout)
    {
        glCreateBuffers(1, &m_vbo);
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferData(GL_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW);
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
    void setData(void * data, size_t count,  size_t offset = 0)
    {
        ScopedBind<VertexBuffer> scopedBind(*this);
        glBufferSubData(GL_ARRAY_BUFFER, offset, count, data);
    }
    DataLayout const & getDataLayout() const
    {
        return m_layout;
    }
private:
    GLuint m_vbo;
    DataLayout m_layout;
};

class IndexBuffer
{
public:
    using index_type = uint32_t;
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

class VertexArray
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
    void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
    {
        m_vertexBuffers.push_back(vertexBuffer);
        ScopedBind<VertexArray> scopedBind(*this);
        vertexBuffer->bind();
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
