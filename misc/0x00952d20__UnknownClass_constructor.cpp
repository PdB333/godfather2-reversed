// FUNC_NAME: UnknownClass_constructor
// Address: 0x00952d20
// Role: Constructor for an object with dual vtable pointers; takes an allocation flag.

class UnknownClass : public BaseClass // BaseClass initialized via FUN_004aa680
{
public:
    UnknownClass(byte allocationFlag) {
        // Set primary vtable at offset 0x0
        *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00d8bfc8); // PTR_FUN_00d8bfc8
        // Set secondary vtable (or RTTI) at offset 0x8
        *(reinterpret_cast<void**>(this) + 2) = reinterpret_cast<void*>(0x00d8bfc4); // PTR_LAB_00d8bfc4

        // Call base class constructor
        BaseClassConstructor(); // FUN_004aa680

        // If the object was allocated via heap (bit 0 set), immediately invoke cleanup
        if (allocationFlag & 1) {
            CleanupOrFree(this); // FUN_009c8eb0 — possibly operator delete or destructor
        }
    }

    // Note: BaseClass is at unknown offset; likely no virtual inheritance.
    // The dual vtable pointers suggest multiple inheritance or a class with a secondary base.
};
```