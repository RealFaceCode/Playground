#ifndef __VAO_H__
#define __VAO_H__
#include "../core.h"

struct VertexArrayObject
{
public:
    VertexArrayObject();
    void bind();
    void unbind();
    const ui32 getID() const;
    void clear();
private:
    ui32 mID;
};

#endif // __VAO_H__