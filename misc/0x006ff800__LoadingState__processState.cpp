// FUNC_NAME: LoadingState::processState
void __thiscall LoadingState::processState(int thisPtr, int stateId)
{
    char loadResult;
    int resourceLoaderPtr;
    int unusedBuffer[2]; // local_18, initialized to 0
    char resourceNameBuffer[16]; // local_10

    if (stateId == 2) {
        // State: start loading
        resourceLoaderPtr = allocateResourceLoader(); // +0x1c
        *(int *)(thisPtr + 0x1c) = resourceLoaderPtr;
        if (resourceLoaderPtr != 0) {
            // Set the update callback (function at 0x006ff3f0)
            setUpdateCallback(&LAB_006ff3f0, thisPtr); // +0x???
            unusedBuffer[0] = 0;
            unusedBuffer[1] = 0;
            // Request a resource load (flags 0x800014, priority 1.0f)
            loadResult = requestLoad(thisPtr, resourceNameBuffer, 0, 0x800014, 0x3f800000);
            if (unusedBuffer[0] != 0) {
                releaseMemory(unusedBuffer); // free buffer if allocated
            }
            if ((loadResult != '\0') && (*(int *)(thisPtr + 0x1c) != 0)) {
                // Load succeeded, initialize the resource
                beginLoad(0x708); // resource type/size 0x708
                initializeLoader(thisPtr + 0x10); // +0x10 is loader object
                endLoad();
                return;
            }
            // Load failed, reset state
            *(undefined4 *)(thisPtr + 0x20) = 0;
            endLoad();
        }
    }
    else if ((stateId == 4) || (stateId == 3)) {
        // State: cancel or abort – clear state
        *(undefined4 *)(thisPtr + 0x20) = 0;
        return;
    }
    return;
}