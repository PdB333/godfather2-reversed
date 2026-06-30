// FUNC_NAME: SomeClass::SomeClass
// Reconstructed from 0x0071e800 (constructor pattern)
// Calls base initialization, then conditionally invokes extra setup if bit 0 of flag is set.
SomeClass::SomeClass(byte flag) {
    // Likely base class constructor or internal field initialization
    this->internalInit(); // FUN_0071e450

    // If flag bit 0 is set, perform additional initialization (e.g., allocate resource)
    if (flag & 1) {
        this->extraInit(); // FUN_009c8eb0
    }
    // Constructor returns 'this' implicitly at machine level
}