// FUNC_NAME: UnknownClass::cleanupResources

void UnknownClass::cleanupResources() {
    // +0x1c: pointer to some resource (int*)
    int* resPtr1 = *(int**)(this + 0x1c);
    if (resPtr1 != nullptr) {
        releaseResource(resPtr1);          // FUN_00617320 – release internal resource
        memoryDeallocate(resPtr1);         // FUN_009c8eb0 – deallocate memory
        *(int**)(this + 0x1c) = nullptr;   // clear pointer
    }

    // +0x20: pointer to another resource (int**)
    int** resPtr2 = *(int***)(this + 0x20);
    if (resPtr2 != nullptr) {
        if (*resPtr2 != nullptr) {
            destroyResource(*resPtr2);     // FUN_009c8f10 – destroy referenced object
        }
        memoryDeallocate(resPtr2);         // FUN_009c8eb0 – deallocate pointer itself
        *(int***)(this + 0x20) = nullptr;
    }

    // +0x24: similar pattern to +0x20
    int** resPtr3 = *(int***)(this + 0x24);
    if (resPtr3 != nullptr) {
        if (*resPtr3 != nullptr) {
            destroyResource(*resPtr3);
        }
        memoryDeallocate(resPtr3);
        *(int***)(this + 0x24) = nullptr;
    }

    // +0x30: pointer to another structure
    int** resPtr4 = *(int***)(this + 0x30);
    if (resPtr4 != nullptr) {
        subSystemShutdown(this);           // FUN_006167a0 – shutdown subsystem
        if (*resPtr4 == nullptr) {
            finalCleanup();               // FUN_006165e0 – final cleanup if needed
        }
    }
}