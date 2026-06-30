// FUNC_NAME: NetReliableStream::NetReliableStream
// Address: 0x00724ea0
// Role: Constructor for a network reliable stream object (32KB payload buffer, debug sentinel initialization)
// This appears to be part of EA's EARS networking layer, possibly for building reliable packets.
// The object contains a large buffer (0x8000 bytes = 32768) and multiple vtable pointers (likely multiple inheritance or embedded sub-objects).
// Initializes fields with debug sentinels (0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911) and copies static initialization data.

extern void BaseStreamConstructor(undefined4 param); // FUN_0046c590
extern void *PTR_LAB_00e32854; // vtable pointer
extern void *PTR_FUN_00d62380; // vtable pointer (primary)
extern void *PTR_LAB_00d62370; // vtable pointer
extern void *PTR_LAB_00d6236c; // vtable pointer
extern void *PTR_LAB_00d62368; // vtable pointer
extern uint32_t _DAT_00d5780c; // some global (maybe default value)
extern uint32_t DAT_00d62364;  // some global
extern void *DAT_0120e93c;     // static initialization data pointer (or NULL)
extern void memcpy(void *dest, void *src, uint32_t size); // FUN_00408900

struct NetReliableStream {
    // offsets in uint32 (4-byte words)
    uint32_t vtable0;    // +0x00: primary vtable
    // ... fields from 0x0C to 0x134
    // +0x3C (0xF*4): buffer start? (passed to memcpy)
};

NetReliableStream * __thiscall NetReliableStream::NetReliableStream(NetReliableStream *this, uint32_t initParam) {
    BaseStreamConstructor(initParam); // call base class constructor

    // Set vtable pointers (multiple inheritance or embedded objects)
    this->vtableAt0x50[0] = &PTR_LAB_00e32854;   // +0x50 (0x14*4) - first assignment, overwritten later
    this->vtable0 = &PTR_FUN_00d62380;             // +0x00
    this->vtableAt0x3C[0] = &PTR_LAB_00d62370;     // +0x3C (0xF*4)
    this->vtableAt0x48[0] = &PTR_LAB_00d6236c;     // +0x48 (0x12*4)
    this->vtableAt0x50[0] = &PTR_LAB_00d62368;     // +0x50 (0x14*4) - final vtable pointer at this offset

    // Initialize fields with debug sentinels
    this->field0x54 = 0xbadbadba;                   // +0x54 (0x15*4)
    this->field0x64 = 0;                            // +0x64 (0x19*4)
    this->field0xCC = 0;                            // +0xCC (0x33*4)
    *(uint16_t*)(&this->field0xD0) = 0;            // +0xD0 (0x34*4) low word
    *(uint16_t*)((uint32_t)this + 0xD2) = 0;       // +0xD2
    this->field0xD4 = 0;                            // +0xD4 (0x35*4)
    *(uint16_t*)(&this->field0xD8) = 0;            // +0xD8 (0x36*4) low word
    *(uint16_t*)((uint32_t)this + 0xDA) = 0;       // +0xDA
    this->field0xDC = 0;                            // +0xDC (0x37*4)
    *(uint16_t*)(&this->field0xE0) = 0;            // +0xE0 (0x38*4) low word
    *(uint16_t*)((uint32_t)this + 0xE2) = 0;       // +0xE2
    this->field0xEC = 0xbadbadba;                   // +0xEC (0x3B*4)
    this->field0xF0 = 0xbeefbeef;                   // +0xF0 (0x3C*4)
    this->field0xF4 = 0xeac15a55;                   // +0xF4 (0x3D*4)
    this->field0xF8 = 0x91100911;                   // +0xF8 (0x3E*4)
    this->field0xFC = 0xbadbadba;                   // +0xFC (0x3F*4)
    this->field0x10C = 0xbadbadba;                  // +0x10C (0x43*4)
    this->field0x110 = 0xbeefbeef;                  // +0x110 (0x44*4)
    this->field0x114 = 0xeac15a55;                  // +0x114 (0x45*4)
    this->field0x118 = 0x91100911;                  // +0x118 (0x46*4)
    this->field0x128 = 0;                           // +0x128 (0x4A*4)
    this->field0x12C = 0;                           // +0x12C (0x4B*4)
    this->field0x130 = 0;                           // +0x130 (0x4C*4)

    // Initialize four groups of 5 fields each (0-indexed)
    uint32_t globalVal = _DAT_00d5780c;             // base value for these fields
    this->group0[0] = globalVal;                    // +0x80 (0x20*4)
    this->group0[1] = 0;                            // +0x84 (0x21*4)
    this->group0[2] = 0;
    this->group0[3] = 0;
    this->group0[4] = 0;                            // +0x90 (0x24*4)
    this->group1[0] = globalVal;                    // +0x94 (0x25*4)
    this->group1[1] = 0;
    this->group1[2] = 0;
    this->group1[3] = 0;
    this->group1[4] = 0;                            // +0xA4 (0x29*4)
    this->group2[0] = globalVal;                    // +0xA8 (0x2A*4)
    this->group2[1] = 0;
    this->group2[2] = 0;
    this->group2[3] = 0;
    this->group2[4] = 0;                            // +0xB8 (0x2E*4)
    this->group3[0] = globalVal;                    // +0xBC (0x2F*4)
    this->group3[4] = 0;                            // +0xCC (0x33*4) note: overwrites previous field0xCC
    this->group3[3] = 0;
    this->group3[2] = 0;
    this->group3[1] = 0;                            // +0xC0 (0x30*4)

    // Set remaining fields
    this->field0xE4 = 1;                            // +0xE4 (0x39*4)
    this->field0x11C = 0;                           // +0x11C (0x47*4)
    this->field0x60 = 0;                            // +0x60 (0x18*4)
    this->field0x5C = 0;                            // +0x5C (0x17*4)
    this->field0x58 = 0;                            // +0x58 (0x16*4)
    this->field0x54 = 0;                            // +0x54 (0x15*4) - overrides earlier 0xbadbadba
    this->field0xE8 = 0;                            // +0xE8 (0x3A*4)
    this->field0x120 = 0;                           // +0x120 (0x48*4)
    this->field0x124 = DAT_00d62364;                // +0x124 (0x49*4)
    this->field0x68 = 0;                            // +0x68 (0x1A*4)
    this->field0x6C = 0;                            // +0x6C (0x1B*4)
    this->field0x70 = 0;                            // +0x70 (0x1C*4)
    this->field0x74 = 0;                            // +0x74 (0x1D*4)
    this->field0x134 = 0;                           // +0x134 (0x4D*4)
    this->field0x108 = 0;                           // +0x108 (0x42*4)
    this->field0x104 = 0;                           // +0x104 (0x41*4)
    this->field0x100 = 0;                           // +0x100 (0x40*4)
    this->field0xFC = 0;                            // +0xFC (0x3F*4) - overrides earlier 0xbadbadba

    // Copy static initialization data into the buffer at offset 0x3C if available
    if (DAT_0120e93c != 0) {
        memcpy(&this->vtableAt0x3C, DAT_0120e93c, 0x8000); // copies 32KB into stream buffer
    }

    return this;
}