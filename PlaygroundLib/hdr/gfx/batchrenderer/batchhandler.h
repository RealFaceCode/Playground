#ifndef __BATCHHANDLER_H__
#define __BATCHHANDLER_H__
#include "../../core.h"
#include "batchvertex.h"
#include "batch.h"
#include "../shader.h"
#include "../../util/buffer/list.h"

namespace GFX
{
    template<typename BatchType>
    struct BatchHandler_
    {
    public:
        BatchHandler_();
        BatchHandler_(const ui32& maxVertexCount, const ui32& drawType);
        ~BatchHandler_();

        Batch_<BatchType>* findBatch(const ui32& numElements, const ui32& textureID);
        void getMatchingBatch(const ui32& numElements, const ui32& textureID);
        ui32 getMappedID(const ui32& textureID);

        void addElement(const BatchType& element, const ui32& textureID);
        void addElements(const BatchType* elements, const ui32& numElements, const ui32& textureID);
        void addElements(const List<BatchType>& elementList, const ui32& textureID);

        void draw(Shader& shader);
    private:
        List<Batch_<BatchType>> mBatches;
        ui32 mMaxVertexCount;
        ui32 mDrawType;
        Batch_<BatchType>* mCurrentBatch;
    };

}

#endif // __BATCHHANDLER_H__