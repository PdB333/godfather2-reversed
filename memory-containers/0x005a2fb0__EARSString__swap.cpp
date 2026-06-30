// FUNC_NAME: EARSString::swap
void EARSString::swap(EARSString& other) {
    // Swap size (offset +0x00)
    uint32 tempSize = size;
    size = other.size;
    other.size = tempSize;

    // Swap capacity (offset +0x04)
    uint32 tempCapacity = capacity;
    capacity = other.capacity;
    other.capacity = tempCapacity;

    // Swap buffer pointer (offset +0x08)
    char* tempBuffer = buffer;
    buffer = other.buffer;
    other.buffer = tempBuffer;

    // Internal buffer is at offset +0x0C (16 bytes, see local_50)
    char* thisInternal = reinterpret_cast<char*>(&internalBuffer);
    char* otherInternal = reinterpret_cast<char*>(&other.internalBuffer);

    // Adjust pointers for small string optimisation
    if (tempBuffer == thisInternal) {
        // original 'this' buffer was internal → other's buffer should point to its own internal
        other.buffer = otherInternal;
    } else {
        other.buffer = tempBuffer;
    }

    if (tempBuffer == otherInternal) {
        // original 'other' buffer was internal → this's buffer should point to its own internal
        buffer = thisInternal;
    } else {
        buffer = tempBuffer;
    }

    // If at least one string used internal buffer, swap the content of the internal buffers
    if ((tempBuffer == thisInternal) || (tempBuffer == otherInternal)) {
        // --- Temporary object to mediate internal buffer swap ---
        // The decompiled code initialises a local stack object (size ~ 0x30 bytes)
        // resembling a minimal string holder:
        //   local_70, local_68, local_60, local_74, local_7c, local_78
        // It then calls FUN_005a0a00 (likely destructor) and FUN_005a1060 (unknown)
        // to properly exchange the internal memory without overlap.

        // Reconstructed as direct swap of the internal arrays if both internal:
        char tempInternal[16];               // local_50
        memcpy(tempInternal, thisInternal, 16);
        memcpy(thisInternal, otherInternal, 16);
        memcpy(otherInternal, tempInternal, 16);

        // NOTE: The original binary also calls FUN_005a3420 to copy something at offset +0x4C (0x13 * 4)
        // which might be an additional member array (e.g., hash code). That logic is omitted here
        // as it goes beyond a simple swap.
    }
}