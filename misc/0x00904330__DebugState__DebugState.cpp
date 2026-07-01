// FUNC_NAME: DebugState::DebugState

// Constructor for DebugState class at 0x00904330
// Initializes debug marker blocks and state variables
DebugState::DebugState(undefined4 initParam) {
    // Call base class constructor (likely some initialization)
    FUN_0046c590(initParam);

    // Set vtable pointer (first field)
    *this = &PTR_FUN_00d81fd0; // vtable

    // Debug marker block 1 (offsets 0x3C, 0x48, 0x50-0x6C)
    this->field_0x3C = &PTR_LAB_00d81fc0; // +0x3C
    this->field_0x48 = &PTR_LAB_00d81fbc; // +0x48
    this->magic1_0 = 0xbadbadba; // +0x50
    this->magic1_1 = 0xbeefbeef; // +0x54
    this->magic1_2 = 0xeac15a55; // +0x58
    this->magic1_3 = 0x91100911; // +0x5C

    // Debug marker block 2 (offsets 0x60-0x6C)
    this->magic2_0 = 0xbadbadba; // +0x60
    this->magic2_1 = 0xbeefbeef; // +0x64
    this->magic2_2 = 0xeac15a55; // +0x68
    this->magic2_3 = 0x91100911; // +0x6C

    // Zero-initialize a large block (offsets 0x70-0xA4)
    this->field_0x70 = 0; // +0x70
    this->field_0x74 = 0; // +0x74
    this->field_0x78 = 0; // +0x78
    this->field_0x7C = 0; // +0x7C
    this->field_0x80 = 0; // +0x80
    *(undefined2 *)((int)this + 0x84) = 0; // +0x84 (16-bit)
    *(undefined2 *)((int)this + 0x86) = 0; // +0x86 (16-bit)
    this->field_0x88 = 0; // +0x88
    *(undefined2 *)((int)this + 0x8C) = 0; // +0x8C (16-bit)
    *(undefined2 *)((int)this + 0x8E) = 0; // +0x8E (16-bit)
    this->field_0x90 = 0; // +0x90
    *(undefined2 *)((int)this + 0x94) = 0; // +0x94 (16-bit)
    *(undefined2 *)((int)this + 0x96) = 0; // +0x96 (16-bit)
    this->field_0x98 = 0; // +0x98
    *(undefined2 *)((int)this + 0x9C) = 0; // +0x9C (16-bit)
    *(undefined2 *)((int)this + 0x9E) = 0; // +0x9E (16-bit)
    this->field_0xA0 = 0; // +0xA0
    *(undefined2 *)((int)this + 0xA4) = 0; // +0xA4 (16-bit)
    *(undefined2 *)((int)this + 0xA6) = 0; // +0xA6 (16-bit)

    // Additional state fields (offsets 0xA8-0xC4)
    this->field_0xA8 = DAT_00d5eee4; // +0xA8
    this->field_0xAC = DAT_00d5d7b8; // +0xAC
    this->field_0xB4 = 0; // +0xB4
    this->field_0xB8 = _DAT_00d5cf70; // +0xB8
    this->field_0xC4 = 0; // +0xC4
    this->field_0xB0 = 0xffffffff; // +0xB0
    this->field_0xBC = 1; // +0xBC
    this->field_0xC0 = DAT_00d5ccf8; // +0xC0
}