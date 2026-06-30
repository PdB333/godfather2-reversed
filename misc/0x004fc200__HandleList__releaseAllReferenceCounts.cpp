// FUNC_NAME: HandleList::releaseAllReferenceCounts
// Function address: 0x004fc200
// Role: Decrements reference counts for a list of resource handles. For each handle in the list,
// fetches its reference count from a thread-local handle table, decrements it, and if it reaches zero,
// calls the release routine.

// Known class pattern: EA EARS handle manager uses a per-thread context pointed to by fs:[0x2c].
// The structure at this+0x58 holds the number of (handle, extra) pairs stored starting at this+0x08.
// Each pair is 8 bytes: int handle (offset +0x00 from pair start) and int extra (offset +0x04).

void HandleList::releaseAllReferenceCounts(int *this)
{
    uint index = 0;
    int *currentPair = this;

    if (this[0x16] != 0) { // +0x58: count of handle pairs
        do {
            int handle = currentPair[2]; // +0x08 relative to 'this' on first iteration (pair[0].handle)
            if (handle != 0) {
                // Get the per-thread context (TLS slot at fs:[0x2c])
                int *tlsContext = *(int **)(__readfsdword(0x2c));
                int resourceExtra = currentPair[3]; // +0x0C: extra identifier (e.g., sub-index)
                // The handle table resides at (tlsContext+8) + 0x30 + handle
                int *refCountPtr = (int *)(*(int *)(tlsContext + 8) + 0x30 + handle);
                *refCountPtr = *refCountPtr - 1;
                if (*refCountPtr == 0) {
                    // Resource no longer referenced – perform actual release
                    releaseHandle(handle, resourceExtra);
                }
            }
            index = index + 1;
            currentPair = currentPair + 2; // advance to next pair (8 bytes)
        } while (index < (uint)this[0x16]);
    }
}