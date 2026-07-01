// FUN_008e7400: SomeClass::constructorWithFlags
// Reconstructed from Ghidra decompilation.
// This function appears to be a constructor or initializer that optionally calls a cleanup function.
// param_2: bit0 indicates whether to call a deallocation (size 0xB0) after base initialization.

uint32_t __thiscall SomeClass::constructorWithFlags(uint8_t param_2) {
    // Call base constructor or initializer (likely at 0x008E7340)
    this->baseInitialize();

    // If bit 0 of param_2 is set, perform a deallocation of size 0xB0
    if (param_2 & 1) {
        // FUN_0043b960 is likely operator delete or a custom deallocator for size 0xB0
        // This may be a "cleanup on construction failure" pattern or an explicit destruction step.
        operatorDelete(this, 0xB0); // 0xB0 = 176 bytes
    }

    // Return this pointer (common for constructor chaining or allocation results)
    return reinterpret_cast<uint32_t>(this);
}