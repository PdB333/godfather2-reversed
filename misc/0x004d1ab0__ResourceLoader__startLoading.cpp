// FUNC_NAME: ResourceLoader::startLoading
void ResourceLoader::startLoading(void)
{
    int* loadRequest;

    // Attempt to allocate a new async load request object
    loadRequest = (int*)allocateAsyncLoadData();
    if (loadRequest != (int*)0x0) {
        // Store the request pointer and set state to "loading" (3)
        this->mLoadRequest = loadRequest;                  // +0xC8 (200)
        this->mLoadState = 3;                              // +0xB0 (176)

        // Start asynchronous resource load with the engine function
        // Parameters: source handle, request offset 4, destination handle,
        // flags, size, callback, context, unknown
        engineLoadResourceAsync(
            this->mResourceHandle1,                        // +0xB8 (184)
            *(int*)(loadRequest + 4),                      // +4 of load request data
            this->mResourceHandle2,                        // +0xC0 (192)
            0,
            0x20000,
            0,
            loadCompleteCallback,                          // FUN_004d19a0
            this,
            0
        );
    }
    else {
        // Allocation failed; set state to "error" (2)
        this->mLoadState = 2;                              // +0xB0 (176)
    }
    return;
}