// FUNC_NAME: GameConnection::GameConnection
undefined4* __thiscall GameConnection::GameConnection(GameConnection* this, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5)
{
    uint16_t uVar1;
    undefined4 uVar2;
    int iVar3;
    struct {
        uint32_t a; // 0xbadbadba
        uint32_t b; // 0xbeefbeef
        uint32_t c; // 0xeac15a55
        uint32_t d; // 0x91100911
    } magicBuffer; // used for validation/hash

    // Call base class constructor with two parameters
    FUN_0046e6b0(param2, param3);

    // Set vtable pointers (multiple inheritance)
    *this = &PTR_FUN_00e31bb8;            // +0x00: primary vtable
    this[0xf] = &PTR_LAB_00e31d4c;        // +0x3C: secondary vtable
    this[0x12] = &PTR_LAB_00e31d5c;       // +0x48
    this[0x14] = &PTR_LAB_00e31d60;       // +0x50
    this[0x15] = &PTR_LAB_00e31d68;       // +0x54
    this[0x16] = &PTR_LAB_00e31dc8;       // +0x58

    // Initialize fields to zero
    this[0x60] = 0;                       // +0x180: flags
    this[0x61] = 0;                       // +0x184
    this[0x82] = 0;                       // +0x208: connection state?
    this[0x84] = 0;                       // +0x210
    *(uint16_t*)(this + 0x85) = 0;        // +0x214: two bytes
    *(uint16_t*)((int)this + 0x216) = 0;  // +0x216
    this[0x86] = 0;                       // +0x218

    // Allocate a 128-byte buffer and store pointer at +0x21C
    uVar2 = FUN_009c8e80(0x80);           // alloc(128)
    this[0x87] = uVar2;                   // +0x21C: buffer pointer

    this[0x88] = 0;                       // +0x220
    this[0x89] = 0x10;                    // +0x224: size/capacity = 16

    this[0x8e] = param5;                  // +0x238: store param5
    this[0x8c] = param4;                  // +0x230: store param4

    this[0x9c] = 0;                       // +0x270
    uVar2 = DAT_00e2b1a4;                 // global variable
    this[0x8a] = 0;                       // +0x228
    this[0x8b] = 0xffffffff;              // +0x22C: -1
    this[0x8f] = 0xffffffff;              // +0x23C: -1
    this[0x98] = 0;                       // +0x260
    this[0x99] = 0;                       // +0x264
    this[0x9a] = 0;                       // +0x268
    this[0x9b] = 0;                       // +0x26C

    *(uint8_t*)(this + 0x9d) = 0;         // +0x274: byte
    *(uint8_t*)((int)this + 0x275) = 0;   // +0x275
    *(uint8_t*)((int)this + 0x276) = 0;   // +0x276
    *(uint8_t*)((int)this + 0x277) = 1;   // +0x277: set to 1 (enabled?)

    this[0x9e] = 0;                       // +0x278
    this[0xa3] = 0;                       // +0x28C
    this[0xa4] = 0;                       // +0x290
    this[0xa5] = uVar2;                   // +0x294: store global value
    this[0xa6] = 0;                       // +0x298
    this[0xa7] = 0;                       // +0x29C
    this[0xa8] = 0;                       // +0x2A0

    this[0x8d] = DAT_01205224 + -1;       // +0x234: some ID - 1
    this[0x83] = 0;                       // +0x20C: init to 0

    // Magic validation buffer
    magicBuffer.a = 0xbadbadba;
    magicBuffer.b = 0xbeefbeef;
    magicBuffer.c = 0xeac15a55;
    magicBuffer.d = 0x91100911;

    // Initialize CRC/hash with first parameter
    FUN_0045da60(&magicBuffer, param2);
    iVar3 = FUN_004211e0(&magicBuffer);   // compute checksum/ID
    if (iVar3 != 0) {
        this[0x83] = iVar3;               // +0x20C: store computed value
    }

    // Initialize more fields to zero
    this[0x90] = 0;                       // +0x240
    this[0x91] = 0;                       // +0x244
    this[0x92] = 0;                       // +0x248
    this[0x93] = 0;                       // +0x24C
    this[0x94] = 0;                       // +0x250
    this[0x95] = 0;                       // +0x254
    this[0x96] = 0;                       // +0x258
    this[0x97] = 0;                       // +0x25C

    if (this[0x83] != 0) {
        FUN_0045ddf0(this, this[0x83]);   // additional initialization with computed ID
    }

    // Reference counting for global object DAT_0120e93c
    if (DAT_0120e93c != 0) {
        _DAT_0120e940 = _DAT_0120e940 + 1; // increment ref count
        iVar3 = FUN_00407da0();            // try to get allocated block
        if (iVar3 == 0) {
            FUN_004084d0(&DAT_0120e93c, 0x8000); // allocate with 0x8000 size (maybe)
        } else {
            uVar1 = *(uint16_t*)(iVar3 + 0x14);
            // Bit manipulation: increment some counter (probably reference count)
            *(uint16_t*)(iVar3 + 0x14) =
                ((int16_t)(((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
        }
    }

    // Reference counting for global object DAT_01206980
    if (DAT_01206980 != 0) {
        _DAT_01206984 = _DAT_01206984 + 1;
        iVar3 = FUN_00407da0();
        if (iVar3 != 0) {
            uVar1 = *(uint16_t*)(iVar3 + 0x14);
            // Similar manipulation
            *(uint16_t*)(iVar3 + 0x14) =
                ((int16_t)(((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
            return this;
        }
        FUN_004084d0(&DAT_01206980, 0x8000);
    }

    return this;
}