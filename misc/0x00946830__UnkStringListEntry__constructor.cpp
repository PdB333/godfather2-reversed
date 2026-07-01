// FUNC_NAME: UnkStringListEntry::constructor

// This function appears to be a constructor or initializer for a structure that
// manages a list of string entries. It stores a pointer to a vtable (or similar),
// copies a string, and stores additional parameters. It also maintains a global
// linked list (or free list) using the global DAT_012059ec.

undefined4 * __thiscall UnkStringListEntry::constructor(
    undefined4 *this,
    char *param_2,
    undefined4 param_3,
    undefined4 param_4,
    undefined4 param_5
)
{
    FUN_0064cc90();  // likely base constructor or memory clearing
    *this = &PTR_LAB_00d8b490;  // set vtable pointer (offset +0x00)
    _strncpy((char *)(this + 8), param_2, 0x3f);  // copy string into buffer at offset +0x20 (since this+8 is 0x20 bytes)
    this[1] = param_3;   // +0x04
    this[3] = param_4;   // +0x0C
    this[2] = param_5;   // +0x08
    this[4] = 0;         // +0x10
    this[5] = 0;         // +0x14
    this[6] = 0;         // +0x18
    this[7] = 0;         // +0x1C
    this[0x1c] = DAT_012059ec;  // link into global list: +0x70
    DAT_012059ec = this;        // update global head
    return this;
}