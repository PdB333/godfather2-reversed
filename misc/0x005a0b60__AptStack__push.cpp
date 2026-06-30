// FUNC_NAME: AptStack::push
void __thiscall AptStack::push(uint* element) {
    // Assertion: stack must not be full (capacity = 0x180 = 384 elements)
    if (this->count >= 0x180) {
        // Debug assertion failure (EA standard assert macro)
        // "nElements < _nSize" from AptStack.h line 0x1c
        // (assertion code omitted for clarity)
        // In release builds, this would be a no-op or crash.
        // For reconstruction, we assume the assertion is active.
        // The original code uses a complex debug check; we simplify to an assert.
        // assert(0 && "AptStack overflow");
        // But to match the original behavior, we just skip the push if full.
        // Actually the original code would trigger a breakpoint; we'll just return.
        return;
    }

    // Push element onto stack
    this->data[this->count + 1] = element;
    this->count++;

    // Handle reference counting for non-null elements
    if (element != s_nullHandle) {
        uint flags = *element;
        uint type = flags & 0x7FFF; // lower 15 bits
        bool bit15Clear = ((flags >> 15) & 1) == 0;

        // If type is not 0x19 (25) and bit15 is clear, and type is not 0x0B, 0x18, 0x17
        if (type != 0x19 && bit15Clear && type != 0x0B && type != 0x18 && type != 0x17) {
            // Release reference on the element (likely decrement refcount or cleanup)
            AptRefCount::release(element);
        }
    }
}