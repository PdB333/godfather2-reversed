// FUNC_NAME: SlotManager::initializeBuffers
// Function at 0x004bb870: Allocates 7 buffers of 0x20 bytes and stores pointers into a struct.
// The struct is likely a slot manager containing an array of 7 ghost/packet slot buffers.
// Each buffer is 32 bytes (0x20), matching the 32-slot window size in EARS network layer.

void SlotManager::initializeBuffers(SlotManager* this, SlotManagerInitData* outData)
// param_1 is unused (this?), param_2 is output struct pointer
// The function allocates 7 buffers via an allocator (FUN_0064b9e0) and stores them at offsets +4..+0x1c
{
    int* bufferPtr; // = param_2 cast to int*
    int temp;       // used as temporary for allocation result

    // First allocation: store at offset +4
    temp = Alloc(0x20);                     // FUN_0064b9e0(0x20, &temp)
    bufferPtr = param_2;                    // iVar1 = param_2
    *(undefined4*)(param_2 + 4) = temp;     // *(int*)(iVar1 + 4) = local_4

    // Subsequent allocations reuse the second argument slot
    Alloc(0x20, &param_2);                  // FUN_0064b9e0(0x20, &param_2) overwrites param_2
    *(int*)(bufferPtr + 0x8) = param_2;    // offset +8

    Alloc(0x20, &param_2);
    *(int*)(bufferPtr + 0xC) = param_2;    // offset +0xC

    Alloc(0x20, &param_2);
    *(int*)(bufferPtr + 0x10) = param_2;   // offset +0x10

    Alloc(0x20, &param_2);
    *(int*)(bufferPtr + 0x14) = param_2;   // offset +0x14

    Alloc(0x20, &param_2);
    *(int*)(bufferPtr + 0x18) = param_2;   // offset +0x18

    Alloc(0x20, &param_2);
    *(int*)(bufferPtr + 0x1C) = param_2;   // offset +0x1C
}

// FUN_0064b9e0 is presumably a memory allocation function (EA allocator).
// Inline allocation helper:
// void Alloc(size_t size, void** outPtr) { *outPtr = malloc(size); }  // simplified