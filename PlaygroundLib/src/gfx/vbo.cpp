#include "../../hdr/gfx/vbo.h"
#include "OpenGL.h"

VertexBufferObject::VertexBufferObject()
    : mAttribs(0), mID(0)
{}

VertexBufferObject::~VertexBufferObject()
{}

void VertexBufferObject::create()
{
    glGenBuffers(1, &mID);
}

void VertexBufferObject::bufferData(ui32 size, void* data, ui32 draw) const
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, draw);
}

void VertexBufferObject::bufferSubData(ui32 offset ,ui32 size, const void* data) const
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBufferObject::addAttrib(ui32 amount, ui32 type, bool normalize, ui32 stride, ui32 offset)
{
    glEnableVertexAttribArray(mAttribs);
    glVertexAttribPointer(mAttribs, amount, type, normalize, stride, (void*)offset);
    mAttribs++;
}

void VertexBufferObject::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBufferObject::unbind() const
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
    mID = 0;
}