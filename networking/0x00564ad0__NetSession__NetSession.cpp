// FUNC_NAME: NetSession::NetSession
// Function address: 0x00564ad0
// Constructor for the network session manager singleton

void __thiscall NetSession::NetSession(int *this)
{
    // Save global singleton pointer
    g_netSession = this;

    // Set vtable pointers (offsets 0x00 and 0x04)
    this[1] = &PTR___purecall_00e3a568; // +0x04: base vtable?
    this[0] = &PTR_FUN_00e3a574;        // +0x00: derived vtable?
    this[1] = &PTR_FUN_00e3a58c;        // Override vtable at +0x04?

    // Initialize various state fields to zero
    this[7] = 0;   // +0x1C: unknown state
    this[8] = 0;   // +0x20: unknown flags

    this[0x49] = 0; // +0x124: unknown counter1
    this[0x4a] = 0; // +0x128: unknown counter2

    this[0x8b] = 0; // +0x22C: unknown field1
    this[0x8c] = 0; // +0x230: unknown field2
    this[0x8d] = 0; // +0x234: unknown field3

    *(byte *)(this + 0x8e) = 0; // +0x238: unknown flag0

    // Initialize five 'slot' structures (each with a 4-byte counter and a byte flag at -0x80)
    this[0xaf] = 0xf;             // +0x2BC: slot0.counter = 15
    *(byte *)(this + 0x8f) = 0;  // +0x23C: slot0.flag = 0

    this[0xd0] = 0xf;             // +0x340: slot1.counter = 15
    *(byte *)(this + 0xb0) = 0;  // +0x2C0: slot1.flag = 0

    this[0xf1] = 0xf;             // +0x3C4: slot2.counter = 15
    *(byte *)(this + 0xd1) = 0;  // +0x344: slot2.flag = 0

    this[0x112] = 0xf;            // +0x448: slot3.counter = 15
    *(byte *)(this + 0xf2) = 0;  // +0x3C8: slot3.flag = 0

    this[0x133] = 0xf;            // +0x4CC: slot4.counter = 15
    *(byte *)(this + 0x113) = 0;  // +0x44C: slot4.flag = 0
}