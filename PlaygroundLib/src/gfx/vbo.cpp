#include "../../hdr/gfx/vbo.h"
#include "OpenGL.h"

VertexBufferObject::VertexBufferObject()
    : mAttribs(0), mvertices(0)
{
    glGenBuffers(1, &mID);
}

void VertexBufferObject::bufferData(ui32 size, void* data, ui32 draw)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER,size, data, draw);
}

void VertexBufferObject::bufferSubData(ui32 elements, ui32 offset ,ui32 size, const void* data)
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    mvertices += elements;
}

void VertexBufferObject::addAttrib(ui32 amount, ui32 type, bool normalize, ui32 stride, ui32 offset)
{
    glVertexAttribPointer(mAttribs, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
    glEnableVertexAttribArray(mAttribs);
    mAttribs++;
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::clear()
{
    if(mID)
    {
        unbind();
        glDeleteBuffers(1, &mID);
    }
}