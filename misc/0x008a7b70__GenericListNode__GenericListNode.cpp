// FUNC_NAME: GenericListNode::GenericListNode
undefined4 * __thiscall GenericListNode::GenericListNode(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base constructor or initialization routine (likely a base class constructor)
    FUN_0064cc90();

    // Set vtable pointer (assigned from global PTR_LAB_00d79bd0)
    *this = &PTR_LAB_00d79bd0;

    // Copy name string into member at offset +0x20 (32 bytes), max 63 characters
    _strncpy((char *)(this + 8), name, 0x3f);

    // Assign the next three parameters to fields at offsets +4, +12, +8 respectively
    this[1] = param3;   // +0x04
    this[3] = param4;   // +0x0C
    this[2] = param5;   // +0x08

    // Initialize four fields to zero (offsets +0x10, +0x14, +0x18, +0x1C)
    this[4] = 0;        // +0x10
    this[5] = 0;        // +0x14
    this[6] = 0;        // +0x18
    this[7] = 0;        // +0x1C

    // Link into a global singly‑linked list:
    // Store previous head (DAT_012059ec) into the next pointer at offset +0x70
    this[0x1c] = DAT_012059ec;   // +0x70 (28*4 = 112)

    // Update global head to point to the new node
    DAT_012059ec = this;

    return this;
}