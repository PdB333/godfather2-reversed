// FUNC_NAME: InputBuffer::setSlotValue
void __thiscall InputBuffer::setSlotValue(uint8_t index, uint8_t value) {
    // Guard index: +0x53D (current processing slot that must not be overwritten)
    if (index < 16 && index != this->currentGuardIndex) {
        // Slot array at +0x52D
        this->slots[index] = value;
    }
}