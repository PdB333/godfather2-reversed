// FUNC_NAME: bufferWriteAlignedIntByte

// Function at 0x005d5210: Writes an aligned command block with type descriptor, a zero byte, then a 4-byte integer and a 1-byte value.
// Uses global buffer manager pointer gBufferManager (DAT_01206880) and static type descriptor sCommandTypeDescriptor (PTR_LAB_01126b90).
void bufferWriteAlignedIntByte(uint32_t intValue, uint8_t byteValue)
{
    BufferManager* bufMgr = gBufferManager;                          // DAT_01206880
    uint8_t** writePtrField = &bufMgr->writePtr;                     // bufMgr + 0x14

    // Write type descriptor pointer
    *(uint32_t*)*writePtrField = (uint32_t)&sCommandTypeDescriptor;  // PTR_LAB_01126b90
    *writePtrField += 4;

    // Write a zero byte (purpose unclear – possibly padding or flag)
    *(uint8_t*)*writePtrField = 0;

    // Align to next 4-byte boundary
    uint32_t aligned1 = ((uint32_t)*writePtrField + 4) & ~3;
    *writePtrField = (uint8_t*)aligned1;

    // Write the 4-byte integer
    *(uint32_t*)*writePtrField = intValue;
    *writePtrField += 4;

    // Write the 1-byte value
    *(uint8_t*)*writePtrField = byteValue;

    // Align again to 4-byte boundary
    uint32_t aligned2 = ((uint32_t)*writePtrField + 4) & ~3;
    *writePtrField = (uint8_t*)aligned2;
}