// FUNC_NAME: UnknownObject::constructor
// Function at 0x0074a840 - Constructor for an object with two-level vtable (base and derived). Initializes fields including random float and two large constants.

#include <cstdlib>

// Forward declaration of base class constructor
void* __thiscall BaseConstructor(void* this, int arg1, int arg2); // FUN_0073e160
void DebugMarker(int markerId); // FUN_007f63e0, marker 0x46

// Assuming the object is some game entity with a vtable pointer at offset 0
class UnknownObject {
public:
    // Vtable pointers (first base, then derived)
    void** vtableBase;  // Initially set to PTR_LAB_00d643d0 at offset 0x00
    void** vtableDerived; // Later set to PTR_LAB_00d644d4 at offset 0x00 (overwrites)

    // Field at offset +0x1c (0x70 bytes from start)
    int field_0x1c; // =0

    // Field at offset +0x20 (0x80 bytes) - random float
    float randomFloat; // rand() * constant1 * constant2 + constant3

    // Fields at offsets 0x21-0x23 (0x84, 0x88, 0x8C)
    int field_0x21; // =0
    int field_0x22; // =0
    int field_0x23; // =0

    // Field at offset 0x27 (0x9C)
    int field_0x27; // =0

    // Fields at offsets 0x2c-0x2f (0xB0, 0xB4, 0xB8, 0xBC)
    int field_0x2c; // =0
    int field_0x2d; // =0
    int field_0x2e; // =0
    int field_0x2f; // =0

    // Fields at offsets 0x30-0x31 (0xC0, 0xC4) - two large constants (likely floats or ints)
    int field_0x30; // =0x4d4ea149
    int field_0x31; // =0x3abf2750
};

// This is the constructor
UnknownObject* __thiscall Constructor(UnknownObject* this, int arg2, int arg3)
{
    // Call base class constructor
    BaseConstructor((void*)this, arg2, arg3);

    // Set base vtable pointer
    this->vtableBase = (void**)0x00d643d0; // PTR_LAB_00d643d0

    // Initialize field at offset 0x1c (0x70) to 0
    this->field_0x1c = 0;

    // Compute random float: rand() * globalConstant1 * globalConstant2 + globalConstant3
    int randValue = _rand();
    // Constants: DAT_00e44590 (global), DAT_00d5c454 (global), _DAT_00d643cc (overlapping global)
    this->randomFloat = (float)randValue * *(float*)0x00e44590 * *(float*)0x00d5c454 + *(float*)0x00d643cc;

    // Set derived vtable pointer (overwrites base)
    this->vtableBase = (void**)0x00d644d4; // PTR_LAB_00d644d4

    // Initialize multiple fields to zero
    this->field_0x21 = 0; // offset 0x84
    this->field_0x22 = 0; // offset 0x88
    this->field_0x23 = 0; // offset 0x8C
    this->field_0x27 = 0; // offset 0x9C
    this->field_0x2c = 0; // offset 0xB0
    this->field_0x2d = 0; // offset 0xB4
    this->field_0x2e = 0; // offset 0xB8
    this->field_0x2f = 0; // offset 0xBC

    // Set two large constants (possibly float values or bit fields)
    this->field_0x30 = 0x4d4ea149; // offset 0xC0
    this->field_0x31 = 0x3abf2750; // offset 0xC4

    // Call debug/profile marker (marker ID 0x46)
    DebugMarker(0x46);

    return this;
}