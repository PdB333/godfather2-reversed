// FUNC_NAME: PacketCommand::writeToBuffer
// Address: 0x004b40a0
// Role: Serializes this command object's state to a global packet buffer.
//        The buffer is managed by a global structure at DAT_01206880.
//        The function writes a vtable pointer, the 'this' pointer, and
//        two packed 64-bit values (combining m_field20/m_field24 and m_field2c/m_field28)
//        after 16-byte alignment padding.

#include <cstdint>

// Global packet buffer manager structure (partial)
struct PacketBufferManager {
    // ... other fields ...
    // +0x14: Current write pointer (points to where to write next)
    uint8_t* pWritePos; 
};

// The global manager instance (address 0x01206880)
extern PacketBufferManager g_packetManager;

// External vtable pointer for this command type
extern void* g_vtable_PacketCommand; // &PTR_LAB_0112458c

void __thiscall PacketCommand::writeToBuffer(
    int thisPtr,
    uint32_t param2,  // m_field20
    uint32_t param3,  // m_field24
    uint32_t param4   // m_field28
)
{
    // Read the current value at this+0x2c (used later in the 2nd 64-bit block)
    uint32_t uVar1 = *(uint32_t*)(thisPtr + 0x2c); // m_field2c

    // Store the three parameters into the object (they may already be set,
    // but this ensures they are written before serializing)
    *(uint32_t*)(thisPtr + 0x20) = param2; // m_field20
    *(uint32_t*)(thisPtr + 0x24) = param3; // m_field24
    *(uint32_t*)(thisPtr + 0x28) = param4; // m_field28

    // Get the address of the global write position variable
    // (equivalent to &g_packetManager.pWritePos)
    int* piVar2 = (int*)(&g_packetManager.pWritePos);

    // Write the vtable pointer into the buffer at the current write location
    **(void***)(&g_packetManager.pWritePos) = (void*)g_variable_PacketCommand;

    // Advance the write pointer by 4 bytes (skip vtable pointer)
    *piVar2 = *piVar2 + 4;

    // Write the 'this' pointer into the buffer after the vtable
    *(int*)*piVar2 = thisPtr;

    // Align the write pointer to the next 16-byte boundary
    // (+0x13 & ~0xF) rounds up to multiple of 16
    uint8_t* puVar3 = (uint8_t*)((*piVar2 + 0x13) & 0xFFFFFFF0);
    *piVar2 = (int)puVar3;

    // Write the first 64-bit value: param2 (low) and param3 (high)
    // (packed into a single 8-byte slot)
    *(uint64_t*)puVar3 = ((uint64_t)param3 << 32) | param2;

    // Write the second 64-bit value: uVar1 (low) and param4 (high)
    *((uint64_t*)puVar3 + 1) = ((uint64_t)param4 << 32) | uVar1;

    // Advance the write pointer by 16 bytes (two 64-bit values)
    *piVar2 = *piVar2 + 0x10;
}