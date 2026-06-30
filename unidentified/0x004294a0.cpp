// FUN_004294a0: CommandBuffer::pushCommand
#include <cstdint>

// Global buffer descriptor (likely a larger struct, only relevant part shown)
struct CommandBufferState {
    uint8_t pad0[0x14];         // padding up to the current write pointer
    uint32_t* currentWritePtr;  // +0x14, pointer to next free slot
};

// The global buffer instance (DAT_01206880)
extern CommandBufferState* g_commandBuffer;

// Static label table (vtable or command type identifier)
extern void* PTR_LAB_0110b7e8;

// Write a command into the buffer:
// - objectId: entity/resource identifier (0 = no object, other values offset by 0x54)
// - data: auxiliary parameter (e.g., attribute value or event ID)
void CommandBuffer::pushCommand(int objectId, uint32 data)
{
    // Retrieve the current write pointer from the global buffer
    uint32_t* writePtr = g_commandBuffer->currentWritePtr;

    // Step 1: Write a pointer to the static command type identifier
    *(void**)writePtr = &PTR_LAB_0110b7e8;  // command vtable/type marker
    writePtr++;

    // Step 2: Write the object ID (0 stays 0, otherwise add base offset 0x54)
    int adjustedId = (objectId == 0) ? 0 : (objectId + 0x54);
    *(int*)writePtr = adjustedId;
    writePtr++;

    // Step 3: Write the data parameter
    *(uint32_t*)writePtr = data;
    writePtr++;

    // Step 4: Write a command termination/type byte (value 1)
    *(uint8_t*)writePtr = 1;
    // Advance pointer by 1 byte (then align to 4 bytes)
    uintptr_t ptr = (uintptr_t)writePtr + 1;
    ptr = (ptr + 3) & ~3;  // align up to DWORD boundary
    writePtr = (uint32_t*)ptr;

    // Update the global buffer's current write pointer
    g_commandBuffer->currentWritePtr = writePtr;
}