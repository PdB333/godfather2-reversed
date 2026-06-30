// FUNC_NAME: EARS::String::getData
// Address: 0x00571d70
// Returns pointer to string data (internal buffer or heap allocated)
// Offsets:
//   0x00: int length? (might be used elsewhere)
//   0x2c: int flags (bit 0x20 indicates heap allocated)
//   0x30: char* dataPointer (external buffer)
//   0x1c: char internalBuffer[?]

int* __thiscall String::getData(void) {
    // Check if heap allocated and length > 2, return external pointer
    if (((this->flags & 0x20U) != 0) && (2 < this->length)) {
        return (int*)this->dataPointer;   // External data
    }

    // Another case for heap allocated with length == 2? Unclear.
    if (((this->flags & 0x20U) != 0) && (this->length == 2)) {
        return (int*)(this + 0xc);         // Might be address of pointer field
    }

    // Default: return internal buffer at offset 0x1c
    return (int*)((char*)this + 0x1c);
}