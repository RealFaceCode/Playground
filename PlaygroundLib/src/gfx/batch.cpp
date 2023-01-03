#include "../../hdr/core.h"
#include "../../hdr/gfx/image.h"
#include "../../hdr/gfx/shader.h"
#include "../../hdr/gfx/batch.h"
#include "../../hdr/gfx/vao.h"
#include "../../hdr/gfx/vbo.h"
#include <OpenGL.h>

namespace GFX
{
	template<typename BatchType>
	Batch<BatchType>::Batch(const ui64 maxVertices, const ui32 drawMode)
		: mMaxVertices(maxVertices), mUsedVertices(0), mVao(0), mVbo(0), mDrawMode(drawMode), mTransform(glm::mat4(1.0f)), mNumTextures(0), mBatchTypeSize(sizeof(BatchType))
	{
		mTextures[0] = 0;
		mTextures[1] = 0;
		mTextures[2] = 0;
		mTextures[3] = 0;
		mTextures[4] = 0;
		mTextures[5] = 0;
		mTextures[6] = 0;
		mTextures[7] = 0;

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, mMaxVertices * mBatchTypeSize, nullptr, GL_STREAM_DRAW);

		if(std::is_same<BatchType, BatchVertex2D>::value)
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, mBatchTypeSize, 0);
		}
		else
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mBatchTypeSize, 0);
		}

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, mBatchTypeSize, (void*)offsetof(BatchType, mColor));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mBatchTypeSize, (void*)offsetof(BatchType, mTexCoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, mBatchTypeSize, (void*)offsetof(BatchType, mTexture));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	template<typename BatchType>
	Batch<BatchType>::~Batch()
	{}

	template<typename BatchType>
	void Batch<BatchType>::addTexture(const Image& image)
	{
        if(mNumTextures >= 8)
		{
            LOG_WARNING({}, "Failed to bind texture to batch, max textures is 8");
			return;
		}
		mTextures[mNumTextures] = image.mId;
		mMapedTextureIndex.insert({image.mId, mNumTextures});
		mNumTextures++;
	}

	template<typename BatchType>
	void Batch<BatchType>::addTexture(const ui32 image)
	{
        if (mNumTextures >= 8)
		{
            LOG_WARNING({}, "Failed to bind texture to batch, max textures is 8");
			return;
		}
		mTextures[mNumTextures] = image;
        mMapedTextureIndex.insert({image, mNumTextures});
		mNumTextures++;
	}

	template<typename BatchType>
	bool Batch<BatchType>::hasTexture(const Image& image)
	{
        for (int i = 0; i < 8; i++)
		{
			if (mTextures[i] == image.mId)
			{
				return true;
			}
		}

		return false;
	}

	template<typename BatchType>
	bool Batch<BatchType>::hasTexture(const ui32 texId)
	{
        for (int i = 0; i < 8; i++)
		{
			if (mTextures[i] == texId)
			{
				return true;
			}
		}

		return false;
	}

	template<typename BatchType>
	bool  Batch<BatchType>::hasSameTextures(const ui32 ids[8])
	{
        if (mTextures[0] == ids[0]
			&& mTextures[1] == ids[1]
			&& mTextures[2] == ids[2]
			&& mTextures[3] == ids[3]
			&& mTextures[4] == ids[4]
			&& mTextures[5] == ids[5]
			&& mTextures[6] == ids[6]
			&& mTextures[7] == ids[7])
		{
			return true;
		}
		return false;
	}

	template<typename BatchType>
	bool Batch<BatchType>::hasSpaceTexture()
	{
        return (mNumTextures <= 8);
	}

	template<typename BatchType>
	ui32* Batch<BatchType>::getTextures()
	{
        return mTextures;
	}

	template<typename BatchType>
    ui8 Batch<BatchType>::getMapedTextureIndex(const Image& image)
    {
        return mMapedTextureIndex[image.mId];
    }

	template<typename BatchType>
    ui8 Batch<BatchType>::getMapedTextureIndex(const ui32& image)
    {
        return mMapedTextureIndex[image];
    }

	template<typename BatchType>
	void Batch<BatchType>::add(const BatchType vertex)
	{
        if (mUsedVertices >= mMaxVertices)
		{
			return;
		}

		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferSubData(GL_ARRAY_BUFFER, mUsedVertices * mBatchTypeSize, mBatchTypeSize, &vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		mUsedVertices++;
	}

	template<typename BatchType>
	void Batch<BatchType>::add(const BatchType* vertices, ui64 elements)
	{
        if ((mUsedVertices + elements) >= mMaxVertices)
		{
			return;
		}

		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferSubData(GL_ARRAY_BUFFER, mUsedVertices * mBatchTypeSize, mBatchTypeSize * elements, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		mUsedVertices += elements;
	}

	template<typename BatchType>
	bool Batch<BatchType>::hasSpace() const 
	{
        return (mMaxVertices > mUsedVertices);
	}

	template<typename BatchType>
	bool Batch<BatchType>::hasSpace(const ui64 elements) const
	{
        return (mMaxVertices > (mUsedVertices + elements));
	}

	template<typename BatchType>
	void Batch<BatchType>::render(Shader& shader)
	{
        if (mUsedVertices == 0)
		{
			return;
		}

		shader.setUniformMat4("uModel", mTransform);

		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		
		for (int i = 0; i < mNumTextures; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mTextures[i]);
		}

		glDrawArrays(GL_TRIANGLES, 0, mUsedVertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		mUsedVertices = 0;
	}

	template<typename BatchType>
	void Batch<BatchType>::clear()
	{
        if (mVbo)
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &mVbo);
		}

		if (mVao)
		{
			glBindVertexArray(0);
			glDeleteVertexArrays(1, &mVao);
		}

		mUsedVertices = 0;
		mMaxVertices = 0;
		mDrawMode = 0;
		mTransform = glm::mat4(0.0f);
		mNumTextures = 0;
	}

	template<typename BatchType>
	Image BatchHandler<BatchType>::mDefaultImage;
	
	template<typename BatchType>
	void BatchHandler<BatchType>::Init()
	{
        const unsigned char whiteImage[4] = { 255, 255, 255, 255 };
		Image image(whiteImage, 1, 1, 1, "defaultWhiteSetting");
		mDefaultImage = image;
	}

	template<typename BatchType>
	BatchHandler<BatchType>::BatchHandler()
		: mMaxVerticesDefault(1000), mDrawModeDefault(GL_TRIANGLES)
	{}

	template<typename BatchType>
	BatchHandler<BatchType>::BatchHandler(const ui64 &maxVertices, const ui32 &drawMode)
		: mMaxVerticesDefault(maxVertices), mDrawModeDefault(drawMode)
	{}

	template<typename BatchType>
	BatchHandler<BatchType>::~BatchHandler() = default;

	template<typename BatchType>
	void BatchHandler<BatchType>::set(const ui64& maxVertices, const ui32& drawMode)
	{
		mMaxVerticesDefault = maxVertices;
		mDrawModeDefault = drawMode;
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addBatch()
	{
        mBatches.emplace_back(Batch<BatchType>(mMaxVerticesDefault, mDrawModeDefault));
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addBatch(const ui64& maxVertices, const ui32& drawMode)
	{
        mBatches.emplace_back(Batch<BatchType>(maxVertices, drawMode));
	}

	template<typename BatchType>
	Batch<BatchType>* BatchHandler<BatchType>::getBatchHasSpace(const ui64& elements)
	{
        for (Batch<BatchType>& batch : mBatches)
		{
			if ((batch.mUsedVertices + elements) < batch.mMaxVertices)
			{
				return &batch;
			}
		}

		addBatch(mMaxVerticesDefault + elements, mDrawModeDefault);

		return &mBatches.back();
	}

	template<typename BatchType>
	Batch<BatchType> *BatchHandler<BatchType>::getBatchMatchTexture(const ui32 &texture)
	{
	    for (Batch<BatchType>& batch : mBatches)
	    {
	        if (batch.hasTexture(texture))
	        {
	            return &batch;
	        }
	    }

	    addBatch(mMaxVerticesDefault, mDrawModeDefault);
	    Batch<BatchType>& batch = mBatches.back();
	    batch.addTexture(texture);
	    return &batch;
	}

	template<typename BatchType>
	Batch<BatchType>* BatchHandler<BatchType>::getBatchHasSpaceMatchTexture(const ui64& elements, const ui32& texture)
	{
        for (Batch<BatchType>& batch : mBatches)
		{
			if ((batch.mUsedVertices + elements) < batch.mMaxVertices && batch.hasTexture(texture))
			{
				return &batch;
			}
			else if ((batch.mUsedVertices + elements) < batch.mMaxVertices && batch.hasSpaceTexture())
			{
				batch.addTexture(texture);
				return &batch;
			}
		}

		addBatch(mMaxVerticesDefault + elements, mDrawModeDefault);
		Batch<BatchType>& batch = mBatches.back();
		batch.addTexture(texture);
		return &batch;
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addImage(const Image& image)
	{
        if (image.mId == 0)
		{
			return;
		}

		for (Batch<BatchType>& batch : mBatches)
		{
			if (batch.hasSpaceTexture() && !batch.hasTexture(image))
			{
				batch.addTexture(image);
				return;
			}
		}

		addBatch();
		Batch<BatchType>& batch = mBatches.back();
		batch.addTexture(image);
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addToBatch(const BatchType& vertex, const Image& image)
	{
        Batch<BatchType>* batch = getBatchHasSpaceMatchTexture(1, image.mId);
		batch->add(vertex);
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addToBatch(const BatchType* vertices, const ui64& elements, const Image& image)
	{
        Batch<BatchType>* batch = getBatchHasSpaceMatchTexture(elements, image.mId);
		batch->add(vertices, elements);
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::addToBatch(const BatchType* vertices, const ui64& elements, const ui32& imageId)
    {
        Batch<BatchType>* batch = getBatchHasSpaceMatchTexture(elements, imageId);
        batch->add(vertices, elements);
    }

	template<typename BatchType>
    void BatchHandler<BatchType>::renderBatches(Shader& shader)
	{
        shader.bind();
        int textures[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        shader.setUniformiv("uTexture[0]", textures, 8);
		for (Batch<BatchType>& batch : mBatches)
		{
			batch.render(shader);
		}
		shader.unbind();
	}

	template<typename BatchType>
	void BatchHandler<BatchType>::clear()
	{
        for (Batch<BatchType>& batch : mBatches)
		{
			batch.clear();
		}
		mBatches.clear();
	}

	template<typename BatchType>
    const Image &BatchHandler<BatchType>::GetDefaultImage()
    {
        return mDefaultImage;
    }

	template struct Batch<BatchVertex2D>;
	template struct Batch<BatchVertex3D>;
	template struct BatchHandler<BatchVertex2D>;
	template struct BatchHandler<BatchVertex3D>;
}