// FUNC_NAME: StreamManager::createStreamPair
// Address: 0x005dc060
// Role: Allocates and initializes two stream slots (0x24 bytes each) in an output pair structure.
//       Uses the manager's vtable callbacks for pre/post creation and temporary resource cleanup.

struct StreamSlotPair {
    void* manager;      // +0x4: reference back to the manager
    int   firstSlot;    // +0x8: first allocated slot index/pointer
    int   secondSlot;   // +0xC: second allocated slot index/pointer
};

int __thiscall StreamManager::createStreamPair(StreamManager* this, StreamSlotPair* outPair) {
    int slotIndex1 = 0;
    int slotIndex2 = 0;
    int* tempPtr = nullptr;
    int tempResult;

    // Guard null this
    if (!this) return 0;

    // Store reference to the manager in the output pair
    outPair->manager = this;

    // Begin first slot creation
    this->vtable->beginCreate();                    // vtable+8

    slotIndex1 = (int)trackableAllocate(0x24);      // FUN_009c8e50 (size 0x24)
    bool isFirstNull = (slotIndex1 == 0);

    if (!isFirstNull) {
        tempPtr = outPair->manager;                 // reload this from stored ptr
        int params[3] = {0, 0, 0};                  // uStack_14, uStack_10, uStack_c
        this->vtable->beginCreate();                // vtable+8 again
        tempResult = createResourceParams(params, tempPtr); // FUN_004265d0
        initFirstSlot();                            // FUN_005df540
    }
    outPair->firstSlot = slotIndex1;

    if (!isFirstNull) {
        if (tempResult != 0) {
            tempPtr->vtable->release(tempResult, 0); // vtable+4
        }
        tempPtr->vtable->endCreate();               // vtable+0xC
    }

    // Begin second slot creation (identical pattern)
    slotIndex2 = (int)trackableAllocate(0x24);
    bool isSecondNull = (slotIndex2 == 0);

    if (!isSecondNull) {
        tempPtr = outPair->manager;
        int params[3] = {0, 0, 0};
        this->vtable->beginCreate();
        tempResult = createResourceParams(params, tempPtr);
        initSecondSlot();                           // FUN_005dfb00
    }
    outPair->secondSlot = slotIndex2;

    if (!isSecondNull) {
        if (tempResult != 0) {
            tempPtr->vtable->release(tempResult, 0);
        }
        tempPtr->vtable->endCreate();
    }

    return 1;
}