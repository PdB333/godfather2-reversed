// FUNC_NAME: GhostObject::writeUpdate
// Address: 0x0075fd60
// Role: Serializes ghost object state into a network update buffer for a specific object type (0x6862a74c).

void __thiscall GhostObject::writeUpdate(GhostObject* this, GhostUpdateBuffer* outBuffer) {
    int objectType;
    bool isClassMatch;
    uint* flagsPtr;
    ulonglong* dataBlock;

    // Virtual call on outBuffer to check object type ID
    objectType = outBuffer->vtable->getClassId(); // (**(code **)*outBuffer)()
    if (objectType == 0x6862a74c) {
        // Set bit 0 of flags at offset 0xA8
        outBuffer->flags[0x2a] |= 1; // +0xA8

        // Call sub-functions on derived state at offsets 0x50 and 0x60
        this->packStatePart1(this + 0x50); // FUN_0075cd50
        this->packStatePart2(this + 0x60); // FUN_00757ab0

        // Write six 8-byte data blocks into the buffer
        // Each block consists of a function pointer (behavior) and a data value from this+0x78
        dataBlock = (ulonglong*)(&outBuffer->data[0x1e]); // offset 0x78
        dataBlock[0] = CONCAT44(0x007347e0, *(uint*)(this + 0x78)); // behaviorFunc1 + someValue
        dataBlock[1] = CONCAT44(0x0073b090, uStack_8); // behaviorFunc2 + unknown (from stack artifact)
        dataBlock[2] = CONCAT44(0x0072f880, *(uint*)(this + 0x78)); // behaviorFunc3 + sameValue
        dataBlock[3] = CONCAT44(0x0074a150, uStack_8); // behaviorFunc4 + unknown

        // Set additional flag bits
        outBuffer->flags[0x2a] |= 0x2000000; // bit 25

        // Conditionally copy more state based on flags at this+0x88
        flagsPtr = (uint*)(this + 0x88);
        if ((*flagsPtr >> 1) & 1) {
            outBuffer->data[0x2f] = *(uint*)(this + 0x84); // copy uint at +0x84 to offset 0xBC
        }
        if ((*flagsPtr >> 2) & 1) {
            outBuffer->flags[0x2a] |= 2; // bit 1
        }
        if ((*flagsPtr & 1)) {
            outBuffer->flags[0x2a] |= 0x40; // bit 6
        }
    }
}