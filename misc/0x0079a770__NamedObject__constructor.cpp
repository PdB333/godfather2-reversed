// FUNC_NAME: NamedObject::constructor
undefined4 * __thiscall NamedObject::constructor(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base class constructor (likely initializes vtable or other base members)
    FUN_0064cc90();

    // Set vtable pointer
    *this = &PTR_LAB_00d6a764;

    // Copy name into buffer at offset +0x20 (max 63 chars)
    _strncpy((char *)(this + 8), name, 0x3f);

    // Store parameters at offsets +0x04, +0x08, +0x0C
    this[1] = param3;
    this[3] = param4;
    this[2] = param5;

    // Zero out four fields at offsets +0x10, +0x14, +0x18, +0x1C
    this[4] = 0;
    this[5] = 0;
    this[6] = 0;
    this[7] = 0;

    // Link into global linked list: set next pointer at offset +0x70 to current head, then update head to this
    this[0x1c] = DAT_012059ec;  // g_namedObjectListHead
    DAT_012059ec = this;        // g_namedObjectListHead = this

    return this;
}