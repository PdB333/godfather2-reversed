// FUNC_NAME: Device::processInput
int __thiscall Device::processInput(int *this, int deviceIndex) {
    char isActive;
    float floatResult;
    int stackList;
    void *listEntry;
    void *prevEntry;

    isActive = isDeviceActive(deviceIndex); // FUN_00903e60
    if (isActive != 0) {
        // Set flag 0x800 in flags at offset 0x60
        *(unsigned short *)(this + 0x60) |= 0x800;
        // Check if flags 0x3000 are not set yet
        if ((*(unsigned short *)(this + 0x60) & 0x3000) == 0) {
            // Call virtual function at vtable+0x14 (likely initialization/reconnect)
            (*(code **)(*this + 0x14))();
        }
        // Set flag 0x1000
        *(unsigned short *)(this + 0x60) |= 0x1000;

        // Check if pointer at offset 0x74 is non-null (maybe a slot/state pointer)
        if (*(int *)(this + 0x74) != 0) {
            floatResult = getDeviceTimeSinceLastUpdate(deviceIndex); // FUN_00900360
            if (floatResult <= 0.0f) {
                // Build intrusive list node from deviceIndex
                if (deviceIndex == 0) {
                    stackList = 0;
                } else {
                    stackList = deviceIndex + 0x48; // +0x48 offset to some structure member
                }
                listEntry = (void *)0;
                if (stackList != 0) {
                    listEntry = *(void **)(stackList + 4); // next pointer
                    // Insert into intrusive list at stackList
                    *(int **)(stackList + 4) = &stackList;
                }
                prevEntry = (void *)DAT_01205228; // global list head?
                enqueueCallback(&stackList); // FUN_009006f0
                if (stackList != 0) {
                    dequeueCallback(&stackList); // FUN_004daf90
                }
            }
        }
    }
    return 1;
}