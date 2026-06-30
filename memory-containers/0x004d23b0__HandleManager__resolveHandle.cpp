// FUNC_NAME: HandleManager::resolveHandle
int __fastcall resolveHandle(uint handle)
{
    // Hash table bucket array base pointer (DAT_012054ac)
    // Each bucket is a pointer to a linked list node chain.
    int *bucketArray = *(int **)0x012054ac;

    if (handle == 0 || bucketArray == nullptr) {
        return 0;
    }

    int node = bucketArray[handle & 0x1fff]; // hash index (13 bits -> 8192 buckets)
    while (node != 0) {
        // Node layout:
        // +0x00: (unused here)
        // +0x08: pointer to the managed object
        // +0x0c: handle value
        // +0x10: next node pointer
        if (*(uint *)(node + 0x0c) == handle) {
            return *(int *)(node + 0x08);
        }
        node = *(int *)(node + 0x10);
    }
    return 0;
}