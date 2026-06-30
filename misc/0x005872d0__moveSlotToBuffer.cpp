// FUNC_NAME: moveSlotToBuffer
// Address: 0x005872d0
// Role: Moves slot data from this object (the source) to a provided buffer, or clears the buffer, based on flags bits 3-5.
// Field offsets: this+0x00: slotData[0], this+0x04: slotData[1], this+0x08: slotData[2], this+0x0C: slotData[3]

#include <cstdint>

// Global sentinel value for an invalid/released slot
static const uint32_t ms_invalidSlotValue = *(uint32_t*)0x00e2b1a4;

// Assuming __thiscall with this pointer passed in ESI
void SlotManager::moveSlotToBuffer(uint32_t* outBuffer, uint32_t flags) {
    // Mask for bits 3-5
    uint32_t slotFlags = flags & 0x38;

    if (slotFlags == 0) {
        // Clear the destination buffer to "empty" state
        outBuffer[0] = 0;
        outBuffer[1] = 0;
        outBuffer[2] = 0;
        outBuffer[3] = ms_invalidSlotValue;
        return;
    }

    if (slotFlags == 0x38) {
        // Move data from this object into outBuffer, then release this object's slot
        outBuffer[0] = this->slotData[0];   // +0x00
        outBuffer[1] = this->slotData[1];   // +0x04
        outBuffer[2] = this->slotData[2];   // +0x08
        outBuffer[3] = this->slotData[3];   // +0x0C
        this->slotData[0] = 0;
        this->slotData[1] = 0;
        this->slotData[2] = 0;
        this->slotData[3] = ms_invalidSlotValue;
        return;
    }

    // Invalid flags – should not happen; handle error/assert
    FUN_0056d810();                          // Assert or debug break
    FUN_0056d370(0, 0, 0, outBuffer);       // Log error with buffer info
    FUN_0056d370(0, 0, 0);                  // Log general error
}