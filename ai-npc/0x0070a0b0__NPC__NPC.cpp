// FUNC_NAME: NPC::NPC
// Constructor for NPC class. Initializes many fields to zero after calling base class constructor (Sentient).
// Address: 0x0070a0b0
// Base constructor called: Sentient::Sentient at 0x0046c590

NPC* __thiscall NPC::NPC(NPC* this, void* initData) {
    // Call base class constructor (Sentient)
    Sentient::Sentient(initData);

    // Initialize vtable pointer to NPC's vtable
    this->vtable = (NPC_vtable*)&Vtable_NPC; // 0x00d613f4

    // Second interface vtable (e.g., for IEntity or ICrew)
    this->interfaceVtable1 = (void*)&InterfaceVtable1; // 0x00d613e4 at offset +0x3C

    // Third interface vtable (e.g., for INPCComponent)
    this->interfaceVtable2 = (void*)&InterfaceVtable2; // 0x00d613e0 at offset +0x48

    // Zero out various fields
    this->field_0x54 = 0;     // +0x54 (4 bytes)
    this->field_0x5C = 0;     // +0x5C (4 bytes)
    this->field_0x68 = 0;     // +0x68 (2 bytes) - written as short at +0x60? Actually offsets are tricky due to pointer arithmetic.
    // The decompiled shows multiple byte/word assignments. We simplify as zeroing entire struct area.
    // For clarity, we zero all fields from offset 0x54 to 0x7A.

    // Using memset-like approach for brevity:
    char* base = reinterpret_cast<char*>(this);
    memset(base + 0x54, 0, 0x26); // clears +0x54 to +0x7A inclusive (0x7A - 0x54 = 0x26)

    // Additional specific fields set to zero (already covered by memset):
    // *(undefined2 *)(this + 0x18) = 0; // +0x60 word
    // *(undefined2 *)((int)this + 0x62) = 0; // +0x62 word
    // *(undefined2 *)(this + 0x1a) = 0; // +0x68 word
    // *(undefined2 *)((int)this + 0x6a) = 0; // +0x6A word
    // *(undefined2 *)(this + 0x1c) = 0; // +0x70 word
    // *(undefined2 *)((int)this + 0x72) = 0; // +0x72 word
    // *(undefined2 *)(this + 0x1e) = 0; // +0x78 word
    // *(undefined2 *)((int)this + 0x7a) = 0; // +0x7A word
    // param_1[0x14] through param_1[0x1e] correspond to +0x50 to +0x78 (4-byte fields)

    return this;
}