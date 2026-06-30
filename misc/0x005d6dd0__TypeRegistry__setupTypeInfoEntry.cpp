// FUNC_NAME: TypeRegistry::setupTypeInfoEntry
// Address: 0x005d6dd0
// Description: Initializes a static type information entry in the engine's type registry.
// This function is called during static initialization to register a new class.
// It allocates a block from a free-list pool and sets up the vtable and metadata.

#include <cstdint>

// Forward declaration of the vtable for the registered type.
extern void* PTR_LAB_01126e88;

// Global pointer to the type registry's free list allocation pointer.
// The actual base is at 0x01206880, with the free-list pointer at offset +0x14.
// The value at that offset is an int* pointing to the next free slot in a memory block.
extern uintptr_t DAT_01206880;

// Pointer to the type name string (used as a class identifier).
extern void* DAT_00e2b1a4;

void TypeRegistry::setupTypeInfoEntry()
{
    // Get the address of the free-list pointer within the registry.
    int** freeListPtr = reinterpret_cast<int**>(DAT_01206880 + 0x14);

    // The current free slot: write the vtable pointer there.
    *freeListPtr = reinterpret_cast<int*>(&PTR_LAB_01126e88);
    // Advance the free-list pointer by one int (4 bytes).
    *freeListPtr += 1;

    // Now allocate a block of 5 ints for the type metadata.
    int* typeData = reinterpret_cast<int*>(*freeListPtr);
    typeData[0] = 0; // flags / padding
    typeData[1] = 0;
    typeData[2] = 0;
    typeData[3] = 0;
    typeData[4] = reinterpret_cast<int>(DAT_00e2b1a4); // pointer to the class name string

    // Move the free-list pointer past the 5 ints.
    *freeListPtr = typeData + 5;

    // Write the size/type ID (0x3f = 63) at the next free slot.
    **freeListPtr = 0x3f;

    // Advance the free-list pointer past this new slot.
    *freeListPtr += 1;
}