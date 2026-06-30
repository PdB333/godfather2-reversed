// FUNC_NAME: initGlobalResourceBuffer
void* initGlobalResourceBuffer(void)
{
    // Global static instance at 0x012190d8 (size 0x28)
    // Structure layout:
    // +0x00: void* vtable (PTR_LAB_00e37c38)
    // +0x04: void* secondaryPtr (&DAT_00e37bec)
    // +0x08: uint32 magic (0x2e656c75 = "ule.")
    // +0x0C: int32 version (2)
    // +0x10: int32 bufferSize (0x800)
    // +0x14: int32 padding (0)
    // +0x18: int32 padding (0)
    // +0x1C: int32 padding (0)
    // +0x20: int32 padding (0)
    // +0x24: int32 padding (0)

    _DAT_012190e4 = 0; // offset 0x0C (version) actually version was set later; this is offset +0x0C? Wait, careful.
    // Re-ordered to match offsets:
    // Actually the assignments as they appear in decompiled order:
    // _DAT_012190e4 = 0; // offset +0x0C
    // _DAT_012190ec = 0; // offset +0x14
    // _DAT_012190f4 = 0; // offset +0x1C
    // _DAT_012190f8 = 0; // offset +0x20
    // _DAT_012190fc = 0; // offset +0x24
    // _DAT_012190dc = &DAT_00e37bec; // offset +0x04
    // _DAT_012190e0 = 0x2e656c75; // offset +0x08
    // _DAT_012190e8 = 2; // offset +0x10
    // _DAT_012190f0 = 0x800; // offset +0x18? Wait: offset delta:
    // 012190d8 start
    // +0x00: d8
    // +0x04: dc
    // +0x08: e0
    // +0x0C: e4
    // +0x10: e8
    // +0x14: ec
    // +0x18: f0
    // +0x1C: f4
    // +0x20: f8
    // +0x24: fc
    // So _DAT_012190e8 (offset 0x10) = 2 is version, _DAT_012190f0 (offset 0x18) = 0x800 is bufferSize, and the zeros fill other fields.

    _DAT_012190e4 = 0;          // +0x0C: padding
    _DAT_012190ec = 0;          // +0x14: padding
    _DAT_012190f4 = 0;          // +0x1C: padding
    _DAT_012190f8 = 0;          // +0x20: padding
    _DAT_012190fc = 0;          // +0x24: padding

    _DAT_012190dc = &DAT_00e37bec; // +0x04: pointer to shared data
    _DAT_012190e0 = 0x2e656c75;    // +0x08: magic identifier 'ule.'
    _DAT_012190e8 = 2;             // +0x10: version number
    _DAT_012190f0 = 0x800;         // +0x18: buffer size (2048 bytes)
    _DAT_012190d8 = &PTR_LAB_00e37c38; // +0x00: vtable pointer

    return &DAT_012190d8; // return address of global instance
}