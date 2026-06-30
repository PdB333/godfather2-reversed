// FUNC_NAME: EStringBuffer::EStringBuffer
// Constructor for a small string/buffer class with internal storage (capacity 15) and optional dynamic allocation.
// Reinitializes the object; if the old capacity was > 15, the external buffer is freed.
// param_2: bit 0 set indicates 'delete this' after construction (used for heap-allocated objects)
undefined4 * __thiscall EStringBuffer::EStringBuffer(undefined4 *this, byte flags)
{
    // Set base class vtable
    this[0] = &PTR_FUN_00da9810;

    // If the existing capacity exceeds the internal limit (15), free the external data buffer (+0x0C)
    if ((uint)this[8] > 15) {
        operator delete(this[3]);  // +0x0C: data pointer
    }

    // Reset to internal buffer mode: capacity = 15, length = 0
    this[8] = 15;              // +0x20: maximum capacity
    this[7] = 0;               // +0x1C: current length
    *(char*)(this + 3) = 0;    // +0x0C: set first byte of the (now internal) buffer to null terminator

    // Set derived class vtable (overrides base)
    this[0] = &PTR_LAB_00e31044;

    // If the 'delete' flag is set, free the object itself
    if ((flags & 1) != 0) {
        operator delete(this);
    }

    return this;
}