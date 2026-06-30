// FUNC_NAME: MemoryAllocator::allocateNode
// Address: 0x00623880
// Allocates a 40‑byte node from a custom allocator and initializes its fields.
// The allocator object has a vtable pointer at offset +0x4 and an optional embedded buffer pointer at +0x8.

void __thiscall MemoryAllocator::allocateNode(int this)
{
    int* nodePtr;
    int localBuffer[3]; // used as a fallback when embedded buffer is null

    // Retrieve embedded buffer pointer (offset +0x8 from allocator object)
    nodePtr = *reinterpret_cast<int**>(this + 8);

    // If no embedded buffer, use a local stack buffer as a hint
    if (nodePtr == nullptr) {
        localBuffer[0] = 0;
        localBuffer[1] = 0;
        localBuffer[2] = 0;
        nodePtr = localBuffer;
    }

    // Call virtual allocation function from vtable (vtable pointer at offset +0x4)
    // vtable[0] takes size (0x28 = 40 bytes) and an optional buffer hint
    nodePtr = reinterpret_cast<int*>(
        (*(code**)(**(int***)(this + 4)))(0x28, nodePtr)   // calls virtual function
    );

    // Zero out the first three dword fields (offsets 0x00, 0x04, 0x08)
    if (nodePtr != nullptr) {
        *nodePtr = 0;             // offset 0x00
    }
    if (nodePtr + 1 != nullptr) {
        *(nodePtr + 1) = 0;      // offset 0x04
    }
    if (nodePtr + 2 != nullptr) {
        *(nodePtr + 2) = 0;      // offset 0x08
    }

    // Set byte at offset 0x25 (37) to 0
    *reinterpret_cast<byte*>(reinterpret_cast<uintptr_t>(nodePtr) + 0x25) = 0;

    // Set byte at offset 0x24 (36) to 1 (accessed via nodePtr + 9 as dword pointer)
    *reinterpret_cast<byte*>(nodePtr + 9) = 1;
}