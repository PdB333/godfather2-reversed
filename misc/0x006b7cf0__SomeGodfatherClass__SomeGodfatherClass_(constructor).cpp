// FUNC_NAME: SomeGodfatherClass::SomeGodfatherClass (constructor)
// Address: 0x006b7cf0
// Initializes vtable pointers for multiple inheritance (3 vtables at +0x00, +0x3C, +0x48),
// increments a global reference count, calls a base-class constructor, and conditionally
// registers a heap-allocated object.

// Estimated object size: 0x68 (104 bytes) based on the size parameter passed to registration.
// Vtable pointers suggest derivation from at least two bases (BaseClass1 and BaseClass2)
// placed at offsets 0x3C and 0x48, while the primary vtable is at offset 0.

class SomeGodfatherClass : public BaseClass1 {
    // Primary vtable at +0x00
    // Data members from +0x04 to +0x3B
    // BaseClass1 vtable at +0x3C (inherited via offset)
    // BaseClass2 vtable at +0x48 (another base or interface)
    // ...
public:
    // Constructor with a flag (likely 'heapAllocated' on bit 0)
    static SomeGodfatherClass* __thiscall constructor(SomeGodfatherClass* this, byte flags);
};

// External functions (names are guesses based on typical EARS patterns)
extern void __stdcall incGlobalRefCount(void* counter);       // FUN_004086d0
extern void __thiscall BaseClass1::constructor(void* this);   // FUN_0046c640
extern void __stdcall registerHeapObject(void* ptr, uint size); // FUN_0043b960

SomeGodfatherClass* __thiscall SomeGodfatherClass::constructor(SomeGodfatherClass* this, byte flags)
{
    // Set primary vtable for this class
    this->vtable = &PTR_FUN_00d5e588;                     // +0x00

    // Set vtable for BaseClass1 at offset 0x3C
    *(void**)((byte*)this + 0x3C) = &PTR_LAB_00d5e578;   // +0x3C

    // Set vtable for another base (BaseClass2) at offset 0x48
    *(void**)((byte*)this + 0x48) = &PTR_LAB_00d5e574;   // +0x48

    // Increment a global reference count for this class type
    incGlobalRefCount(&DAT_0120e93c);                     // global counter

    // Call base-class constructor (likely the primary base)
    BaseClass1::constructor(this);                        // FUN_0046c640

    // If the object was heap-allocated (flag bit 0 set), register it
    // (e.g., for memory tracking or to enable later deletion)
    if (flags & 1) {
        registerHeapObject(this, sizeof(SomeGodfatherClass)); // 0x68 = 104
    }

    return this;
}