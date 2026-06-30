// FUNC_NAME: PoolAllocator::allocateSlot
undefined4 PoolAllocator::allocateSlot(void)
{
    uint *flagsArray;
    uint index;
    uint *currentSlot;
    
    if (this->count < 0x90) {
        index = 0;
        flagsArray = this + 0x122a8;  // +0x122a8: array of 0x90 slot status words (uint32 each)
        do {
            if ((*flagsArray & 1) == 0) {
                // Found a free slot; allocate it.
                this->currentSlot = (PoolAllocator *)((uint8_t *)this + (index + 0x2455) * 8);
                // Clear the slot's data fields (offsets relative to slot start)
                *(undefined4 *)(this->currentSlot + 4) = 0;    // +4: field2
                *(undefined4 *)((uint8_t *)this->currentSlot + 8) = 0;   // +8: field3
                *(undefined4 *)((uint8_t *)this->currentSlot + 0xc) = 0;  // +0xc: field4
                *(undefined4 *)((uint8_t *)this->currentSlot + 0x14) = 0; // +0x14: field5
                *(undefined4 *)((uint8_t *)this->currentSlot + 0x18) = 0; // +0x18: field6
                return 1;
            }
            index++;
            flagsArray += 8;  // each slot is 32 bytes (8 uint32)
        } while (index < 0x90);
    }
    return 0;
}