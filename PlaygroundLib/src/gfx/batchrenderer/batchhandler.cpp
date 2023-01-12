#include "../../../hdr/gfx/batchrenderer/batchhandler.h"
#include "../../../hdr/logger.h"

namespace GFX
{
    template struct BatchHandler_<BatchVertex2D>;
	template struct BatchHandler_<BatchVertex3D>;

    template<typename BatchType>
    BatchHandler_<BatchType>::BatchHandler_()
        : mMaxVertexCount(0), mDrawType(0), mCurrentBatch(nullptr)
    {}

    template<typename BatchType>
    BatchHandler_<BatchType>::BatchHandler_(const ui32& maxVertexCount, const ui32& drawType)
        : mMaxVertexCount(maxVertexCount), mDrawType(drawType), mCurrentBatch(nullptr)
    {}

    template<typename BatchType>
    BatchHandler_<BatchType>::~BatchHandler_()
    {}

    template<typename BatchType>
    Batch_<BatchType>* BatchHandler_<BatchType>::findBatch(const ui32& numElements, const ui32& textureID)
    {
        for(const Batch_<BatchType>& batch_ : mBatches)
        {
            Batch_<BatchType>& batch = (Batch_<BatchType>&)batch_;
            bool hasSpaceAndTexture = batch.isSpaceAndTexture(numElements, textureID);

            if(hasSpaceAndTexture)
            {
                return &batch;
            }

            bool hasSpace        = batch.hasSpace(numElements);
            bool hasSpaceTexture = batch.hasSpaceTexture();

            if(hasSpace && hasSpaceTexture)
            {
                batch.addNewTexture(textureID);
                return &batch;
            }
        }

        ui32 elements = mMaxVertexCount;
        if(numElements > mMaxVertexCount)
        {
            elements += numElements;
        }
        
        mBatches.add(Batch_<BatchType>(elements, mDrawType));

        Batch_<BatchType>* rBatch = mBatches.at(mBatches.length() - 1);
        rBatch->addNewTexture(textureID);
        return rBatch;
    }

    template<typename BatchType>
    void BatchHandler_<BatchType>::getMatchingBatch(const ui32& numElements, const ui32& textureID)
    {
        mCurrentBatch = findBatch(numElements, textureID);
    }

    template<typename BatchType>
    ui32 BatchHandler_<BatchType>::getMappedID(const ui32& textureID)
    {
        if(mCurrentBatch == nullptr)
        {
            LOG_ERROR({C_HiLi("getMatchingBatch(const ui32&, const ui32&)", Green, 0)}, 
                        "The current batch is a nullptr! Call [getMatchingBatch(const ui32&, const ui32&)] befor");
            return 0;
        }
        return mCurrentBatch->getMappedID(textureID);
    }

    template<typename BatchType>
    void BatchHandler_<BatchType>::addElement(const BatchType& element, const ui32& textureID)
    {
        if(mCurrentBatch == nullptr)
        {
            LOG_ERROR({C_HiLi("getMatchingBatch(const ui32&, const ui32&)", Green, 0)}, 
                        "The current batch is a nullptr! Call [getMatchingBatch(const ui32&, const ui32&)] befor");
            return;
        }
        mCurrentBatch->addElement(element, textureID);
    }

    template<typename BatchType>
    void BatchHandler_<BatchType>::addElements(const BatchType* elements, const ui32& numElements, const ui32& textureID)
    {
        if(mCurrentBatch == nullptr)
        {
            LOG_ERROR({C_HiLi("getMatchingBatch(const ui32&, const ui32&)", Green, 0)}, 
                        "The current batch is a nullptr! Call [getMatchingBatch(const ui32&, const ui32&)] befor");
            return;
        }
        mCurrentBatch->addElements(elements, numElements, textureID);
    }

    template<typename BatchType>
    void BatchHandler_<BatchType>::addElements(const List<BatchType>& elementList, const ui32& textureID)
    {
        if(mCurrentBatch == nullptr)
        {
            LOG_ERROR({C_HiLi("getMatchingBatch(const ui32&, const ui32&)", Green, 0)}, 
                        "The current batch is a nullptr! Call [getMatchingBatch(const ui32&, const ui32&)] befor");
            return;
        }
        mCurrentBatch->addElements(elementList, textureID);
    }

    template<typename BatchType>
    void BatchHandler_<BatchType>::draw(Shader& shader)
    {
        shader.bind();

        shader.setUniformMat4("uModel", glm::mat4(1.0f));
        shader.setUniformMat4("uView", glm::mat4(1.0f));
        
        int textures[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        shader.setUniformiv("uTexture[0]", textures, 8);

        for(auto& batch_ : mBatches)
        {
            auto& batch = (Batch_<BatchType>&)batch_;
            batch.draw();
        }
    }
}