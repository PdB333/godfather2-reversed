// FUNC_NAME: StreamManager::areAssetsReady
uint __fastcall StreamManager::areAssetsReady(StreamManager* this) {
    uint status;

    // Check if streaming system is ready; if not, return error status.
    status = isStreamingReady();  // FUN_004035a0
    if ((status & 0xFF) == 0) {
        return status & 0xFFFFFF00;
    }

    // Sum three counters at offsets 0x80, 0x81, 0x82 (bytes)
    // +0x80: countA, +0x81: countB, +0x82: countC
    uint totalCount = (uint)*(byte*)((int)this + 0x80) +
                      (uint)*(byte*)((int)this + 0x82) +
                      (uint)*(byte*)((int)this + 0x81);
    if (totalCount != 0) {
        // +0x68: pointer to an array of handles (uint32s)
        uint* handles = *(uint**)((int)this + 0x68);
        for (uint i = 0; i < totalCount; i++) {
            uint handle = getObjectFromHandle(handles[i]);  // FUN_0088dbb0
            if (handle != 0) {
                // Dereference something at handle+4
                uint* obj = (uint*)getObjectPointer(*(uint*)(handle + 4)); // FUN_004025a0
                if (obj != 0) {
                    uint objStatus = isObjectReady();  // FUN_00402c80
                    // If the object is not ready (low byte zero), break and return its status.
                    if ((objStatus & 0xFF) == 0) {
                        return objStatus & 0xFFFFFF00;
                    }
                }
            }
        }
    }
    // All assets are ready
    return 1;
}