// FUNC_NAME: DebugLogEntry::DebugLogEntry
undefined4 * __thiscall DebugLogEntry::DebugLogEntry(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base class constructor (likely for linked list node base)
    FUN_0064cc90();

    // Set vtable pointer (class-specific)
    *this = &PTR_LAB_00d6a734;

    // Copy name string into buffer at offset +0x20 (this+8 in 4-byte units)
    _strncpy((char *)(this + 8), name, 0x3f);  // max 63 chars

    // Store parameters at offsets:
    // +0x04: param3
    // +0x0C: param4
    // +0x08: param5
    this[1] = param3;
    this[3] = param4;
    this[2] = param5;

    // Zero out fields at offsets +0x10 through +0x1C (4 fields)
    this[4] = 0;
    this[5] = 0;
    this[6] = 0;
    this[7] = 0;

    // Insert this node at head of global linked list (DAT_012059ec is head pointer)
    // Offset +0x70 (this[0x1c]) stores next pointer
    this[0x1c] = DAT_012059ec;  // next = old head
    DAT_012059ec = this;        // head = this

    return this;
}