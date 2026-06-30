// FUNC_NAME: Grid2D::initialize
// Address: 0x004c6fa0
// This function initializes a 2D grid structure (possibly a tile map or navigation graph).
// It receives an additional parameter in `edi` (likely a pointer to external data) stored at +0xA8.
// It registers two static callbacks and allocates two memory pools based on capacity fields.

void __thiscall Grid2D::initialize(/* implicit edi param passed in register */)
{
    // Register first callback with table at PTR_LAB_00e3653c
    uint *pCapacityY = reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x98); // offset +0x98
    // Store edi value (external data pointer) at +0xA8
    *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0xA8) = unaff_EDI;

    // Set up local pointer for first registration
    undefined1 **table1 = &PTR_LAB_00e3653c; // static table pointer
    FUN_0049f960(FUN_0049ead0, &table1);  // register callback

    // Second callback with table at PTR_LAB_00e36548
    uint *pCapacityX = reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0xA0); // offset +0xA0
    undefined1 **table2 = &PTR_LAB_00e36548;
    uint *tempPtr = pCapacityX;
    FUN_0049f960(FUN_0049eb20, &table2);  // register callback

    // Only proceed if both capacity fields are non-zero
    if ((*pCapacityX != 0) && (*pCapacityY != 0))
    {
        // Allocate first buffer: size = capacityY * 0x50 (80 bytes per element)
        // The size computation handles 64-bit overflow by clamping to 0xFFFFFFFF if high 32 bits non-zero
        unsigned long long fullSizeY = static_cast<unsigned long long>(*pCapacityY) * 0x50;
        uint sizeY = (static_cast<int>(fullSizeY >> 32) != 0) ? 0xFFFFFFFF : static_cast<uint>(fullSizeY);
        uint *bufferY = FUN_009c8e80(-static_cast<int>(sizeY)); // negative size? maybe allocation with alignment or special pool
        *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x9C) = bufferY; // store at +0x9C

        // Allocate second buffer: size = capacityX * 0x1c (28 bytes per element)
        unsigned long long fullSizeX = static_cast<unsigned long long>(*pCapacityX) * 0x1c;
        uint sizeX = (static_cast<int>(fullSizeX >> 32) != 0) ? 0xFFFFFFFF : static_cast<uint>(fullSizeX);
        uint *bufferX = FUN_009c8e80(-static_cast<int>(sizeX));
        *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0xA4) = bufferX; // store at +0xA4

        // Third registration (maybe initializer for the allocated buffers)
        uint savedBufferY = *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x9C);
        // Set up local variables for third callback
        undefined4 local30 = 0;
        undefined4 local2c = 0;
        undefined1 **table3 = &PTR_LAB_00e36560;
        FUN_0049f960(FUN_0049ead0, &table3);

        // Initialize structure fields
        this->count1 = 0;         // offset +0x4
        this->count2 = 0;         // offset +0x8
        this->dataStart = reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 4); // offset +0x90: pointer to self+4
        this->currentIndex = 0;   // offset +0x94
        this->initialized = 1;    // offset +0x0: set to 1 indicating successful initialization
    }
}