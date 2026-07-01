// FUNC_NAME: SomeObject::initFromSourceWithScale
// Address: 0x00836010
// This function appears to be a constructor or initializer for an object of size at least 0x60 bytes.
// It sets a vtable pointer, then copies and scales five float fields from a source object.
// The fields at this+0x4c through this+0x5c are multiplied by scale and stored.
// The initial assignments (from globals) are immediately overwritten – likely default values in the original source.

#include <cstdint>

// Forward declaration for base class constructor called at 0x008334a0
extern void __thiscall baseConstructor(void* thisPtr);

// Global data references (likely static defaults)
extern uint32_t DAT_00e44630;
extern uint32_t DAT_00d5ef88;
extern uint32_t DAT_00d6471c;
extern uint32_t _DAT_00d5cf70;

// Vtable pointer
extern void* PTR_LAB_00d7377c;

// Reconstructed class (size at least 0x60 bytes)
struct SomeObject {
    void* vtable; // +0x00
    // ... other fields up to +0x4c
    float field_0x4c; // +0x4c (index 0x13)
    float field_0x50; // +0x50 (index 0x14)
    float field_0x54; // +0x54 (index 0x15)
    float field_0x58; // +0x58 (index 0x16)
    float field_0x5c; // +0x5c (index 0x17)
    // ... possibly more fields
};

// __thiscall convention: this is in ecx, parameters on stack
void* __thiscall SomeObject::initFromSourceWithScale(void* thisPtr, void* source, float scale) {
    SomeObject* self = (SomeObject*)thisPtr;

    // Call base class constructor (unknown purpose)
    baseConstructor(self);

    // Retrieve global default values (these will be overwritten below)
    uint32_t defaultField0x4c = DAT_00d5ef88;
    uint32_t defaultField0x58 = DAT_00e44630;
    uint32_t defaultField0x50 = DAT_00d6471c;
    uint32_t defaultField0x5c = _DAT_00d5cf70;
    uint32_t defaultField0x54 = _DAT_00d5cf70; // note: same as above due to variable reuse in decompiled

    // Set vtable
    self->vtable = &PTR_LAB_00d7377c;

    // Set fields to defaults (will be overwritten below – these are likely for a different code path)
    self->field_0x4c = *(float*)&defaultField0x4c; // stored as uint32_t reinterpreted as float
    self->field_0x58 = *(float*)&defaultField0x58;
    self->field_0x50 = *(float*)&defaultField0x50;
    self->field_0x54 = *(float*)&defaultField0x54;
    self->field_0x5c = *(float*)&defaultField0x5c;

    // Now scale and copy from source
    self->field_0x4c = *(float*)((uint8_t*)source + 0x4c) * scale;
    self->field_0x50 = *(float*)((uint8_t*)source + 0x50) * scale;
    self->field_0x54 = *(float*)((uint8_t*)source + 0x54) * scale;
    self->field_0x58 = *(float*)((uint8_t*)source + 0x58) * scale;
    self->field_0x5c = *(float*)((uint8_t*)source + 0x5c) * scale;

    return self;
}