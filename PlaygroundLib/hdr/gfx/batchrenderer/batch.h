#ifndef __BATCH_H__
#define __BATCH_H__
#include "../../core.h"
#include "../../util/buffer/list.h"
#include "../../util/buffer/pair.h"
#include "../shader.h"
#include "../vao.h"
#include "../vbo.h"

namespace GFX
{
    template<typename BatchType>
    struct Batch_
    {
    public:
        Batch_();
        Batch_(const ui32& maxVertexCount, const ui32& drawType);
        ~Batch_();
        bool hasTexture(const ui32& textureID) const;
        bool hasSpaceTexture() const;
        bool hasSpace(const ui32& elements) const;
        bool isSpaceAndTexture(const ui32& elements, const ui32& textureID) const;

        void addElement(const BatchType& element, const ui32& textureID);
        void addElements(const BatchType* elements, const ui32& numElements, const ui32& textureID);
        void addElements(const List<BatchType>& elementList, const ui32& textureID);
        void addNewTexture(const ui32& textureID);

        ui32 getMappedID(const ui32& textureID) const;

        void draw();
    private:
        void pushToGPU();
    public:
        VertexArrayObject vao;
        VertexBufferObject vbo;
        ui8 mNumTexIDs;
        ui32 mNumMaxVertexCount;
        ui32 mDrawType;
        std::array<Pair<ui32, ui32>, 8> mMapedID;
        List<BatchType> mRenderData;
    };
}
#endif // __BATCH_H__