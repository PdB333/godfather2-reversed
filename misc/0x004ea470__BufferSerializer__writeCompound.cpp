// FUNC_NAME: BufferSerializer::writeCompound
void __thiscall BufferSerializer::writeCompound(uint32_t commandId, bool flag, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
    // Dereference 'this' to get the underlying buffer pointer
    uint8_t* buffer = *(uint8_t**)this;

    // The current write position is stored at offset +0x14 within the buffer structure
    uint32_t** currentPosPtr = (uint32_t**)(buffer + 0x14); // pointer to current write pointer
    uint32_t* currentPos = *currentPosPtr;               // actual position in buffer

    // Write the static label (e.g., "COMPound" identifier)
    *currentPos = (uint32_t)&PTR_LAB_01124bf8;
    currentPos++;

    // Write the command ID
    *currentPos = commandId;
    currentPos++;

    // Write the boolean flag (stored as a byte, but alignment to 4-byte boundary)
    *(bool*)currentPos = flag;
    // Align to next 4-byte boundary after the bool
    currentPos = (uint32_t*)((uint32_t)(currentPos + 1) & 0xFFFFFFFC);

    // Write the remaining 4 arguments
    *currentPos = arg1;
    currentPos++;
    *currentPos = arg2;
    currentPos++;
    *currentPos = arg3;
    currentPos++;
    *currentPos = arg4;
    currentPos++;

    // Update the stored write position in the buffer structure
    *currentPosPtr = currentPos;
}