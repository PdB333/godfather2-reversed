// FUNC_NAME: DebugNamedObject::DebugNamedObject
undefined4 * __thiscall DebugNamedObject::DebugNamedObject(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base class constructor (likely sets vtable and initializes base fields)
    baseConstructor();

    // Set vtable pointer for this class
    *this = &PTR_LAB_00d6a794;

    // Copy name string into buffer at offset +0x20 (max 63 chars + null)
    strncpy((char *)(this + 8), name, 0x3f);

    // Store additional parameters
    this[1] = param3;   // +0x04
    this[3] = param4;   // +0x0C
    this[2] = param5;   // +0x08

    // Zero out fields at offsets +0x10, +0x14, +0x18, +0x1C
    this[4] = 0;
    this[5] = 0;
    this[6] = 0;
    this[7] = 0;

    // Link into global singly-linked list (prepend)
    // DAT_012059ec is the head pointer of the list
    this[0x1C] = DAT_012059ec;  // +0x70: next pointer
    DAT_012059ec = this;        // Update head to this new node

    return this;
}