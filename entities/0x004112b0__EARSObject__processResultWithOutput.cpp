// FUNC_NAME: EARSObject::processResultWithOutput
uint EARSObject::processResult(void) {
    // This pointer in EAX (ECX in standard __thiscall)
    // +0x4ec: table of function pointer arrays (size 4 each, indexed by byte at +0x564)
    // +0x564: index byte into that table
    uint8_t index = *(uint8_t *)(this + 0x564);
    void **tableEntry = *(void ***)(this + 0x4ec + index * 4);  // pointer to an object with vtable
    // Vtable offset 0x1c: method that takes a buffer and returns a status/value
    uint32_t (*vfunc)(uint8_t *buffer) = (uint32_t (*)(uint8_t *))((*(void ***)tableEntry)[0x1c / 4]);

    uint8_t buffer[8]; // large enough: first 2 dwords (or more) used
    uint32_t result = vfunc(buffer);

    uint8_t firstByte = (uint8_t)result; // low byte of returned value from vfunc
    if (firstByte == 0) {
        // Return the rest of the dword with low byte cleared
        return result & 0xFFFFFF00; // upper 24 bits (error code?)
    }

    // The vfunc wrote into buffer; second dword at buffer+4
    uint32_t secondDword = *(uint32_t *)(buffer + 4);
    uint8_t secondByteLow = (uint8_t)secondDword;
    if (secondByteLow != 0x01 && secondByteLow != 0x03) {
        // Invalid type: set output to 0xFF
        // Return 1 with high byte = 0xFF
        return 0x00000001 | (0xFF << 8);
    } else {
        // Valid type: extract second byte of second dword as output
        uint8_t outputValue = (uint8_t)(secondDword >> 8);
        // Return 1 with high byte = outputValue
        return 0x00000001 | (outputValue << 8);
    }
}