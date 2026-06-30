// FUNC_NAME: allocateAndConstructArray
// Address: 0x005d1b60
// Role: Allocates memory for an array of objects (size 0x10 each) and constructs them using a default constructor.
// The count is passed in EDI (fastcall convention). Returns pointer to first element (skipping the count stored at offset -4).

#include <cstdint>

// Forward declarations of external functions
void* allocateMemory(uint32_t size, uint32_t flags); // FUN_005c4410
void vectorConstructorIterator(void* base, uint32_t elementSize, uint32_t count, void (*constructor)(void*)); // `vector_constructor_iterator`

// Constructor for each element (size 0x10) - defined elsewhere at LAB_005d1bb0
extern void elementConstructor(void* element);

uint32_t* allocateAndConstructArray(uint32_t count) // count passed in EDI
{
    // Calculate total size: 4 bytes for count + count * 0x10 (16 bytes per element)
    uint32_t totalSize = count * 0x10 + 4;
    // Check for overflow: if high 32 bits of (count * 0x10) are non-zero, set to all ones (saturation)
    uint32_t overflowCheck = (uint32_t)((uint64_t)count * 0x10 >> 32);
    if (overflowCheck != 0) {
        totalSize = 0xFFFFFFFF; // Saturate to max size (or error)
    }

    // Allocate memory
    uint32_t* memory = (uint32_t*)allocateMemory(totalSize, 0);
    if (memory == nullptr) {
        return nullptr;
    }

    // Store the element count at the beginning of the block
    *memory = count;

    // Construct each element using the vector constructor iterator
    // Elements start at memory + 1 (after the count), each of size 0x10
    vectorConstructorIterator(memory + 1, 0x10, count, elementConstructor);

    // Return pointer to the first element (skip the count)
    return memory + 1;
}