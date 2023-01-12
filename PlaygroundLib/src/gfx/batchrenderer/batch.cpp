#include "../../../hdr/gfx/batchrenderer/batch.h"
#include "../../../hdr/gfx/batchrenderer/batchvertex.h"
#include "OpenGL.h"

namespace GFX
{
	template struct Batch_<BatchVertex2D>;
	template struct Batch_<BatchVertex3D>;

    template<typename BatchType>
    Batch_<BatchType>::Batch_()
    {}

    template<typename BatchType>
    Batch_<BatchType>::Batch_(const ui32& maxVertexCount, const ui32& drawType)
        :mNumMaxVertexCount(maxVertexCount), mDrawType(drawType), mNumTexIDs(0), mMapedID(), mRenderData()
    {   
        vao.create();
        vao.bind();
        vbo.create();
        vbo.bind();
        vbo.bufferData(mNumMaxVertexCount * sizeof(BatchType), nullptr, mDrawType);

        if(std::is_same<BatchType, BatchVertex2D>::value)
		{
            vbo.addAttrib(2, GL_FLOAT, GL_FALSE, sizeof(BatchType), offsetof(BatchType, mPosition));
		}
		else
		{
            vbo.addAttrib(3, GL_FLOAT, GL_FALSE, sizeof(BatchType), offsetof(BatchType, mPosition));
		}

        vbo.addAttrib(4, GL_FLOAT, GL_FALSE, sizeof(BatchType), offsetof(BatchType, mColor));
        vbo.addAttrib(2, GL_FLOAT, GL_FALSE, sizeof(BatchType), offsetof(BatchType, mTexCoord));
        vbo.addAttrib(1, GL_FLOAT, GL_FALSE, sizeof(BatchType), offsetof(BatchType, mTexture));
    }
    
    template<typename BatchType>
    Batch_<BatchType>::~Batch_()
    {
        //vbo.unbind();
        //vao.unbind();
        //vbo.clear();
        //vao.clear();
    }
    
    template<typename BatchType>
    bool Batch_<BatchType>::hasTexture(const ui32& textureID) const
    {
        for(ui8 i = 0; i < mNumTexIDs; i++)
        {
            if(mMapedID[i].first == textureID)
            {
                return true;
            }
        }
        return false;
    }

    template<typename BatchType>
    bool Batch_<BatchType>::hasSpaceTexture() const
    {
        return mNumTexIDs < 8;
    }
    
    template<typename BatchType>
    bool Batch_<BatchType>::hasSpace(const ui32& elements) const
    {
        return (mRenderData.length() + elements) < mNumMaxVertexCount;
    }
    
    template<typename BatchType>
    bool Batch_<BatchType>::isSpaceAndTexture(const ui32& elements, const ui32& textureID) const
    {
        return hasTexture(textureID) && hasSpace(elements);
    }
    
    template<typename BatchType>
    void Batch_<BatchType>::addElement(const BatchType& element, const ui32& textureID)
    {
        if(!isSpaceAndTexture(1, textureID))
        {
            //TODO: add error msg
            return;
        }
        mRenderData.add(element);
    }

    template<typename BatchType>
    void Batch_<BatchType>::addElements(const BatchType* elements, const ui32& numElements, const ui32& textureID)
    {
        if(!isSpaceAndTexture(numElements, textureID))
        {
            //TODO: add error msg
            return;
        }
        mRenderData.add(elements, numElements);
    }
    
    template<typename BatchType>
    void Batch_<BatchType>::addElements(const List<BatchType>& elementList, const ui32& textureID)
    {
        if(!isSpaceAndTexture(elementList.length(), textureID))
        {
            //TODO: add error msg
            return;
        }
        mRenderData.add(elementList);
    }

    template<typename BatchType>
    void Batch_<BatchType>::addNewTexture(const ui32& textureID)
    {
        if(!hasSpaceTexture() || hasTexture(textureID))
        {
            //TODO: add error msg
            return;
        }
        mMapedID[mNumTexIDs] = Pair<ui32, ui32>{textureID, mNumTexIDs};
        mNumTexIDs++;
    }
    
    template<typename BatchType>
    ui32 Batch_<BatchType>::getMappedID(const ui32& textureID) const
    {
        for(auto& id : mMapedID)
        {
            if(id.first == textureID)
            {
                return id.second;
            }
        }
        return 0;
    }

    template<typename BatchType>
    void Batch_<BatchType>::draw()
    {
        if (mRenderData.length() == 0)
		{
			return;
		}

        vao.bind();
        vbo.bind();

        for (int i = 0; i < mNumTexIDs; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mMapedID[i].first);
		}

        pushToGPU();
        glDrawArrays(GL_TRIANGLES, 0, mRenderData.length());

        vbo.unbind();
        vao.unbind();

        mRenderData.clear();
    }
    
    template<typename BatchType>
    void Batch_<BatchType>::pushToGPU()
    {
        vao.bind();
        vbo.bind();
        vbo.bufferSubData(0, mRenderData.length() * sizeof(BatchType), mRenderData.at(0));
    }
    
}