// FUNC_NAME: MemoryManager::allocateObject
// Address: 0x006836e0
// Role: Allocates memory from a pool (size 0x140) and constructs an object via a separate init function.
// Parameters: thisPtr - pointer to object to construct (pre-allocated or supplied externally)
//             heapId - identifier for the memory pool/heap context
// Returns: result of object construction if allocation succeeds, else 0.

// Structure passed to pool allocation function (offsets: 0x00 = type, 0x04 = flags, 0x08 = alignment)
struct MemoryPoolRequest {
    int32_t type;        // +0x00: allocation type (e.g., 2)
    int32_t flags;       // +0x04: allocation flags (e.g., 0x10)
    int32_t alignment;   // +0x08: alignment requirement (e.g., 0)
};

// Pool allocation function (returns non-zero if successful)
int32_t __cdecl poolAllocate(uint32_t size, MemoryPoolRequest* request, int32_t heapId);
// Object constructor (initializes the object at the given pointer)
int32_t __thiscall constructObject(void* thisPtr);

int32_t __thiscall allocateObject(void* thisPtr, int32_t heapId) {
    MemoryPoolRequest request;
    int32_t result;

    request.type = 2;
    request.flags = 0x10;
    request.alignment = 0;

    // Attempt to reserve a slot in the pool for a 0x140-byte object
    result = poolAllocate(0x140, &request, heapId);
    if (result != 0) {
        // Allocation succeeded; construct the object using the supplied pointer
        return constructObject(thisPtr);
    }
    return 0;
}