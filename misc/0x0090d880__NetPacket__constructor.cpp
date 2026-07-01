// FUNC_NAME: NetPacket::constructor
uint* __thiscall NetPacket::constructor(uint* this, uint someId, uint sequence, uint ack, uint flags, undefined4 unknownParam6, int listHead, undefined8* data)
{
    uint uVar1;

    // Initialize packet fields
    this[1] = sequence;          // +0x04: sequence number
    this[0] = flags & 0x1f;      // +0x00: flags (5-bit mask, likely packet type or window bits)
    this[2] = ack;               // +0x08: acknowledgment
    this[3] = someId;            // +0x0C: perhaps message ID or session ID

    // Call initializer for unknown subsystem (likely memory or state)
    FUN_004d3bc0(unknownParam6);

    // Zero out reserved fields (offsets 0x20 to 0x2C)
    this[8] = 0;                 // +0x20
    this[9] = 0;                 // +0x24
    this[10] = 0;                // +0x28
    this[0xb] = 0;               // +0x2C

    // Link into send list: if listHead is non-null, use its +0x48 as list anchor
    if (listHead == 0) {
        uVar1 = 0;
    } else {
        uVar1 = listHead + 0x48; // +0x48: pointer to linked-list node inside listHead
    }
    this[0xc] = uVar1;           // +0x30: store anchor pointer (or null)
    this[0xd] = 0;              // +0x34: next pointer, initially null
    if (uVar1 != 0) {
        // Insert this node after the anchor (push front)
        this[0xd] = *(uint*)(uVar1 + 4);   // +0x34: remember old next
        *(uint**)(uVar1 + 4) = this + 0xc; // anchor's next now points to us
    }

    // Copy optional 24-byte payload if provided
    this[0xe] = 0;              // +0x38: clear payload area
    this[0x13] = 0;             // +0x4C: clear last word (ensures zero if no data)
    if (data != (undefined8*)0x0) {
        *(undefined8*)(this + 0xe) = data[0];   // +0x38-0x3F: first 8 bytes
        *(undefined8*)(this + 0x10) = data[1];  // +0x40-0x47: next 8 bytes
        *(undefined8*)(this + 0x12) = data[2];  // +0x48-0x4F: last 8 bytes
    }

    return this;
}