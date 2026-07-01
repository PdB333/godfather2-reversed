// FUNC_NAME: SomeClass::getFiveUint32
// Address: 0x00826510
// Role: Copies 5 consecutive 32-bit values from offsets 0x5c-0x6c of the object into an output array.

void SomeClass::getFiveUint32(uint32_t* outArray) {
    // Copy five uint32 values from the object's internal data (offsets 0x5c, 0x60, 0x64, 0x68, 0x6c)
    // These likely represent a small struct (e.g., 5-element vector, color, or bounds data)
    outArray[0] = *(uint32_t*)((uint8_t*)this + 0x5c);
    outArray[1] = *(uint32_t*)((uint8_t*)this + 0x60);
    outArray[2] = *(uint32_t*)((uint8_t*)this + 0x64);
    outArray[3] = *(uint32_t*)((uint8_t*)this + 0x68);
    outArray[4] = *(uint32_t*)((uint8_t*)this + 0x6c);
}