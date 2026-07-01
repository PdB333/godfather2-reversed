// FUNC_NAME: AudioDataManager::releaseAllStreams
void __thiscall AudioDataManager::releaseAllStreams(AudioDataManager* this, void* owner)
{
    int elementIndex;
    int elementOffset;
    StreamElement* element;
    int* pRefCount;
    
    if (this->parentOwner == owner) {
        if ((this->flags & 0x02) != 0) {
            stopAllStreams();
        }
        if ((this->flags & 0x10) != 0) {
            this->releaseStreamList(&this);
        }
        this->flags &= ~0x10;
        this->someField44 = 0;
        
        elementIndex = 0;
        if (0 < this->numStreams) {
            elementOffset = 0;
            do {
                element = this->streamArray + elementOffset; // each element size 0xC0
                if (element->data1 != 0) {
                    releaseAudioData(0);
                    releaseAudioHandle(0);
                    releaseMemoryBlock(0);
                }
                if (element->data2 != 0) {
                    releaseBnkStream(0);
                }
                if (element->streamHandle->dataPtr != 0) {
                    destroyStreamData(&this, element->streamHandle);
                }
                // Decrement reference count on streamHandle and streamData
                pRefCount = element->streamHandle;
                if ((*(short*)(pRefCount + 1) != 0) &&
                    (*(short*)((int)pRefCount + 6) = *(short*)((int)pRefCount + 6) - 1,
                    *(short*)((int)pRefCount + 6) == 0)) {
                    (**(code**)*pRefCount)(1); // virtual destructor call
                }
                pRefCount = element->streamData;
                if ((*(short*)(pRefCount + 1) != 0) &&
                    (*(short*)((int)pRefCount + 6) = *(short*)((int)pRefCount + 6) - 1,
                    *(short*)((int)pRefCount + 6) == 0)) {
                    (**(code**)*pRefCount)(1);
                }
                elementOffset += 0xC0;
                elementIndex++;
            } while (elementIndex < this->numStreams);
        }
        this->numStreams = 0;
        
        // Release owner reference if present
        if (this->parentOwner != 0) {
            pRefCount = this->parentOwner;
            if ((*(short*)(pRefCount + 1) != 0) &&
                (*(short*)((int)pRefCount + 6) = *(short*)((int)pRefCount + 6) - 1,
                *(short*)((int)pRefCount + 6) == 0)) {
                (**(code**)*pRefCount)(1);
            }
            this->parentOwner = 0;
        }
        // Release another reference (likely linked list pointer)
        if (this->nextStream != 0) {
            pRefCount = this->nextStream;
            if ((*(short*)(pRefCount + 1) != 0) &&
                (*(short*)((int)pRefCount + 6) = *(short*)((int)pRefCount + 6) - 1,
                *(short*)((int)pRefCount + 6) == 0)) {
                (**(code**)*pRefCount)(1);
            }
            this->nextStream = 0;
        }
    }
    return;
}