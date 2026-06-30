// FUNC_NAME: SomeClass::constructorWithFlag

// 0x0053efa0: Constructor for an EARS object. Takes a flag (byte) indicating whether to call a cleanup routine after construction.
// This pattern is common in EARS engine for objects that can be allocated on heap or stack.
// The flag's bit 0 controls whether to invoke FUN_009c8eb0 (likely a deallocation or virtual table setup).

// 0x0053f0c0: Actual initialization function (base constructor or member init).
// 0x009c8eb0: Conditional cleanup function (e.g., operator delete, or finalization).

undefined4 __thiscall SomeClass::constructorWithFlag(undefined4 this, byte param_2)
{
    // Call the base initialization (likely sets up vtable, members, etc.)
    this->initialize();

    // If the lowest bit is set, perform additional cleanup/allocation handling.
    if ((param_2 & 1) != 0)
    {
        // This might be a custom deallocation or finalization step.
        // In EARS, some objects allocate a separate buffer; this call may free it.
        PerformCleanup(this);
    }

    return this;
}