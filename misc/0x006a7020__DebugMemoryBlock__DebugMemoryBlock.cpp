// FUNC_NAME: DebugMemoryBlock::DebugMemoryBlock
undefined4 * __thiscall DebugMemoryBlock::DebugMemoryBlock(undefined4 *this, undefined4 param_2) // param_2 likely base class initialization data
{
    // +0x00: vtable pointer
    // +0x3C: pointer to static data (likely a second vtable or interface)
    // +0x48: another static pointer
    // +0x50: 4 bytes zero
    // +0x54: 2 bytes zero
    // +0x56: 2 bytes zero
    // +0x58: 4 bytes zero
    // +0x5C: 2 bytes zero
    // +0x5E: 2 bytes zero
    // +0x60: sentinel 0xBADBADBA
    // +0x64: sentinel 0xBEEFBEEF
    // +0x68: sentinel 0xEAC15A55
    // +0x6C: sentinel 0x91100911
    // +0x70: 4 bytes zero
    // +0x74: 4 bytes zero

    FUN_0046c590(param_2); // Base class constructor call
    *this = &PTR_FUN_00d5d810; // Set vtable
    this[0xf] = &PTR_LAB_00d5d800;
    this[0x12] = &PTR_LAB_00d5d7fc;
    this[0x14] = 0;
    *(undefined2 *)(this + 0x15) = 0;
    *(undefined2 *)((int)this + 0x56) = 0;
    this[0x16] = 0;
    *(undefined2 *)(this + 0x17) = 0;
    *(undefined2 *)((int)this + 0x5e) = 0;
    this[0x18] = 0xbadbadba;
    this[0x19] = 0xbeefbeef;
    this[0x1a] = 0xeac15a55;
    this[0x1b] = 0x91100911;
    this[0x1c] = 0;
    this[0x1d] = 0;
    return this;
}