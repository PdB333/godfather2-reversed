// FUNC_NAME: ResourceHandleManager::releaseSlot
// Address: 0x007ee880
// Role: Decrements reference counts for a resource handle. The manager maintains a total ref count and per-slot counters.
// When total ref count reaches 1 (last external reference), the associated data pointer is freed.
// Returns pointer to the decremented per-slot counter byte (for caller to check if zero).

// Forward declarations
class ResourceHandle;
void deallocate(void* ptr); // FUN_009c8eb0 – likely heap deallocation

class ResourceHandleManager {
public:
    // +0x00: vtable (not directly used in this function)
    void* vtable;

    // +0x04: first handle pointer (cleared if matching param_2)
    ResourceHandle* pFirstHandle;

    // +0x08: second handle pointer (cleared if matching param_2)
    ResourceHandle* pSecondHandle;

    // +0x0C: total reference count (decremented each release)
    int totalRefCount;

    // +0x10: pointer to shared data (freed when totalRefCount reaches 1)
    void* pData;

    // +0x14: variable-length array of per-slot reference counters (byte)
    // Access via index from handle->slotIndex
    unsigned char slotCounters[];

    /**
     * Release a referenced handle, decrementing both total and per-slot counters.
     * @param handle The handle to release. Must have slotIndex at offset 0x12.
     * @return Pointer to the decremented per-slot counter byte.
     */
    int __thiscall releaseSlot(ResourceHandle* handle);
};

// handle structure – only known field is slotIndex at +0x12
struct ResourceHandle {
    // ... unknown fields ...
    // +0x12: byte index into slotCounters array
    unsigned char slotIndex;
};

int __thiscall ResourceHandleManager::releaseSlot(ResourceHandle* handle) {
    unsigned char slotIdx;
    unsigned char* pCounter;

    // Decrement total reference count
    this->totalRefCount--;

    // If total count dropped to 1, free the data pointer (last external reference)
    if (this->totalRefCount == 1) {
        if (this->pData != nullptr) {
            deallocate(this->pData);
        }
        this->pData = nullptr;
    }

    // Decrement per-slot counter using handle's slot index
    slotIdx = handle->slotIndex;               // handle->slotIndex at +0x12
    pCounter = &this->slotCounters[slotIdx];   // slotCounters begin at +0x14
    (*pCounter)--;

    // Clear stored handle pointers if they match the input handle
    if (this->pFirstHandle == handle) {
        this->pFirstHandle = nullptr;
    }
    if (this->pSecondHandle == handle) {
        this->pSecondHandle = nullptr;
    }

    // Return address of the decremented per-slot counter byte
    return reinterpret_cast<int>(pCounter);
}