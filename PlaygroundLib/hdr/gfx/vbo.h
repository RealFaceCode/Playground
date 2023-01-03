#ifndef __VBO_H__
#define __VBO_H__
#include "../core.h"

struct VertexBufferObject
{
public:
    VertexBufferObject();

    void bufferData(ui32 size, void* data, ui32 draw);
    void bufferSubData(ui32 elemets, ui32 offset, ui32 size, const void* data);
    void addAttrib(ui32 amount, ui32 type, bool normalize, ui32 stride, ui32 offset);

    void bind();
    void unbind();

    void clear();
private:
    ui32 mID;
    ui32 mAttribs;
    ui32 mvertices;
};

#endif // __VBO_H__