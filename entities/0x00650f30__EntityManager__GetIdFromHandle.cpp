// FUNC_NAME: EntityManager::GetIdFromHandle
// Address: 0x00650f30
// Role: Resolves a handle to an internal ID using either a fast path or a hash table lookup.
//       The handle is an integer key; the function returns the associated ID, or -1 if not found.

int __fastcall EntityManager::GetIdFromHandle(int handle) {
    if (handle == 0) {
        return -1;
    }

    // Fast path: either the manager has disabled the hash table (m_fastPathDisabled == 0)
    // or the handle itself has bit 1 set (possibly indicating a special type that always uses the fast path).
    if (*(int*)(this + 0x1FC) == 0 || (*(uint32_t*)(handle + 0x30) & 2) != 0) {
        return *(int*)(handle + 0x18);
    }

    // Hash table lookup
    // Bucket index = (handle / 52) % 1024  (0x34 = 52, 0x3FF = 1023)
    int bucketIndex = (handle / 0x34) & 0x3FF;
    int** bucketArray = *(int***)(this + 0x218);
    int* nodePtr = bucketArray[bucketIndex];

    while (nodePtr) {
        // nodePtr layout (offsets relative to node start):
        // +0x00: key (nodePtr[0])
        // +0x18: next pointer (nodePtr[6])
        // +0x20: flags (byte at nodePtr+8, i.e., address nodePtr+32)
        // +0x28: value (nodePtr[10])
        if (nodePtr[0] == handle && (*(uint8_t*)(nodePtr + 8) & 0x3C) == 0) {
            return nodePtr[10];
        }
        nodePtr = (int*)nodePtr[6];
    }

    return -1;
}