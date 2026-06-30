// FUNC_NAME: getObjectFlagBit
// Function at 0x005e69b0: Retrieves a specific flag (bit 6) from an object's status word at offset 0x28.
// Uses a lookup function with an ID and output buffers. Returns 0 if lookup fails or returns error code -32 (0xffffffe0).

uint __fastcall getObjectFlagBit(uint param_1, int objectId)
{
    uint objPtr;
    byte singleByteOutput;
    int fourByteOutput[1]; // 4-byte buffer

    objPtr = lookupObject(objectId, &singleByteOutput, fourByteOutput);
    if ((objPtr != 0) && (objPtr != 0xffffffe0)) {
        // Read flags from object at offset 0x28, shift right 6, mask to keep bit0 and upper bits (possibly bug: intended to isolate bit6? mask 0xffffff01 is unusual)
        return *(uint *)(objPtr + 0x28) >> 6 & 0xffffff01;
    }
    // On failure, return masked object pointer (low byte cleared)
    return objPtr & 0xffffff00;
}