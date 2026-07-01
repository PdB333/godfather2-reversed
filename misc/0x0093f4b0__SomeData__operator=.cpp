// FUNC_NAME: SomeData::operator=
// 0x0093f4b0 - Copy assignment operator for a data structure with two 16-byte sub-objects
undefined4 * __thiscall SomeData::operator=(undefined4 *this, undefined4 *source)
{
    // Zero out the destination fields that will be overwritten by sub-object copies
    this[1] = 0; // +0x04
    this[2] = 0; // +0x08
    this[3] = 0; // +0x0C
    this[4] = 0; // +0x10
    this[6] = 0; // +0x18
    this[7] = 0; // +0x1C
    this[8] = 0; // +0x20
    this[9] = 0; // +0x24

    // Copy primary field (first 4 bytes)
    *this = *source; // +0x00

    // Copy first sub-object (16 bytes at offset 0x04)
    // FUN_004d3e20 likely handles deep copy of the sub-object from source to this
    FUN_004d3e20(source + 1); // +0x04 in source

    // Copy scalar field at offset 0x14
    this[5] = source[5]; // +0x14

    // Copy second sub-object (16 bytes at offset 0x18)
    FUN_004d3e20(source + 6); // +0x18 in source

    // Copy remaining fields at offsets 0x28, 0x2C, 0x30
    this[10] = source[10]; // +0x28
    this[11] = source[11]; // +0x2C
    this[12] = source[12]; // +0x30

    return this;
}