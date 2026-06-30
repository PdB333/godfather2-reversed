// FUNC_NAME: NetSession::allocateMessageEvent
void __fastcall NetSession::allocateMessageEvent(uint32_t* headerData, uint64_t* payloadData)
{
    // Stack buffer to combine header (64 bytes) and payload (96 bytes) into 0xA0 byte block
    uint8_t combined[0xA0]; // total 160 bytes

    // Copy header data (16 uint32 = 64 bytes) from param_1
    for (int i = 0; i < 16; i++)
    {
        ((uint32_t*)combined)[i] = headerData[i];
    }

    // Copy payload data (12 uint64 = 96 bytes) from in_EAX
    for (int i = 0; i < 12; i++)
    {
        ((uint64_t*)(combined + 0x40))[i] = payloadData[i];
    }

    // Allocate from arena at DAT_01206880 + 0x14 (global memory pool pointer)
    int* allocPtr = *(int**)(DAT_01206880 + 0x14); // pointer to next free block

    // Set vtable at start of allocated block
    *allocPtr = (int)&PTR_LAB_01126d48;
    allocPtr++; // skip vtable slot (4 bytes)

    // Align to 16 bytes (round up)
    void* dst = (void*)((uintptr_t)(allocPtr) + 0x0F & ~0x0F);

    // Update global allocator pointer to after this allocation
    *(int**)(DAT_01206880 + 0x14) = (int*)((uintptr_t)dst + 0xA0);

    // Copy combined data into allocated block
    memcpy(dst, combined, 0xA0);
}