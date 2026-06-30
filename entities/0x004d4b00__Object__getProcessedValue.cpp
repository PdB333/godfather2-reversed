// FUNC_NAME: Object::getProcessedValue
uint32_t Object::getProcessedValue(uint32_t param) {
    // Call internal preprocessor with the same param
    this->updateInternal(param);
    // Return raw value at offset +0x04 (likely a pointer or ID)
    return *(uint32_t*)((uint8_t*)this + 4); // +0x04 member
}