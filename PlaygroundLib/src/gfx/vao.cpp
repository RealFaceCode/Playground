#include "../../hdr/gfx/vao.h"
#include "OpenGL.h"

VertexArrayObject::VertexArrayObject()
	: mID(0)
{
    glGenVertexArrays(1, &mID);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(mID);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

const ui32 VertexArrayObject::getID() const
{
    return mID;
}

void VertexArrayObject::clear()
{
    	if (mID)
		{
			unbind();
			glDeleteVertexArrays(1, &mID);
		}
}