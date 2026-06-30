// FUNC_NAME: PacketWriteBuffer::writeTypedEvent
void __thiscall PacketWriteBuffer::writeTypedEvent(
    uint32_t lowA, uint32_t highA, uint32_t lowB, uint32_t highB,
    uint32_t extraData, const void* largeData)
{
    // +0x00: pointer to internal buffer manager structure
    int* pBufferMgr = *reinterpret_cast<int**>(this);

    // Write type identifier (vtable pointer for the serialized object)
    // +0x14 in buffer manager: current write pointer
    **reinterpret_cast<void***>(pBufferMgr + 0x14) =
        reinterpret_cast<void*>(0x011251d0);
    *reinterpret_cast<int*>(pBufferMgr + 0x14) += 4;   // advance by 4

    // Align current pointer to 4 bytes for 8-byte writes
    int currentWrite = *reinterpret_cast<int*>(pBufferMgr + 0x14);
    uint64_t* aligned = reinterpret_cast<uint64_t*>((currentWrite + 3) & ~3);
    *reinterpret_cast<int*>(pBufferMgr + 0x14) = reinterpret_cast<int>(aligned);

    // Write two 64-bit values (high/low parts combined)
    aligned[0] = (static_cast<uint64_t>(highA) << 32) | lowA;
    aligned[1] = (static_cast<uint64_t>(highB) << 32) | lowB;

    // Write 4-byte value (extraData occupies low byte, high bytes indeterminate)
    *(uint32_t*)(aligned + 2) = extraData;

    // Align to 16 bytes for 64-byte block copy
    void* dst = reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(aligned) + 0x23) & ~0xF);
    *reinterpret_cast<int*>(pBufferMgr + 0x14) = reinterpret_cast<int>(dst);

    // Copy 64 bytes from input data
    memcpy(dst, largeData, 0x40);

    // Advance write pointer by 64
    *reinterpret_cast<int*>(pBufferMgr + 0x14) += 0x40;
}