#ifndef __VAO_H__
#define __VAO_H__
#include "../core.h"

struct VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void create();
    void bind() const;
    void unbind() const;
    const ui32 getID() const;
    void clear();
private:
    ui32 mID;
};

#endif // __VAO_H__