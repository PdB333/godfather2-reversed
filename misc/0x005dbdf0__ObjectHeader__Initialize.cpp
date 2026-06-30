// FUNC_NAME: ObjectHeader::Initialize
void __thiscall ObjectHeader::Initialize(void)
{
    uint32_t uVar1;
    
    uVar1 = g_timeStamp1; // DAT_00e2eff4
    this->magic0 = 0xbadbadba; // +0x20 (offset 8 dwords)
    this->magic1 = 0xbeefbeef; // +0x24
    this->field0 = uVar1; // +0x00
    this->field1 = uVar1; // +0x04
    this->field2 = uVar1; // +0x08
    uVar1 = g_timeStamp2; // DAT_00e2b1a4
    this->field3 = uVar1; // +0x0C (dword)
    this->field4 = uVar1; // +0x10
    this->field5 = 0; // +0x14
    this->field6 = 0; // +0x18
    this->field7 = 1; // +0x1C? Wait check offsets
    // Actually offset 0x1C is field7 (dword at index 7)
    this->magic0 = 0xbadbadba; // duplicate
    this->magic1 = 0xbeefbeef; // duplicate
    this->magic2 = 0xeac15a55; // +0x28
    this->magic3 = 0x91100911; // +0x2C
    this->byteAt12 = 0; // +0x0C (first byte of field3)
    return;
}

// However, the decompiled code shows offsets in terms of dword indices. Let's recalc with actual offsets:
// in_EAX[8] = 0xbadbadba -> offset 32 (0x20)
// in_EAX[9] = 0xbeefbeef -> offset 36 (0x24)
// *in_EAX = uVar1 -> offset 0
// in_EAX[1] = uVar1 -> offset 4
// in_EAX[2] = uVar1 -> offset 8
// in_EAX[3] = DAT_00e2b1a4 -> offset 12
// in_EAX[4] = uVar1 -> offset 16
// in_EAX[5] = 0 -> offset 20
// in_EAX[6] = 0 -> offset 24
// in_EAX[7] = 1 -> offset 28
// then duplicate [8] and [9] (overwrites previous?)
// in_EAX[10] = 0xeac15a55 -> offset 40 (0x28)
// in_EAX[0xb] = 0x91100911 -> offset 44 (0x2C)
// *(undefined1 *)(in_EAX + 0xc) = 0 -> offset 12 (first byte of field at offset 12)

// So the structure has at least fields at offsets: 0,4,8,12,16,20,24,28,32,36,40,44 (48 bytes total) plus a byte at offset 12.
// This is a 48-byte header with magic numbers and two timestamps.

// I'll refine the reconstructed code accordingly.// FUNC_NAME: ObjectHeader::Initialize
void __thiscall ObjectHeader::Initialize(void)
{
    uint32_t ts1 = DAT_00e2eff4; // global timestamp or counter
    uint32_t ts2 = DAT_00e2b1a4; // another global timestamp

    // +0x20 (8*4) magic0
    this->magic0 = 0xbadbadba;
    // +0x24 (9*4) magic1
    this->magic1 = 0xbeefbeef;

    // +0x00: field0 = ts1
    this->field0 = ts1;
    // +0x04: field1 = ts1
    this->field1 = ts1;
    // +0x08: field2 = ts1
    this->field2 = ts1;

    // +0x0C: field3 (dword) = ts2
    this->field3 = ts2;
    // +0x10: field4 = ts1
    this->field4 = ts1;

    // +0x14: field5 = 0
    this->field5 = 0;
    // +0x18: field6 = 0
    this->field6 = 0;

    // +0x1C: field7 = 1
    this->field7 = 1;

    // +0x20: magic0 (overwrites previous)
    this->magic0 = 0xbadbadba;
    // +0x24: magic1 (overwrites previous)
    this->magic1 = 0xbeefbeef;
    // +0x28: magic2
    this->magic2 = 0xeac15a55;
    // +0x2C: magic3
    this->magic3 = 0x91100911;

    // +0x0C (first byte of field3) set to 0
    // This likely zeros the low byte of the dword field3
    *(uint8_t *)(((uint8_t*)this) + 0x0C) = 0;
}