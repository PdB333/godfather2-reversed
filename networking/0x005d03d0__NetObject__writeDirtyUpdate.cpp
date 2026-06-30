// FUNC_NAME: NetObject::writeDirtyUpdate
// Function address: 0x005d03d0
// Role: When a high-priority dirty flag (bits 28-31) is set at offset +0x04 of the object's vtable/header,
// this method begins an update block and packs update data into a 76-byte buffer for network replication.

// Note: This is a __thiscall member function of a network-replicable class (likely NetObject from EARS/TNL).
// The two parameters are passed to the pack routine; typical usage would be an update ID and flags.

#include <cstdint>

// Forward declaration of external functions (not defined here)
void beginUpdateBlock(); // Global function at 0x00417560
void packUpdateBuffer(void* obj, void* buffer, uint32_t updateId, uint32_t updateFlags); // Member function at 0x005cf9a0

void NetObject::writeDirtyUpdate(uint32_t updateId, uint32_t updateFlags)
{
    // +0x04 from the object's first vtable entry holds flags (likely object state bits).
    // Check if the high-priority dirty flag (0x0F000000) is set.
    uint32_t* vtable = *(uint32_t**)this;
    if ((vtable[1] & 0x0F000000) != 0)
    {
        // Start the update block (prepares some global state for the update).
        beginUpdateBlock();

        // Local buffer for packed update data (76 bytes). This buffer is filled by packUpdateBuffer.
        uint8_t updateBuffer[76];

        // Pack the object's current state into the buffer using the provided update ID and flags.
        packUpdateBuffer(this, updateBuffer, updateId, updateFlags);
    }
}