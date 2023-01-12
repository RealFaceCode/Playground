#ifndef __VBO_H__
#define __VBO_H__
#include "../core.h"

struct VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void create();

    void bufferData(ui32 size, void* data, ui32 draw) const;
    void bufferSubData(ui32 offset, ui32 size, const void* data) const;
    void addAttrib(ui32 amount, ui32 type, bool normalize, ui32 stride, ui32 offset);

    void bind() const;
    void unbind() const;

    void clear();
private:
    ui32 mID;
    ui32 mAttribs;
};

#endif // __VBO_H__