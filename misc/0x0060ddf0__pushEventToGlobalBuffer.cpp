// FUNC_NAME: pushEventToGlobalBuffer
void pushEventToGlobalBuffer(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6)
{
    // Global index into an array of 24-byte structures
    int index = g_eventBufferIndex * 0x18; // +0x00 to +0x14 for 6 uint32s

    // Store the six parameters into the current slot of the global buffer
    *(uint32 *)(g_eventBuffer + index + 0x00) = param1;
    *(uint32 *)(g_eventBuffer + index + 0x04) = param2;
    *(uint32 *)(g_eventBuffer + index + 0x08) = param3;
    *(uint32 *)(g_eventBuffer + index + 0x0C) = param4; // used below
    *(uint32 *)(g_eventBuffer + index + 0x10) = param5;
    *(uint32 *)(g_eventBuffer + index + 0x14) = param6; // used below

    // Process the stored event with the 4th and 6th parameters
    processEvent(param4, param6);
}