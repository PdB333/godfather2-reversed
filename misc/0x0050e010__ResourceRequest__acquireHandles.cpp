// FUNC_NAME: ResourceRequest::acquireHandles
uint __thiscall ResourceRequest::acquireHandles(ResourceRequest *this, uint *outHandle0, uint *outHandle1, uint *outHandle2, uint *outHandle3)
{
    char state;
    uint handle;
    int *refCountPtr;
    void *subObj;

    state = this->m_state; // +0x5b
    // Only allow handle allocation if state is Idle(0), Loading(4), or Ready(5)
    if ((state != 0) && (state != 5) && (state != 4)) {
        return 1; // handles already present or not needed
    }

    handle = allocateHandle(); // FUN_004e9270
    *outHandle0 = handle;
    if (handle == 0) {
        return 0;
    }
    // Increment reference count if handle is valid
    if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
        if (g_handleTable[handle].ptr != NULL) { // &DAT_011a0f38 + handle*0x38
            refCountPtr = g_handleTable[handle].refCountPtr; // actually int** stored at +0x10
            *refCountPtr = *refCountPtr + 1;
        }
    }
    if (*outHandle0 == 0) {
        return 0;
    }

    subObj = this->m_subObj; // +0x24
    // Attempt slot 1: checks 4 flags at subObj+0x10..0x1c
    if ((*(uint*)((int)subObj + 0x10) != 0) ||
        (*(uint*)((int)subObj + 0x14) != 0) ||
        (*(uint*)((int)subObj + 0x18) != 0) ||
        (*(uint*)((int)subObj + 0x1c) != 0)) {
        handle = allocateHandle();
        *outHandle1 = handle;
        if (handle != 0) {
            if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
                if (g_handleTable[handle].ptr != NULL) {
                    refCountPtr = g_handleTable[handle].refCountPtr;
                    *refCountPtr = *refCountPtr + 1;
                }
            }
        }
    } else {
        *(undefined*)((int)subObj + 0x60) = 0;
    }

    // Attempt slot 2: checks 4 flags at subObj+0x20..0x2c
    if ((*(uint*)((int)subObj + 0x20) != 0) ||
        (*(uint*)((int)subObj + 0x24) != 0) ||
        (*(uint*)((int)subObj + 0x28) != 0) ||
        (*(uint*)((int)subObj + 0x2c) != 0)) {
        handle = allocateHandle();
        *outHandle2 = handle;
        if (handle != 0) {
            if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
                if (g_handleTable[handle].ptr != NULL) {
                    refCountPtr = g_handleTable[handle].refCountPtr;
                    *refCountPtr = *refCountPtr + 1;
                }
            }
        }
    }

    // Attempt slot 3: checks 4 flags at subObj+0x30..0x3c
    if ((*(uint*)((int)subObj + 0x30) != 0) ||
        (*(uint*)((int)subObj + 0x34) != 0) ||
        (*(uint*)((int)subObj + 0x38) != 0) ||
        (*(uint*)((int)subObj + 0x3c) != 0)) {
        handle = allocateHandle();
        *outHandle3 = handle;
        if (handle != 0) {
            if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
                if (g_handleTable[handle].ptr != NULL) {
                    refCountPtr = g_handleTable[handle].refCountPtr;
                    *refCountPtr = *refCountPtr + 1;
                }
            }
        }
    }

    return 1;
}

// Handle table entry structure (size 0x38)
struct HandleTableEntry {
    int field_0x00; // unknown
    int field_0x04;
    int field_0x08;
    int field_0x0C;
    int* refCountPtr; // +0x10 , points to external refcount
    char pad[0x28]; // rest up to 0x38
};

HandleTableEntry g_handleTable[0x1000]; // base at 0x011a0f28