// FUNC_NAME: StreamWriter::writeSerializedBlock
void __thiscall StreamWriter::writeSerializedBlock(int32_t param_2, int64_t param_3, int64_t param_4, int64_t param_5, int64_t param_6, int32_t param_7, int32_t param_8, int32_t param_9) {
    // Get buffer object pointer from this (offset +0x00)
    uint8_t* bufferObj = *(uint8_t**)this;

    // Current write position pointer is at bufferObj + 0x14
    uint8_t** writePosPtr = (uint8_t**)(bufferObj + 0x14);

    // Write vtable pointer for the serialized object type
    **(uint32_t**)writePosPtr = (uint32_t)&PTR_FUN_011250f4;
    *writePosPtr += 4; // advance past vtable

    // Write 32-bit parameter (e.g. object ID or flags)
    **(uint32_t**)writePosPtr = param_2;
    *writePosPtr += 4;

    // Align current pointer to next 4-byte boundary
    uint8_t* alignedBlock = (uint8_t*)(*writePosPtr + 7) & ~3;
    *writePosPtr = alignedBlock;

    // Package 36 bytes from remaining parameters into local structure
    struct PackedData {
        int64_t d1;   // param_3
        int64_t d2;   // param_4
        int64_t d3;   // param_5
        int64_t d4;   // param_6
        int32_t d5;   // param_7
    } data = { param_3, param_4, param_5, param_6, param_7 };

    // Copy the 36-byte block to the aligned position
    memcpy(alignedBlock, &data, 0x24);
    *writePosPtr = alignedBlock + 0x24;

    // Align again
    uint8_t* alignedTail = (uint8_t*)(*writePosPtr + 7) & ~3;
    *writePosPtr = alignedTail;

    // Write last two 32-bit parameters as a single 64-bit value (param_9 high, param_8 low)
    *(uint64_t*)alignedTail = ((uint64_t)param_9 << 32) | (uint32_t)param_8;
    *writePosPtr = alignedTail + 8;
}