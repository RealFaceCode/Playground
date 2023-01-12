#include "../../hdr/gfx/vao.h"
#include "OpenGL.h"

VertexArrayObject::VertexArrayObject()
	: mID(0)
{}

VertexArrayObject::~VertexArrayObject()
{}

void VertexArrayObject::create()
{
	glGenVertexArrays(1, &mID);
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(mID);
}

void VertexArrayObject::unbind() const
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
		mID = 0;
}