// FUNC_NAME: ResourceLoader::loadResource
// Function address: 0x006ffc40
// Role: Loads a resource from disk asynchronously or synchronously, copies data into class members

int __thiscall ResourceLoader::loadResource(undefined4 *this, undefined4 *sourceFields, undefined8 *sourceData, undefined4 param_4) {
    char readResult;
    int loadResult; // iVar2
    undefined4 allocHandle;
    int local_18[2]; // for some cleanup
    undefined1 local_10[16]; // buffer for reading

    local_18[0] = 0;
    local_18[1] = 0;

    // Start async load: priority 0, size 0x708, global resource name, callback at LAB_006ff930, this pointer as context
    loadResult = resourceLoadAsync(0, 0x708, DAT_00d5ddec, &LAB_006ff930, this);

    if (local_18[0] != 0) {
        memFree(local_18); // free intermediate buffer if allocated
    }

    if (loadResult == 2) { // Async completed
        // Allocate a buffer (0x708 sized structure)
        allocHandle = allocateBuffer();
        this[7] = allocHandle; // +0x1C = buffer handle
        this[8] = 2; // +0x20 = state? (2 = loaded)
        registerCallback(&LAB_006ff3f0, this); // register another callback?

        local_18[0] = 0;
        local_18[1] = 0;
        // Read data block into local buffer with flags 0x800014
        readResult = readDataBlock(sourceFields, local_10, 0, 0x800014, param_4);
        if (local_18[0] != 0) {
            memFree(local_18);
        }
        if (readResult != '\0') {
            // Copy source fields into this
            this[0] = sourceFields[0]; // +0x00
            this[1] = sourceFields[1]; // +0x04
            this[2] = sourceFields[2]; // +0x08
            this[3] = sourceFields[3]; // +0x0C
            // Copy 8-byte source data into offsets +0x10 and +0x14
            *(undefined8 *)(this + 4) = *sourceData;
            this[6] = *(undefined4 *)(sourceData + 1); // +0x18 = low 4 bytes of second 8-byte
            if (this[7] != 0) { // +0x1C buffer allocated
                releaseBuffer(0x708); // release buffer of size 0x708
                freeBuffer(sourceData); // free source data?
                unregisterCallback();
                return 1;
            }
        }
        this[8] = 0; // reset state
        unregisterCallback();
        return 0;
    }

    if (loadResult == 1) { // Data already available (e.g., cached)
        // Copy directly without buffer allocation
        this[0] = sourceFields[0];
        this[1] = sourceFields[1];
        this[2] = sourceFields[2];
        this[3] = sourceFields[3];
        *(undefined8 *)(this + 4) = *sourceData;
        undefined4 temp = *(undefined4 *)(sourceData + 1);
        this[8] = 1; // +0x20 state = 1 (ready)
        this[6] = temp; // +0x18
        return 1;
    }

    return 0; // loadResult == 0 -> failed to start
}