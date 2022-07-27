#include "../../hdr/gfx/batch.h"

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
		glBufferData(GL_ARRAY_BUFFER, mMaxVertices * sizeof(BatchVertex), nullptr, GL_DYNAMIC_DRAW);

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
			log_warning("Failed to bind texture to batch, max textures is 8");
			return;
		}
		mTextures[mNumTextures] = image.mId;
		mNumTextures++;
	}

	void Batch::addTexture(const ui32 image)
	{
		if (mNumTextures >= 8)
		{
			log_warning("Failed to bind texture to batch, max textures is 8");
			return;
		}
		mTextures[mNumTextures] = image;
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

		GL_CHECK(glBindVertexArray(mVao);)
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, mVbo);)
		
		for (int i = 0; i < mNumTextures; i++)
		{
			GL_CHECK(glActiveTexture(GL_TEXTURE0 + i);)
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, mTextures[i]);)
		}

		GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, mUsedVertices);)
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0);)
		GL_CHECK(glBindVertexArray(0);)
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

	namespace BatchHandler
	{
		static std::vector<Batch> batches = {};
		static ui64 maxVerticesDefault = 1000;
		static ui32 drawModeDefault = GL_TRIANGLES;
		Image defaultImage;

		void SetDefaultValuesBatch(const ui64 maxVertices, const ui32 drawMode)
		{
			maxVerticesDefault = maxVertices;
			drawModeDefault = drawMode;
		}

		void Init()
		{
			const unsigned char whiteImage[4] = { 255, 255, 255, 255 };
			Image image(whiteImage, 1, 1, 1);
			defaultImage = image;
		}

		void AddBatch()
		{
			batches.emplace_back(Batch(maxVerticesDefault, drawModeDefault));
		}

		void AddBatch(const ui64 maxVertices, const ui32 drawMode)
		{
			batches.emplace_back(Batch(maxVertices, drawMode));
		}

		Batch* GetBatchHasSpace(const ui64 elements)
		{
			for (Batch& batch : batches)
			{
				if ((batch.mUsedVertices + elements) < batch.mMaxVertices)
				{
					return &batch;
				}
			}

			AddBatch(maxVerticesDefault + elements, drawModeDefault);

			return &batches.back();
		}

		Batch* GetBatchHasSpaceMatchTexture(const ui64 elements, ui32 texture)
		{
			for (Batch& batch : batches)
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

			AddBatch(maxVerticesDefault + elements, drawModeDefault);
			Batch& batch = batches.back();
			batch.addTexture(texture);
			return &batch;
		}

		void AddImage(const Image& image)
		{
			if (image.mId == 0)
			{
				return;
			}

			for (Batch& batch : batches)
			{
				if (batch.hasSpaceTexture() && !batch.hasTexture(image))
				{
					batch.addTexture(image);
					return;
				}
			}

			AddBatch();
			Batch& batch = batches.back();
			batch.addTexture(image);
		}

		void AddToBatch(const BatchVertex vertex, const Image& image)
		{
			Batch* batch = GetBatchHasSpaceMatchTexture(1, image.mId);
			batch->add(vertex);
		}

		void AddToBatch(const BatchVertex* vertices, const ui64 elements, const Image& image)
		{
			Batch* batch = GetBatchHasSpaceMatchTexture(elements, image.mId);
			batch->add(vertices, elements);
		}

		void RenderBatches(Shader& shader)
		{
			shader.bind();
            int textures[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
            shader.setUniformiv("uTexture[0]", textures, 8);
			for (Batch& batch : batches)
			{
				batch.render(shader);
			}
			shader.unbind();
		}

		void Clear()
		{
			for (Batch& batch : batches)
			{
				batch.clear();
			}
			batches.clear();
		}
	}
}