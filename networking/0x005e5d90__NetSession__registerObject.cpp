// FUNC_NAME: NetSession::registerObject
int NetSession::registerObject(int obj, int *outSlot, void **outVtable) {
    // in_EAX is the 'this' pointer for the NetSession (passed via EAX register)
    if (this == 0 || obj == 0) {
        return 0;
    }

    // Allocate a ghost slot (likely from a pool)
    // this+0x08: some object type/flags, this+0x14: network config
    int slot = allocateGhostSlot(*(int*)((char*)this + 0x08), *(int*)((char*)this + 0x14), 0);
    if (slot == 0) {
        return 0;
    }

    // Store the object reference in the slot (likely owner/entity pointer)
    *(int*)(slot + 0x0C) = obj;

    // Check if the slot has a vtable pointer (indicates valid ghost interface)
    if (*(int*)(slot + 0x10) != 0) {
        if (isNetworkReady()) {
            // Retrieve the first virtual method from the ghost interface
            *outSlot = slot;
            *outVtable = **(void***)(slot + 0x10);
            return 1;
        }
    }
    return 0;
}