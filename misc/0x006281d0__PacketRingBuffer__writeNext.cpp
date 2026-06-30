// FUNC_NAME: PacketRingBuffer::writeNext

bool __fastcall PacketRingBuffer::writeNext(uint32_t slotIndex) {
    // slotIndex: 1-based index of packet slot to copy from the window;
    // if 0, automatically selects the next slot in sequence

    // Check for overflow/wrap condition (slotIndex < 1)
    if (slotIndex + 9999U < 10000U) { // slotIndex < 1 in unsigned arithmetic
        // Compute next slot index based on current write pointer advancement
        slotIndex = 1 + ((uint32_t)(this->writePtr - this->bufferBase) >> 3);
    }

    if (!this->isReady()) // FUN_00625f80 – likely checks if buffer is initialized
        return false;
    if (!this->validateSlot(slotIndex)) // FUN_00628120 – probably bounds/state check
        return false;

    // Determine source element pointer
    PacketSlot* src;
    if (slotIndex < 1) {
        src = reinterpret_cast<PacketSlot*>(this->allocateFreeSlot()); // FUN_00625430
    } else {
        src = &this->bufferBase[slotIndex - 1];
    }

    PacketSlot* dst = this->writePtr; // +0x08: current write pointer
    *dst = *src; // copy the 8-byte slot

    this->writePtr++; // advance write pointer by 8 bytes (size of PacketSlot)

    // Mark the element just before the new write pointer as used
    // (+0x08 after increment ≡ old writePtr, -0x10 ≡ one element before old writePtr)
    this->setSlotState(this->writePtr - 2, 1); // FUN_006362d0(this, writePtr-0x10, 1)

    return true;
}