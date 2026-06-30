// FUNC_NAME: Allocator::allocateAlignedArray
// Function address: 0x005f73d0
// Role: Allocates an array of elements with alignment and header, initializes memory.
// param_1: this pointer to allocator object with vtable
// param_2: number of elements to allocate (count)
// unaff_EDI: element size (passed in EDI register / third parameter)

void* __thiscall Allocator::allocateAlignedArray(Allocator* this, int count, uint elementSize)
{
    uint alignedElementSize;
    void* memory;
    void* result;

    // Round element size up to next multiple of 4 (alignment)
    if ((elementSize & 3) != 0) {
        alignedElementSize = (elementSize - (elementSize & 3)) + 4;
    } else {
        alignedElementSize = elementSize;
    }

    // Allocation hints: type=2, alignment=4, flags=0
    struct {
        uint type;      // +0x00: allocation type (2 = array?)
        uint alignment; // +0x04: alignment requirement (4 bytes)
        uint flags;     // +0x08: flags (0)
    } allocHints = {2, 4, 0};

    // Call virtual allocation function (vtable slot 0) with total size = header(0x20) + data
    // The allocator adds a header for array metadata.
    memory = (void*)(this->vtable[0])(alignedElementSize * count + 0x20, &allocHints);
    if (memory != nullptr) {
        // Initialize the data portion of the allocation
        // Parameters: data pointer (after header), size, elementSize, elementSize? (or stride=4)
        result = initializeMemory((char*)memory + 0x20, alignedElementSize * count, elementSize, 4);
        return result;
    }
    return nullptr;
}

// Assumed helper function: initializes a block of memory (e.g., memset or custom)
// Address: 0x004abe90
void* __cdecl initializeMemory(void* dest, uint size, uint elementSize, uint stride);