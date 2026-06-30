// FUNC_NAME: EAString::assign
int __thiscall EAString::assign(int this, const char* src, uint length)
{
    uint capacity = *(uint*)(this + 0x18);      // +0x18: mCapacity (total buffer capacity)
    char* inlineBuf = (char*)(this + 4);        // +0x04: start of inline buffer (or pointer ptr when large)
    char* buffer = inlineBuf;
    if (capacity > 15) {                        // Large string: buffer is heap-allocated
        buffer = *(char**)inlineBuf;            // Dereference pointer to get heap address
    }

    // Check if source overlaps with current string; if so, use more careful method
    if (buffer <= (char*)src) {
        char* currentBuffer = inlineBuf;
        if (capacity > 15) {
            currentBuffer = *(char**)inlineBuf;
        }
        char* endOfString = (char*)(*(int*)(this + 0x14) + (int)currentBuffer); // mSize + actual buffer start
        if ((char*)src < endOfString) {
            // Source lies within the current string data, so we must handle overlap
            int offset = (int)src - (int)inlineBuf;  // Offset from the inline address (might differ for heap)
            return internalAssignOverlap(this, offset, length); // FUN_0043eeb0
        }
    }

    // Error condition: -1 length indicates invalid operation
    if (length == 0xFFFFFFFF) {
        errorHandler(); // FUN_00b9654f - probably assert or crash
    }

    // Resize if needed
    if (capacity < length) {
        reserve(length, *(undefined4*)(this + 0x14)); // FUN_0043f830: reallocate to new capacity
    }
    else if (length == 0) {
        *(int*)(this + 0x14) = 0;       // mSize = 0
        char* buf = inlineBuf;
        if (capacity > 15) {
            buf = *(char**)inlineBuf;
        }
        *buf = 0;                        // Null-terminate
        return this;
    }

    // Normal copy
    if (length != 0) {
        char* dest = inlineBuf;
        if (capacity > 15) {
            dest = *(char**)inlineBuf;
        }
        memcpy_s(dest, capacity, src, length);  // _memcpy_s
        *(int*)(this + 0x14) = length;           // mSize = length
        char* terminator = inlineBuf;
        if (capacity > 15) {
            terminator = *(char**)inlineBuf;
        }
        terminator[length] = 0;                  // Null-terminate
    }

    return this;
}