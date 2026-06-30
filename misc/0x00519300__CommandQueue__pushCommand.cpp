//FUNC_NAME: CommandQueue::pushCommand
void CommandQueue::pushCommand(void* funcPtr, uint32_t data)
{
    // Global command queue instance pointer (DAT_012068e8)
    // Offset +0x14: pointer to current write position in command buffer
    int** bufferPtrPtr = (int**)(g_commandQueue + 0x14);
    int* bufferPtr = *bufferPtrPtr;

    // Write function pointer (4 bytes)
    *(void**)bufferPtr = funcPtr;
    bufferPtr += 1; // advance by 4 bytes

    // Align to next 4-byte boundary (already aligned after increment)
    uint64_t* alignedPtr = (uint64_t*)(((uint32_t)bufferPtr + 3) & ~3);
    bufferPtr = (int*)alignedPtr;

    // Write two 4-byte parameters as a single 8-byte value
    *alignedPtr = ((uint64_t)data << 32) | (uint32_t)funcPtr; // CONCAT44(param_2, param_1)
    bufferPtr += 2; // advance by 8 bytes

    // Update buffer pointer
    *bufferPtrPtr = bufferPtr;
}