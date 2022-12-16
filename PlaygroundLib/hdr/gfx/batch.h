#include "../core.h"
#include "gfx.h"

#ifndef BATCH_H
#define BATCH_H

namespace GFX
{
    struct Image;
    struct Shader;

	struct BatchVertex
	{
	public:
		glm::vec2 mPosition;
		glm::vec4 mColor;
		glm::vec2 mTexCoord;
        f32 mTexture;
	};

	struct Batch
	{
	public:
		Batch(const ui64 maxVertices, const ui32 drawMode);
		~Batch();

		void addTexture(const Image& image);
		void addTexture(const ui32 image);
		bool hasTexture(const Image& image);
		bool hasTexture(const ui32 texId);
		bool hasSameTextures(const ui32 ids[8]);
		ui32* getTextures();
		bool hasSpaceTexture();

		ui8 getMapedTextureIndex(const Image& image);
        ui8 getMapedTextureIndex(const ui32& image);

		void add(const BatchVertex vertex);
		void add(const BatchVertex* vertices, ui64 elements);
		bool hasSpace() const;
		bool hasSpace(const ui64 elements) const;
		void render(Shader & shader);
		void clear();
	public:
	    ui64 mMaxVertices;
	    ui64 mUsedVertices;
	    ui32 mVao;
	    ui32 mVbo;
	    ui32 mDrawMode;
	    glm::mat4 mTransform;
	    ui8 mNumTextures;
	    ui32 mTextures[8];
	    std::unordered_map<ui32, ui8> mMapedTextureIndex;
	};

	struct BatchHandler
	{
    public:
	    static void Init();
	    BatchHandler();
	    BatchHandler(const ui64& maxVertices, const ui32& drawMode);
	    ~BatchHandler();
	    void addBatch();
	    void addBatch(const ui64& maxVertices, const ui32& drawMode);
	    void addImage(const Image& image);
	    Batch* getBatchHasSpace(const ui64& elements);
	    Batch* getBatchMatchTexture(const ui32& texture);
	    Batch* getBatchHasSpaceMatchTexture(const ui64& elements, const ui32& texture);
	    void addToBatch(const BatchVertex& vertex, const Image& image = mDefaultImage);
	    void addToBatch(const BatchVertex* vertices, const ui64& elements, const Image& image = mDefaultImage);
	    void addToBatch(const BatchVertex* vertices, const ui64& elements, const ui32& imageId);
	    void renderBatches(Shader& shader);
	    void clear();
	    static const Image& GetDefaultImage();
	private:
	    std::vector<Batch> mBatches;
	    ui64 mMaxVerticesDefault;
	    ui32 mDrawModeDefault;
	    static Image mDefaultImage;
	};
}
#endif