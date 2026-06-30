// FUNC_NAME: MemoryStream::writeVTableMessage
void __thiscall MemoryStream::writeVTableMessage(int** streamHandle, uint32_t typeId, uint32_t data0, uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t valueLow, uint32_t valueHigh)
{
    // streamHandle points to a pointer to the actual MemoryStream object.
    // The object has a current write pointer at offset +0x14.
    MemoryStream* stream = (MemoryStream*)*streamHandle;
    char* writePtr = *(char**)((char*)stream + 0x14); // current buffer position

    // Write vtable pointer (class descriptor) at the buffer start
    *(uint32_t*)writePtr = (uint32_t)&PTR_FUN_01124a90; // vtable for the message type
    writePtr += 4; // advance past vtable

    // Write the type identifier (or size) as a 4-byte value
    *(uint32_t*)writePtr = typeId;
    writePtr += 4;

    // Align the pointer to the next 4-byte boundary for the 28-byte data block
    writePtr = (char*)((uint32_t)(writePtr + 7) & 0xFFFFFFFC);
    *(char**)((char*)stream + 0x14) = writePtr; // update pointer in stream

    // Copy 28 bytes from the 7 data parameters into the buffer
    uint32_t dataBlock[7];
    dataBlock[0] = data0;
    dataBlock[1] = data1;
    dataBlock[2] = data2;
    dataBlock[3] = data3;
    dataBlock[4] = data4;
    dataBlock[5] = data5;
    dataBlock[6] = data6;
    memcpy(writePtr, dataBlock, 0x1c); // 28 bytes
    writePtr += 0x1c; // advance past the copied block

    // Align pointer for the final 8-byte value (offset +0x1f to round up)
    writePtr = (char*)((uint32_t)(writePtr + 0x1f) & 0xFFFFFFFC);
    *(char**)((char*)stream + 0x14) = writePtr;

    // Write an 8-byte value (e.g., a 64-bit timestamp or identifier)
    *(uint64_t*)writePtr = ((uint64_t)valueHigh << 32) | valueLow;
    writePtr += 8;

    // Update the stream’s current write pointer
    *(char**)((char*)stream + 0x14) = writePtr;
}