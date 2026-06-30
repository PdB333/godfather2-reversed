// FUNC_NAME: SomeClass::SomeClass (constructor)

void __thiscall SomeClass::SomeClass(void* this, uint32 param1, uint32 param2) {
    // Allocate some memory or initialize something with size 0x1E (30)
    FUN_00a72c80(0x1E); // Could be heapAllocate(30) or similar

    // Set up vtable pointers (multiple inheritance)
    *reinterpret_cast<uint32*>(this) = &PTR_FUN_00e39ff4;   // +0x00 first vtable
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x04) = &PTR_LAB_00e3a018; // +0x04 second vtable?

    // Store parameters
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x18) = param2; // +0x18
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x34) = param1; // +0x34

    // Initialize multiple fields to zero
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x38) = 0; // +0x38
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x3C) = 0; // +0x3C
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x40) = 0; // +0x40
    *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x44) = 0; // +0x44

    // Set byte flag to 1
    *reinterpret_cast<uint8*>(reinterpret_cast<uint8*>(this) + 0x48) = 1; // +0x48

    // Allocate a 0x14 (20) byte block
    uint32* newBlock = reinterpret_cast<uint32*>(FUN_009c8e50(0x14)); // e.g., new or malloc
    if (newBlock != nullptr) {
        // Local struct with fields: (2, 0x10, 0)
        struct {
            uint32 field0;
            uint32 field4;
            uint32 field8;
        } localStruct = {2, 0x10, 0};

        // Get some manager/interface pointer
        int* managerPtr = reinterpret_cast<int*>(FUN_009c8f80()); // e.g., getManager()
        uint32 result = FUN_004265d0(&localStruct, managerPtr);   // e.g., createResource()

        // Populate the new block
        newBlock[3] = result;   // +0x0C
        newBlock[4] = reinterpret_cast<uint32>(managerPtr); // +0x10

        // Call a virtual function on managerPtr (index 2 = third function)
        (*(void (**)(void))(*managerPtr + 8))();

        // Zero out first three fields
        newBlock[0] = 0; // +0x00
        newBlock[2] = 0; // +0x08
        newBlock[1] = 0; // +0x04

        // Store block pointer in this
        *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x30) = reinterpret_cast<uint32>(newBlock); // +0x30
    } else {
        *reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x30) = 0; // +0x30
    }
}