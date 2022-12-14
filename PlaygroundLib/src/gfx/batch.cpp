#include "../../hdr/core.h"
#include "../../hdr/gfx/image.h"
#include "../../hdr/gfx/shader.h"
#include "../../hdr/gfx/batch.h"
#include "../../hdr/logger.h"
#include <OpenGL.h>

namespace GFX
{
	Batch::Batch(const ui64 maxVertices, const ui32 drawMode)
		: mMaxVertices(maxVertices), mUsedVertices(0), mVao(0), mVbo(0), mDrawMode(drawMode), mTransform(glm::mat4(1.0f)), mNumTextures(0)
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
		glBufferData(GL_ARRAY_BUFFER, mMaxVertices * sizeof(BatchVertex), nullptr, GL_STREAM_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, mColor));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, mTexCoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, mTexture));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Batch::~Batch()
	{
		
	}

	void Batch::addTexture(const Image& image)
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

	void Batch::addTexture(const ui32 image)
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

	bool Batch::hasTexture(const Image& image)
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

	bool Batch::hasTexture(const ui32 texId)
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

	bool  Batch::hasSameTextures(const ui32 ids[8])
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

	bool Batch::hasSpaceTexture()
	{
        return (mNumTextures <= 8);
	}

	ui32* Batch::getTextures()
	{
        return mTextures;
	}

    ui8 Batch::getMapedTextureIndex(const Image& image)
    {
        return mMapedTextureIndex[image.mId];
    }

    ui8 Batch::getMapedTextureIndex(const ui32& image)
    {
        return mMapedTextureIndex[image];
    }

	void Batch::add(const BatchVertex vertex)
	{
        if (mUsedVertices >= mMaxVertices)
		{
			return;
		}

		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferSubData(GL_ARRAY_BUFFER, mUsedVertices * sizeof(BatchVertex), sizeof(BatchVertex), &vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		mUsedVertices++;
	}

	void Batch::add(const BatchVertex* vertices, ui64 elements)
	{
        if ((mUsedVertices + elements) >= mMaxVertices)
		{
			return;
		}

		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferSubData(GL_ARRAY_BUFFER, mUsedVertices * sizeof(BatchVertex), sizeof(BatchVertex) * elements, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		mUsedVertices += elements;
	}

	bool Batch::hasSpace() const 
	{
        return (mMaxVertices > mUsedVertices);
	}

	bool Batch::hasSpace(const ui64 elements) const
	{
        return (mMaxVertices > (mUsedVertices + elements));
	}

	void Batch::render(Shader& shader)
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

	void Batch::clear()
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

	Image BatchHandler::mDefaultImage;

	void BatchHandler::Init()
	{
        const unsigned char whiteImage[4] = { 255, 255, 255, 255 };
		Image image(whiteImage, 1, 1, 1, "defaultWhiteSetting");
		mDefaultImage = image;
	}

	BatchHandler::BatchHandler()
	:mMaxVerticesDefault(1000), mDrawModeDefault(GL_TRIANGLES)
	{}

	BatchHandler::BatchHandler(const ui64 &maxVertices, const ui32 &drawMode)
	:mMaxVerticesDefault(maxVertices), mDrawModeDefault(drawMode)
	{}

	BatchHandler::~BatchHandler() = default;

	void BatchHandler::addBatch()
	{
        mBatches.emplace_back(Batch(mMaxVerticesDefault, mDrawModeDefault));
	}

	void BatchHandler::addBatch(const ui64& maxVertices, const ui32& drawMode)
	{
        mBatches.emplace_back(Batch(maxVertices, drawMode));
	}

	Batch* BatchHandler::getBatchHasSpace(const ui64& elements)
	{
        for (Batch& batch : mBatches)
		{
			if ((batch.mUsedVertices + elements) < batch.mMaxVertices)
			{
				return &batch;
			}
		}

		addBatch(mMaxVerticesDefault + elements, mDrawModeDefault);

		return &mBatches.back();
	}

	Batch *BatchHandler::getBatchMatchTexture(const ui32 &texture)
	{
	    for (Batch& batch : mBatches)
	    {
	        if (batch.hasTexture(texture))
	        {
	            return &batch;
	        }
	    }

	    addBatch(mMaxVerticesDefault, mDrawModeDefault);
	    Batch& batch = mBatches.back();
	    batch.addTexture(texture);
	    return &batch;
	}

	Batch* BatchHandler::getBatchHasSpaceMatchTexture(const ui64& elements, const ui32& texture)
	{
        for (Batch& batch : mBatches)
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
		Batch& batch = mBatches.back();
		batch.addTexture(texture);
		return &batch;
	}

	void BatchHandler::addImage(const Image& image)
	{
        if (image.mId == 0)
		{
			return;
		}

		for (Batch& batch : mBatches)
		{
			if (batch.hasSpaceTexture() && !batch.hasTexture(image))
			{
				batch.addTexture(image);
				return;
			}
		}

		addBatch();
		Batch& batch = mBatches.back();
		batch.addTexture(image);
	}

	void BatchHandler::addToBatch(const BatchVertex& vertex, const Image& image)
	{
        Batch* batch = getBatchHasSpaceMatchTexture(1, image.mId);
		batch->add(vertex);
	}

	void BatchHandler::addToBatch(const BatchVertex* vertices, const ui64& elements, const Image& image)
	{
        Batch* batch = getBatchHasSpaceMatchTexture(elements, image.mId);
		batch->add(vertices, elements);
	}

	void BatchHandler::addToBatch(const BatchVertex* vertices, const ui64& elements, const ui32& imageId)
    {
        Batch* batch = getBatchHasSpaceMatchTexture(elements, imageId);
        batch->add(vertices, elements);
    }

    void BatchHandler::renderBatches(Shader& shader)
	{
        shader.bind();
        int textures[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        shader.setUniformiv("uTexture[0]", textures, 8);
		for (Batch& batch : mBatches)
		{
			batch.render(shader);
		}
		shader.unbind();
	}

	void BatchHandler::clear()
	{
        for (Batch& batch : mBatches)
		{
			batch.clear();
		}
		mBatches.clear();
	}

    const Image &BatchHandler::GetDefaultImage()
    {
        return mDefaultImage;
    }
}