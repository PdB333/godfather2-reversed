// FUNC_NAME: UnknownClass::Constructor
// Function at 0x00857aa0: Constructor for a class with dual vtable pointers (multiple inheritance).
// Called from 0x00879160. Base class constructor at 0x0055a1f0 takes one argument (param_2).
// Uses global constants: _DAT_00d5cf70, DAT_00d5d7b8, DAT_00d5f378, DAT_00d5e288.

// Note: Class name unknown; vtables: +0x00 = &PTR_LAB_00d751fc, +0x04 = &PTR_LAB_00d751e8
// +0x38 (array index 0xe) flags, +0x3C (0xf) some value, +0x40 (0x10), +0x44 (0x11), +0x48 (0x12) other values.

class UnknownClass;

Undefined4* __thiscall UnknownClass::constructor(Undefined4* thisPtr, Undefined4 baseArg)
{
    // Call base class constructor (likely a base in the multiple inheritance chain)
    FUN_0055a1f0(baseArg);  // Base constructor, takes an argument

    // Retrieve global constant
    Undefined4 uVar1 = _DAT_00d5cf70;

    // Set first vtable pointer (primary class)
    thisPtr[0] = (Undefined4*)&PTR_LAB_00d751fc;  // +0x00 vtable1

    // Set second vtable pointer (secondary base/interfaces)
    thisPtr[1] = (Undefined4*)&PTR_LAB_00d751e8;  // +0x04 vtable2

    // Initialize flags field at offset +0x38 (0xe * 4) to 0
    thisPtr[0xe] = 0;  // +0x38 flags

    // Set member values from global constants
    thisPtr[0xf] = uVar1;                  // +0x3C
    thisPtr[0x10] = DAT_00d5d7b8;          // +0x40
    thisPtr[0x11] = DAT_00d5f378;          // +0x44
    thisPtr[0x12] = DAT_00d5e288;          // +0x48

    // Set bit 0 in flags (e.g., indicating initialization)
    thisPtr[0xe] = thisPtr[0xe] | 1;

    // Return this pointer
    return thisPtr;
}