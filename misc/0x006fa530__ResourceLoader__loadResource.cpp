// FUNC_NAME: ResourceLoader::loadResource
void __thiscall ResourceLoader::loadResource(ResourceLoader* this, const char* filePath, uint fileSize, bool isAsync)
{
    int state;
    int handle;
    char yieldFlag;
    int handleInfo;
    int fileSizeLocal; // Actually derived
    int position;
    char* defaultPath;
    int asyncHandle;

    // Check various loading states via helper functions
    state = checkIfLoaded(filePath);
    if (state != 0) {
        // Already loaded, just update file size and possibly stop sound?
        setFileSize(fileSize);
        asyncHandle = *(int*)(state + 0xc);
        handleInfo = getFileHandleInfo(asyncHandle);
        if ((handleInfo == 0) || (*(int*)(handleInfo + 0x24) != 3)) {
            if (isAsync == 0) goto LAB_006fa6ed;
            handleInfo = getFileHandleInfo(asyncHandle);
            if (handleInfo != 0) {
                setAsyncCallback(handleInfo, *(int*)0x00e448cc); // Some global
            }
        } else {
            // Handle specific state 3
            handleError();
        }
        goto LAB_006fa6e6;
    }

    // Not loaded, check streaming state
    state = checkIfStreaming(filePath);
    if (state != 0) {
        setFileSize(fileSize);
        stopSound(*(int*)(state + 0x2c), 0); // Possibly stop previous stream
        goto LAB_006fa6e6;
    }

    // Check pending state
    state = checkIfPending(filePath);
    if (state != 0) {
        setFileSize(fileSize);
        // Mark something as ready?
        *(char*)(state + 0x35) = 1;
        goto LAB_006fa6e6;
    }

    // Not in any state, proceed to allocate and open file
    state = allocateBuffer();
    if (state == 0) {
        yieldFlag = shouldYield();
        if (yieldFlag == 0) {
            if (isAsync == 0) goto LAB_006fa6ed;
            state = (int)(this) + 0x44; // Points to file handle structure
        } else {
            state = allocateBuffer(); // Try again?
        }
        if (state == 0) goto LAB_006fa6e6;
    }

    // Open file
    handle = openFile(filePath, isAsync ? *(int*)0x00e448cc : 0, 0, 0, 0);
    *(int*)(state + 0xc) = handle;
    if (handle == 0) {
        // Failed to open
        cleanup();
    } else {
        // Setup file I/O
        setBufferSize(filePath); // Maybe buffer size from path?
        setFileSize(fileSize);
        handleInfo = getFileHandleInfo(*(int*)(state + 0xc));
        position = getFilePosition(); // Current position in file
        *(int*)(this + 0x34) = *(int*)(this + 0x34) + position; // Update total bytes? 
        *(int*)(state + 0x30) = position; // Store position
        if (isAsync != 0) {
            attachToAsync(fileSize);
            *(int*)(this + 0x38) = *(int*)(state + 0xc); // Save async handle
        }
        processFile(state); // Process the file data
        registerCallback(*(int*)(state + 0xc), 2, state);
        registerCallback(*(int*)(state + 0xc), 4, this);
    }

LAB_006fa6e6:
    if (isAsync != 0) {
        return; // Async returns immediately
    }

LAB_006fa6ed:
    // Synchronous wait loop: wait until loading is done or yield says stop
    while (*(uint*)(this + 0x34) > 0x300000 && shouldYield() != 0) {
        // Busy wait, yielding each iteration
    }
    return;
}