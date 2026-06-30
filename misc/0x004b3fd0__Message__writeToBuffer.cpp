// FUNC_NAME: Message::writeToBuffer
void __thiscall Message::writeToBuffer(int thisPtr, undefined4 param_2)
{
    // Read 64-bit field at +0x20
    uint64_t data64 = *(uint64_t*)(thisPtr + 0x20);
    // Read 32-bit field at +0x28
    uint32_t data32 = *(uint32_t*)(thisPtr + 0x28);

    // Write back (likely redundant or sign extension)
    *(uint32_t*)(thisPtr + 0x20) = *(uint32_t*)(thisPtr + 0x20); // Low 32 of data64
    *(uint32_t*)(thisPtr + 0x24) = *(uint32_t*)(thisPtr + 0x24); // High 32 of data64
    *(uint32_t*)(thisPtr + 0x28) = data32;
    *(uint32_t*)(thisPtr + 0x2c) = param_2;

    // Global buffer manager pointer +0x14 is the current write pointer
    // (likely a pointer to a growing buffer)
    int* pCurrent = *(int**)(g_bufferManager + 0x14);

    // Write a vtable/type identifier (LAB_0112458c)
    **(int**)pCurrent = (int)&PTR_LAB_0112458c; // +0x00: type info
    *pCurrent += 4;

    // Write the this pointer
    *(int*)*pCurrent = thisPtr; // +0x04: object pointer
    *pCurrent += 4;

    // Align to 16-byte boundary
    int aligned = (*pCurrent + 0x13) & 0xFFFFFFF0;
    *pCurrent = aligned;

    // Write the 64-bit data
    *(uint64_t*)aligned = data64; // +0x08: data64
    // Write the combined 32-bit data and param_2 as 64-bit (low 32 bits = data32, high = param_2)
    *(uint64_t*)(aligned + 8) = ((uint64_t)param_2 << 32) | data32; // +0x10: {param_2, data32}

    // Advance by 16 bytes
    *pCurrent += 16;
}