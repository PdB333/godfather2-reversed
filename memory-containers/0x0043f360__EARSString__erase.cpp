// FUNC_NAME: EARSString::erase
int __thiscall EARSString::erase(uint offset, uint count)
{
    // param_1 = this (EARSString*)
    // offsets: +0x04 -> pointer to data (or inline if capacity<=15)
    // +0x14 -> length (uint)
    // +0x18 -> capacity (uint)

    uint length = *(uint*)(this + 0x14);
    uint capacity = *(uint*)(this + 0x18);

    // Validate offset
    if (length < offset) {
        // Possibly an assertion or error handler
        FUN_00b965e0();
    }

    uint remaining = length - offset;
    if (remaining < count) {
        count = remaining; // clamp count to what's available
    }

    if (count != 0) {
        // Determine actual data pointer (inline or heap)
        char* data;
        if (capacity > 15) {
            data = *(char**)(this + 4); // heap allocated
        } else {
            data = (char*)(this + 4);   // inline buffer
        }

        // Move the tail of the string left by count
        _memmove_s(
            data + offset,                     // destination
            capacity - offset,                 // destination size
            data + offset + count,             // source
            remaining - count                  // number of bytes to move
        );

        // Update length
        length -= count;
        *(uint*)(this + 0x14) = length;

        // Determine the end of string for null termination
        char* endPtr;
        if (capacity > 15) {
            endPtr = *(char**)(this + 4);
        } else {
            endPtr = (char*)(this + 4);
        }
        endPtr[length] = '\0';
    }

    return (int)this;
}