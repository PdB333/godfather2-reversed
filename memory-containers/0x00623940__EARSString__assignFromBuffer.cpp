// FUNC_NAME: EARSString::assignFromBuffer
// Function address: 0x00623940
// Role: Assigns a reference-counted string buffer to this string object.
// This is likely part of EA's internal string class used in EARS engine.
// Offsets: +0x0c = pointer to buffer (EARSStringBuffer*), +0x10 = reference count or index.

void EARSString::assignFromBuffer(EARSStringBuffer* buffer, EARSStringBuffer* source) {
    // Save buffer pointer for later use
    EARSStringBuffer* targetBuffer = buffer;

    // Call vtable+8 on target buffer: presumably "AddRef" or "retain"
    (buffer->vtable->retain)(buffer);

    // If source is non-null, copy its data into the buffer
    int resultCode;
    if (source == nullptr) {
        resultCode = 0;
    } else {
        resultCode = FUN_004265d0(source, targetBuffer);  // Likely "copyStringData"
    }

    // Attach the result code (or internal handle) to the buffer
    FUN_006240e0(targetBuffer, resultCode);  // E.g., "setBufferData"

    // Store the buffer pointer into this string's inner field
    this->bufferPtr = buffer;  // +0x0c

    // Call vtable+8 again? Possibly a second retain or set operation (may be redundant)
    (buffer->vtable->retain)();

    if (source != nullptr) {
        // Copy again from source using the stored buffer (maybe to update internal state)
        resultCode = FUN_004265d0(source, this->bufferPtr);
        this->sourceCode = resultCode;  // +0x10

        // Release the source (vtable+4) with a flag (0)
        (source->vtable->release)(source, 0);

        // Release the buffer (vtable+0xc) – possibly decrement ref count
        (buffer->vtable->release)();
        return;
    }

    // No source: set sourceCode to 0 and release buffer
    this->sourceCode = 0;
    (buffer->vtable->release)();
}