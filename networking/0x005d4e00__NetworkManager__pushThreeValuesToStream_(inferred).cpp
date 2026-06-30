// FUNC_NAME: NetworkManager::pushThreeValuesToStream (inferred)
// Address: 0x005d4e00
// Role: Writes a 4-byte header (vtable/type) followed by three 4-byte values into a serialization buffer.
// The buffer pointer is stored in a global structure at +0x14.

// Assume global structure: g_networkStream (DAT_01206880)
// struct StreamBuffer {
//     char pad[0x14]; // +0x14: current write pointer
// };
// Other offsets unknown.

// The constant PTR_LAB_01126b18 is likely a vtable or type identifier for the data being pushed.

void __fastcall NetworkManager::pushThreeValuesToStream(void* unused_ecx, uint32_t value1, uint32_t value2, uint32_t value3)
{
    // Global pointer to stream control block
    StreamBuffer* streamCtrl = (StreamBuffer*)DAT_01206880;

    // Write 4-byte header (pointer to vtable/type constant) at current position
    *(uint32_t**)streamCtrl->currentWritePtr = &HEADER_TYPE_CONSTANT; // PTR_LAB_01126b18
    // Advance write pointer by 4
    streamCtrl->currentWritePtr = (uint32_t*)((uint8_t*)streamCtrl->currentWritePtr + 4);

    // Align to 4 bytes (already aligned after increment, but code does explicit alignment)
    uint32_t* alignedPtr = (uint32_t*)(((uint32_t)streamCtrl->currentWritePtr + 3) & 0xFFFFFFFC);
    streamCtrl->currentWritePtr = alignedPtr;
    *alignedPtr = value1;

    // Write value2 at next aligned offset (effective +4)
    alignedPtr = (uint32_t*)(((uint32_t)streamCtrl->currentWritePtr + 7) & 0xFFFFFFFC);
    streamCtrl->currentWritePtr = alignedPtr;
    *alignedPtr = value2;

    // Write value3 at next aligned offset
    alignedPtr = (uint32_t*)(((uint32_t)streamCtrl->currentWritePtr + 7) & 0xFFFFFFFC);
    streamCtrl->currentWritePtr = alignedPtr;
    *alignedPtr = value3;

    // Final advance by 4 (padding or to make room for next element)
    streamCtrl->currentWritePtr = (uint32_t*)((uint8_t*)streamCtrl->currentWritePtr + 4);
}