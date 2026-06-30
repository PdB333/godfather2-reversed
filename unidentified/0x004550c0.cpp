// FUN_004550c0: SmallObjectArray::allocateSlot
void* SmallObjectArray::allocateSlot(void)
{
    int currentCapacity = this->capacity;
    if (this->count == currentCapacity) {
        if (currentCapacity == 0) {
            currentCapacity = 1;
        } else {
            currentCapacity *= 2;
        }
        this->resize(currentCapacity); // FUN_00455570
    }
    uint8_t* slotAddress = this->buffer + (this->count * 16); // each slot is 16 bytes
    if (slotAddress != nullptr) {
        *(uint32_t*)(slotAddress + 4) = 0xFE16702F; // likely a vtable or type marker
        *(uint32_t*)(slotAddress + 8) = 0;           // some field initialization
    }
    int oldCount = this->count;
    this->count = oldCount + 1;
    return this->buffer + (oldCount * 16);
}