// FUNC_NAME: NamedEntry::NamedEntry
// Reconstructed constructor for a linked-list entry with a name and three data fields.
// Offsets: [0] vtable, [1] unknown1 (4 bytes), [2] unknown3 (4 bytes), [3] unknown2 (4 bytes),
//          [4-7] zeros (4*4=16 bytes), [8] name buffer (64 bytes), [0x1c] next pointer.
__thiscall __int32* NamedEntry::NamedEntry(__int32* this, char* nameStr, int data1, int data2, int data3)
{
    // Call base class constructor (likely initializes vtable members)
    FUN_0064cc90(); // BaseClass::BaseClass()?

    // Set vtable pointer
    *this = (int)&PTR_LAB_00d8b4b0; // vtable for NamedEntry

    // Copy up to 63 characters of the name into the buffer at offset 8
    _strncpy((char*)(this + 2), nameStr, 0x3F); // +8 bytes from this

    // Store the three data parameters
    this[1] = data1;   // +4
    this[3] = data2;   // +12? Actually offset 12, but note param order: param_3 -> this[1], param_4 -> this[3], param_5 -> this[2]
    this[2] = data3;   // +8

    // Zero out four fields (probably state flags or counters)
    this[4] = 0; // +16
    this[5] = 0; // +20
    this[6] = 0; // +24
    this[7] = 0; // +28? Wait, this[7] = +28, but next pointer is at this[0x1c] = +0x70? Let's recalc: 
    // Actually offsets: this points to int*, so index *4 = byte offset. this[0x1c] = 0x1c * 4 = 0x70 = 112 bytes.
    // But the first fields are: vtable (4), data1 (4), data3 (4), data2 (4), zeros (16 bytes = indices 4-7), name buffer (64 bytes = indices 8 to 8+15 = up to index 23?).
    // Wait 64 bytes is 16 ints, so name occupies indices 8 to 23. Then next pointer at index 0x1c = 28. So it's after the name buffer.
    // So this[4..7] are zeros, then name at this[8..23], then next at this[28].
    // The code sets this[4..7] to zero, then sets this[0x1c] (i.e., this[28]) to the global head.
    // So we must ensure we haven't overwritten something. The actual assignment order is:

    // Set the next pointer to the current head of the global list
    this[0x1c] = (int)DAT_012059ec; // +0x70 bytes (112 dec)

    // Update the global head to point to this new entry
    DAT_012059ec = this;

    return this;
}