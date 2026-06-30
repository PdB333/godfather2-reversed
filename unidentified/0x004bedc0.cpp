// FUN_004bedc0: GameListener::GameListener

// Constructor for GameListener class. Initializes vtable pointers, zeroes member fields,
// registers a search ID string via helper, and stores 'this' in a global singleton pointer (DAT_012234e4).
// The constructor first sets up a base vtable (likely from a parent or interface), then later overrides
// to the final vtable for this class. This pattern is typical for object initialization in the EARS engine.

// Structure offsets (relative to this):
// +0x00: vtable pointer (first vtable, later reassigned to final vtable)
// +0x04: secondary vtable pointer (modified twice)
// +0x08: uint32 field (0 initially)
// +0x0C: uint32 field (0 initially)
// +0x20: byte field (set to 0)
// +0x24: uint32 field (set to 0)

__thiscall GameListener::GameListener() {
    // Set first vtable pointer (temporary base vtable)
    this->vtable = &PTR_FUN_00e3a8d8;
    // Set secondary vtable pointer (base interface)
    this->vtable2 = &PTR_LAB_00e3a924;
    // Store this pointer in global singleton
    DAT_012234e4 = this;
    // Zero out fields at offset +0x08 and +0x0C
    this->field08 = 0;
    this->field0C = 0;
    // Call helper function with a string identifier (likely for debug/listener registration)
    FUN_004d3bc0("GameListener Search ID");
    // Zero out byte at offset +0x20 and uint32 at +0x24
    *(byte*)((uint32_t)this + 0x20) = 0;
    *(uint32_t*)((uint32_t)this + 0x24) = 0;
    // Reassign vtable pointers to final values (derived class or final vtable)
    this->vtable = &PTR_FUN_00e35d30;
    this->vtable2 = &PTR_LAB_00e35d78;
    return this;
}